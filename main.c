#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>


#define LOOP 1
#define LENGTH 127
#define PORT_NUMBER 4711

int main(){

    //Struct for the connection between Client and Server
    struct sockaddr_in address;

    //Integer for length of the address
    int addr_length = sizeof(address);

    //Filedescriptor(Rendezvous-Descriptor), integer for identifying the socket.
    int rndzvs_fd;
    //Filedescriptor(Connection-Descriptor)
    int cnnct_fd;
    //Integer for return value of bind
    int bind_result;
    //Number of bytes the client has send
    int bytes_read;

    //String buffer to send Messages between Server and Client
    char buffer[LENGTH];
    memset(buffer, 0, sizeof(buffer));

    //Creating the socket with ipv4 and tcp no further description for protocol needed so 0 is enough -> SOCK_STREAM uses tcp by default.
    rndzvs_fd = socket(AF_INET, SOCK_STREAM, 0);

    //Return value of rndzvs_fd is negative when an error occurs.
    if (rndzvs_fd <0){
        fprintf(stderr, "error while creating socket\n");
        return EXIT_FAILURE;
    }

    //Define to use ipv4
    address.sin_family = AF_INET;
    //Define from which ip-address clients want to connect to server, any adress is allowed
    address.sin_addr.s_addr = INADDR_ANY;
    //Define port number
    address.sin_port = htons(PORT_NUMBER);

    //Bind an address to the socket
    bind_result = bind(rndzvs_fd, (struct sockaddr *) &address, sizeof(address));
    if(bind_result < 0){
        fprintf(stderr, "error when binding socket\n");
        return EXIT_FAILURE;
    }

    const int max_clients = 4;

    //Bring socket to listen for incoming connections
    int lstn = listen(rndzvs_fd, max_clients);
    if (lstn < 0 ){
        fprintf(stderr, "error when socket should set to listen\n");
        return EXIT_FAILURE;
    }

    while(LOOP){


        rndzvs_fd = accept(cnnct_fd, (struct sockaddr *) &address, (socklen_t *) &addr_length);

        if(rndzvs_fd < 0) {
            fprintf(stderr, "error when socket should set to listen\n");
            return EXIT_FAILURE;
        }


        //TODO hier weiter
        //reading bytes the client has send
        bytes_read = read(cnnct_fd, , BUFSIZE);
    }


    return EXIT_SUCCESS;
}