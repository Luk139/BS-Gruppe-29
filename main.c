/* *  Echo-Server * * * */#include <sys/socket.h>#include <netinet/in.h>#include <stdio.h>#include <stdlib.h>#include <strings.h>#include <unistd.h>#include <string.h>#include <sys/ipc.h>#include <sys/shm.h>#include <sys/sem.h>#include "keyValStore.h"#include "sub.h"#define STORESIZE 100#define SEGSIZE (sizeof(Key)*STORESIZE)#define LOOP 1#define BUFSIZE 1024 // Size of the buffer//  Opened Ports in the Docker Container, or whatelse is used for the host-system#define PORT_NUMBER 5678// Port for running on mac itself//#define PORT_NUMBER 4711#define LENGTH 100#define SIZE 25//TODO global variable for address of the store could be implemented with "extern" -> also the index// Storing the Index of the keyValueStoreint pos = 0;//*sharMem is used to edit values in the storeKey *sharMem = NULL;int semaphoreId;int clientHandler(int cnnct_fd) {    int read_bytes;    char userInput[BUFSIZE];    struct sembuf enter, leave; // Structs für den Semaphor    enter.sem_num = leave.sem_num = 0;  // Semaphor 0 in der Gruppe    enter.sem_flg = leave.sem_flg = SEM_UNDO;    enter.sem_op = -1; // blockieren, DOWN-Operation    leave.sem_op = 1;   // freigeben, UP-Operation    while (LOOP){        // read the bytes from the client        read_bytes = read(cnnct_fd, userInput, BUFSIZE);        if (read_bytes < 0) {            perror("Error while read()");            return EXIT_FAILURE;        }        // Sending back data as long the client keeps sending some        while (read_bytes > 0) {            //Quit            if (strncmp("QUIT", userInput, 4) == 0) {                printf("Server Exit...\n");                exit(0);                //break;            }            // Get rid of the trash at the end of the telnet message            char delimiter1[] = "\r";            char *ptr;            ptr = strtok(userInput, delimiter1);            // /x20 delimiter is a space            char delimiter[] = "\x20";            //Array for storing the prts of the string [0] will store the command, [1] for the key and [2] for the value            char arr[SIZE][LENGTH];            int i = 0;            int sendBytes = 0;            //First Part, should be the commands GET, PUT, DEL            ptr = strtok(ptr, delimiter);            sendBytes = strlen(ptr);            while (ptr != NULL) {                strcpy(arr[i], ptr);                write(cnnct_fd, ptr, sendBytes);                //add : to the message to the client                // if put command skip last :                if (i <= 1) {                    write(cnnct_fd, ":", 1);                }                // create next                ptr = strtok(NULL, delimiter);                //Dont set the integer to NULL in the last execution                if (ptr != NULL) {                    sendBytes = strlen(ptr);                }                i++;            }            char *wrongInput = "Please use a proper command.\n";            int wrngInptLength = strlen(wrongInput);            char *command;            //Check the Input for a Command GET, PUT, DEL            if (strcmp(arr[0], "GET") == 0) {                //TODO We could face problems with semaphores here                command = get(arr[1], sharMem);                sendBytes = strlen(command);                write(cnnct_fd, command, sendBytes);                write(cnnct_fd, "\n", 2);            } else if (strcmp(arr[0], "PUT") == 0) {                put(arr[1], arr[2], pos, sharMem);                pos += 1;                write(cnnct_fd, "\n", 2);                //printf("positions counter: %d\n", pos);            } else if (strcmp(arr[0], "DEL") == 0) {                int i = del(arr[1], sharMem);                if (i >= 0) {                    write(cnnct_fd, "key_deleted\n", 12);                } else {                    write(cnnct_fd, "key_nonexistent\n", 16);                }            } else if (strcmp(arr[0], "ALL") == 0) {                ausgabeKeyValStore(sharMem);            }            else if (strcmp(arr[0], "BEG") == 0) {                semop(semaphoreId, &enter, 1); // Eintritt in kritischen Bereich                if(strcmp(arr[0], "END")){                    semop(semaphoreId, &leave, 1); // Verlassen des kritischen Bereichs                }              }            else {                write(cnnct_fd, wrongInput, wrngInptLength);            }            printf("sending back the %d bytes I received...\n", read_bytes);            //write(cnnct_fd, userInput, read_bytes);            read_bytes = read(cnnct_fd, userInput, BUFSIZE);        }    }}int main(){    // id for shared memory segment    int id;    /*Create the shared Memory    * IPC_CREATE = Numeric key of type long    * SEGSIZE = Size of the shm    * IPC_CREAT    * 0600 = Write, Read, Execute permission for the user    */    if((id = shmget(IPC_PRIVATE, SEGSIZE, IPC_CREAT|0600)) < 0){        perror("Error while shmget()");        return EXIT_FAILURE;    }    /* Attach the Shared Memory     * (Key *) = Typecast to keypointer     * shmid = integer for the sharedmemory     * shmaddr = for choosing the address of the memory, 0 for the os to choose it itself     * shmflg = 0 for read/write allowance for the shared memory     */    if((sharMem = (Key *)shmat(id, 0, 0)) < 0){        perror("Error while shmat()");        return EXIT_FAILURE;    }    // Empty the random values in the shared memory    // s = sharmem specifies the first address to be overwritten    // c = 0 => set all adresses of the specified memory to 0    // n = SEGSIZE specifies the size, starting from the first address    memset(sharMem,0,SEGSIZE);    /*  key = of type long, IPC_PRIVATE => Kernel specifies the key by itself     *  nsems = counter for the semaphores     *  semflg = Create semaphoregrp with access rights 0644     */    // Store the Semaphore ID    semaphoreId = semget(IPC_PRIVATE, 1, IPC_CREAT | 0644);    if (semaphoreId <0){        perror("Error while semget()");        return EXIT_FAILURE;    }    unsigned short initiateSpecs[2] = {1};    // If you need to set several semaphores    //    unsigned short initiateSpecs[2] = {1, 1};    /*  id = Identifier for the semaphoregrp     *  nsem = Counter of the semaphore in the grp     *  cmd = SETALL set values of the semaphore     *  arg = Options for setall need to be of type array to set the values     */    int semaphoreCtl = semctl(semaphoreId, 1, SETALL, initiateSpecs);    if (semaphoreId <0){        perror("Error while semctl()");        return EXIT_FAILURE;    }    //testarea/*    strcpy(sharMem[0].keyName, "v1");    strcpy(sharMem[0].keyValue, "n1");    printf("%s",sharMem[0].keyName );    printf("%s",sharMem[0].keyValue );*/    /*    Key testkey;    testkey.keyName = "n1";    testkey.keyValue = "v1";    sharMem[0] = testkey;    testkey.keyName = "n2";    testkey.keyValue = "v2";    sharMem[1] = testkey;    testkey.keyName = "n3";    testkey.keyValue = "v3";    sharMem[2] = testkey;    testkey.keyName = "n4";    testkey.keyValue = "v4";    sharMem[3] = testkey;    printf("%s\n", sharMem[0].keyName);    printf("%s\n", sharMem[0].keyValue);    printf("%s\n", sharMem[1].keyName);    printf("%s\n", sharMem[1].keyValue);    printf("%s\n", sharMem[2].keyName);    printf("%s\n", sharMem[2].keyValue);    printf("%s\n", sharMem[3].keyName);    printf("%s\n", sharMem[3].keyValue);*/    //File-Descriptor Rendezvous und Connect    int rndvz_fd;    //  Struct for the connection between client and server    struct sockaddr_in client;    //Length of the Client-Data    socklen_t client_len = sizeof(client);    /*  Creating the socket with ipv4 and tcp no further description for protocol needed so 0 is enough -> SOCK_STREAM uses tcp by default.    *   AF_INET = ipv4    *   SOCK_STREAM = tcp    *   protocol 0 = default (For other protocols to expect when working with ip)    */    rndvz_fd = socket(AF_INET, SOCK_STREAM, 0);    //  Return value of rndzvs_fd is negative when an error occurs. And 0 when successfull. If it wasn't successfull terminate program    if (rndvz_fd <0){        perror("Error while socket()");        return EXIT_FAILURE;    }    // Set Option for the Socket for rapid iterative binding to adress    int option = 1;    setsockopt(rndvz_fd, SOL_SOCKET, SO_REUSEADDR, (const void *) &option, sizeof(int));    //  Struct for the connection between client and server    struct sockaddr_in server;    //  Define to use ipv4    server.sin_family = AF_INET;    //  Define from which ip-address clients want to connect to server, any adress is allowed    server.sin_addr.s_addr = INADDR_ANY;    //  Define port number on which the client wants to connect    server.sin_port = htons(PORT_NUMBER);    /*  Bind an address to the socket     *  rndzvs_fd = socket file descriptor     *  addr = address struct for cast     *  len = length of the adress     */    int bnd_result = bind(rndvz_fd, (struct sockaddr *) &server, sizeof(server));    // Ask for return value of the function to check for error while binding => terminate program if error    if(bnd_result < 0){        perror("Error while bind()");        return EXIT_FAILURE;    }    //  Max. capacity for clients communicating with the server    const int max_clients = 5;    /*  Bring socket to listen for incoming connections and put then in a queue     *  rndzvs_fd = socket file descriptor     *  n = maximum number of clients     *     */    int lstn_result = listen(rndvz_fd, max_clients);    // Check return value for error    if (lstn_result < 0 ){        perror("Error while listen()");        return EXIT_FAILURE;    }    while (LOOP) {        /*  Accept incoming connection request of the client        *        *  cnnct_fd = socket file descriptor        *  addr = source adress        *  addr_len = size of source adress        */        int cnnct_fd = accept(rndvz_fd, (struct sockaddr *) &client, &client_len);        if(cnnct_fd < 0) {            perror("Error while accept()");            return EXIT_FAILURE;        }        // return value of fork is 0 if child process, parent process has the value > 0 (process ID of newly created child        if(fork() == 0){            clientHandler(cnnct_fd);            //For terminating the child            exit(0);        }        //Close the accept to the socket that is given to child        close(cnnct_fd);        //shared memory delet        //shmdt(sharMem);        //shmctl(id, IPC_RMID, 0);    }}