/*
 *  Echo-Server
 *
 *
 */

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include "main.h"
#include "keyValStore.h"

#define LOOP 1
#define BUFSIZE 1024 // Size of the buffer
//  Opened Ports in the Docker Container, or whatelse is used for the host-system
#define PORT_NUMBER 5678
// Port for running on mac itself
//#define PORT_NUMBER 4711
//<<<<<<< Updated upstream
//=======
#define LENGTH 100
#define SIZE 25




// Storing the Index of the keyValueStore
int pos = 0;


//>>>>>>> Stashed changes

int main(){


//<<<<<<< Updated upstream
//=======
    typedef struct key_ {
        char* keyName;
        char* keyValue;
    }Key;


    Key keyValueStore[SIZE];


    // id für shared Memory Segment
    //*sharMem zum verändern von Werten im Shared Memory
    int id, *sharMem;
    id = shmget(IPC_PRIVATE, SEGSIZE, IPC_CREAT|0600);

    sharMem = (int *)shmat(id, 0, 0);
    *sharMem = 0;








//>>>>>>> Stashed changes
    //File-Descriptor Rendezvous und Connect
    int rndvz_fd;
    int cnnct_fd;

    //  Struct for the connection between client and server
    struct sockaddr_in client;
    //Length of the Client-Data
    socklen_t client_len;
    // Counter for send Bytes from the Client
    int read_bytes;
    // Char-Array for Messages from the Client to the Server
    char in[BUFSIZE];

    /*  Creating the socket with ipv4 and tcp no further description for protocol needed so 0 is enough -> SOCK_STREAM uses tcp by default.
*   AF_INET = ipv4
*   SOCK_STREAM = tcp
*   protocol 0 = default (For other protocols to expect when working with ip)
*/
    rndvz_fd = socket(AF_INET, SOCK_STREAM, 0);

    //  Return value of rndzvs_fd is negative when an error occurs. And 0 when successfull. If it wasn't successfull terminate program
    if (rndvz_fd <0){
        perror("Error while socket()");
        return EXIT_FAILURE;
    }

    // Set Option for the Socket for rapid iterative binding to adress
    int option = 1;
    setsockopt(rndvz_fd, SOL_SOCKET, SO_REUSEADDR, (const void *) &option, sizeof(int));

    //  Struct for the connection between client and server
    struct sockaddr_in server;
    //  Define to use ipv4
    server.sin_family = AF_INET;
    //  Define from which ip-address clients want to connect to server, any adress is allowed
    server.sin_addr.s_addr = INADDR_ANY;
    //  Define port number on which the client wants to connect
    server.sin_port = htons(PORT_NUMBER);

    /*  Bind an address to the socket
     *  rndzvs_fd = socket file descriptor
     *  addr = address struct for cast
     *  len = length of the adress
     */
    int bnd_result = bind(rndvz_fd, (struct sockaddr *) &server, sizeof(server));
    // Ask for return value of the function to check for error while binding => terminate program if error
    if(bnd_result < 0){
        perror("Error while bind()");
        return EXIT_FAILURE;
    }

    //  Max. capacity for clients communicating with the server
    const int max_clients = 5;

    /*  Bring socket to listen for incoming connections
     *  rndzvs_fd = socket file descriptor
     *  n = maximum number of clients
     *
     */
    int lstn_result = listen(rndvz_fd, max_clients);
    // Check return value for error
    if (lstn_result < 0 ){
        perror("Error while listen()");
        return EXIT_FAILURE;
    }


    while (LOOP) {

        /*  Accept incoming connection request of the client
        *
        *  cnnct_fd = socket file descriptor
        *  addr = source adress
        *  addr_len = size of source adress
        */
        cnnct_fd = accept(rndvz_fd, (struct sockaddr *) &client, &client_len);
        if(cnnct_fd < 0) {
            perror("Error while accept()");
            return EXIT_FAILURE;
        }


        // read the bytes from the client
        read_bytes = read(cnnct_fd, in, BUFSIZE);
        if(read_bytes < 0){
            perror("Error while read()");
            return EXIT_FAILURE;
        }
        // Sending back data as long the client keeps sending some
        while (read_bytes > 0) {
            printf("sending back the %d bytes I received...\n", read_bytes);

            write(cnnct_fd, in, read_bytes);
            read_bytes = read(cnnct_fd, in, BUFSIZE);

        }
        close(cnnct_fd);
//<<<<<<< Updated upstream
//=======

        //shared memory delet
        //shmdt(sharMem);
        //shmctl(id, IPC_RMID, 0);
//>>>>>>> Stashed changes
    }

    close(read_bytes);








}