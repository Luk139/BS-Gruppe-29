#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <string.h>

#define LENGTH 127


//TODO comment precisely and refactor

static const unsigned int port_number = 5678;

//arguments for the client, client id and
int main(int argc, char **argv){

    //check if the two necessary arguments are given to the client
    if(argc != 2){
        fprintf(stderr, "usage: %s <CLIENT_ID\n", argv[0]);
        return EXIT_FAILURE;
    }

    int client_fd = -1;
    int val_read = -1;
    int val_connect = -1;
    int val_close = -1;

    struct sockaddr_in serv_addr;
    char buffer[LENGTH];
    char basic_content[LENGTH];

    memset(buffer, 0, sizeof(buffer));
    memset(basic_content, 0, sizeof(basic_content));

    strcpy(basic_content, "client with client-ID \"");
    strncat(basic_content, argv[1], strlen(argv[1]));

    client_fd = socket(AF_INET, SOCK_STREAM, 0);

    if(client_fd <0){
        perror("Error while socket()");
        return EXIT_FAILURE;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port_number);

    /*
     * fd = client socket file descriptor
     * addr = address to use
     * len = size of address
     */
    connect(client_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));

    if(val_connect < 0){
        perror("Error while connect()");
        return EXIT_FAILURE;
    }

    puts("sending message was successfull");
    //answer
    bzero(buffer, LENGTH);

    val_read = read(client_fd, buffer, LENGTH);
    if(val_read < 0){
        perror("Error while read()");
        return EXIT_FAILURE;
    }

    //print the string
    puts(buffer);

    val_close = close(client_fd);

    if(val_close < 0){
        perror("Error while close()");
        return EXIT_FAILURE;

    }



    return EXIT_SUCCESS;

}