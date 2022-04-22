#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <string.h>

#define LOOP 1
#define LENGTH 127
//  Look in "Docker Desktop" for opened ports on container
#define PORT_NUMBER 5678

int main(){

    //  Struct for the connection between client and server
    struct sockaddr_in address;

    //  Integer for length of the address
    int addr_length = sizeof(address);
    //  Filedescriptor(Rendezvous-Descriptor), integer for identifying the socket. Set to -1 so we dont get a "success" value by default.
    int rndzvs_fd = -1;
    //  Filedescriptor(Connection-Descriptor)
    int cnnct_fd = -1;
    //  Integer for return value of bind
    int bind_result = -1;
    //  Integer for return value of listen
    int lstn = -1;
    // integer for return value of read and number of transmitted bytes/characters
    int val_read = -1;
    // integer for return value of send
    int send_result = -1;
    //  Number of bytes the client has send
    int bytes_read;

    //  String buffer to send messages between server and client
    char buffer[LENGTH];
    // Strings to send messages to the client
    char answer[LENGTH][LENGTH] = {"Halli hallo!", "Muss muss und dir?" , "Sehr schön, man sieht sich!" , "Darauf antworte ich nicht."};
    // Selector int for answer
    int answr;

    //TODO Check whats going on here
    memset(buffer, 0, sizeof(buffer));

    /*  Creating the socket with ipv4 and tcp no further description for protocol needed so 0 is enough -> SOCK_STREAM uses tcp by default.
    *   AF_INET = ipv4
    *   SOCK_STREAM = tcp
    *   protocol 0 = default (For other protocols to expect when working with ip)
    */
     rndzvs_fd = socket(AF_INET, SOCK_STREAM, 0);

    //  Return value of rndzvs_fd is negative when an error occurs. And 0 when successfull. If it wasn't successfull terminate program
    if (rndzvs_fd <0){
        perror("Error while socket()");
        return EXIT_FAILURE;
    }

    //  Define to use ipv4
    address.sin_family = AF_INET;
    //  Define from which ip-address clients want to connect to server, any adress is allowed
    address.sin_addr.s_addr = INADDR_ANY;
    //  Define port number
    address.sin_port = htons(PORT_NUMBER);

    /*  Bind an address to the socket
     *  rndzvs_fd = socket file descriptor
     *  addr = address struct for cast
     *  len = length of the adress
     */
    bind_result = bind(rndzvs_fd, (struct sockaddr *) &address, sizeof(address));
    // Ask for return value of the function to check for error while binding => terminate program if error
    if(bind_result < 0){
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
    lstn = listen(rndzvs_fd, max_clients);
    // Check return value for error
    if (lstn < 0 ){
        perror("Error while listen()");
        return EXIT_FAILURE;
    }

    // continuous while loop for server to maintain its service until disruption with "str/ctrl + c"
    while(LOOP){

        /*  Accept incoming connection request
         *
         *  cnnct_fd = socket file descriptor
         *  addr = source adress
         *  addr_len = size of source adress
         */
        //TODO Nochmal alle sockets überprüfen höchstwahrscheinlich sind hier Dreher drin
        rndzvs_fd = accept(rndzvs_fd, (struct sockaddr *) &address, (socklen_t *) &addr_length);

        if(rndzvs_fd < 0) {
            perror("Error while accept()");
            return EXIT_FAILURE;
        }

        /*  cnnct_fd = connect file descriptor
         *  buf = text buffer
         *  nbytes = size of text buffer
         *
         */
        val_read = read(cnnct_fd, buffer, LENGTH);
        if(val_read < 0){
            perror("Error while read()");
            return EXIT_FAILURE;
        }

        // Store transmitted message, in a string, to stdout
        puts(buffer);

        // evaluate answer
        if(buffer == "Hallo."){
            answr = 0;
        }
        else if(buffer == "Wie geht's?"){
            answr = 1;

        }else if(buffer == "Joa, muss."){
            answr = 2;

        }
        else{
            answr = 3;

        }

        /*  Send answer to client via tcp (send requires tcp)
         *  cnnct_fd = socket file descriptor
         *  buf = text buffer
         *  n = length of the buffer
         *  flags = set if required, default value is 0 -> man send
         */
        send(cnnct_fd, answer[answr], strlen(answer[answr]),0);
        if(send_result < 0){
            perror("Error while send()");
            return EXIT_FAILURE;
        }

        // TODO
        memset(buffer, 0, sizeof(buffer));

        if(close(rndzvs_fd) < 0){
            perror("Error while close()");
            return EXIT_FAILURE;
        }
    }


    return EXIT_SUCCESS;


    //TODO Refactor everything for example header-files and so on...
    // Check how perror works => maybe it defines the error by the different errorcodes
}