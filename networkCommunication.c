//
// Created by Tobias Mai on 07.06.22.
//

#include "networkCommunication.h"

#define FOREVER while(1)
#define BUFSIZE 1024 // Size of the buffer

int subscriberPid;

int clientHandler(int cnnct_fd) {
    int read_bytes;
    char userInput[BUFSIZE];

    FOREVER{

        // read the bytes from the client
        read_bytes = read(cnnct_fd, userInput, BUFSIZE);
        if (read_bytes < 0) {
            perror("Error while read()");
            return EXIT_FAILURE;
        }
        // Skip loop when client isn't stopped properly prevent sending 0 bytes|| Quit
        if (read_bytes == 0 || strncmp("QUIT", userInput, 4) == 0) {
            printf("Server Exit...\n");
            deleteSubscribers();
            exit(0);
        }

        if(!exclusive){
            semaphoreDown();
        }
        input(userInput, cnnct_fd);
        if(!exclusive) {
            semaphoreUp();
        }

        printf("sending back the %d bytes I received...\n", read_bytes);
    }

}

void parentLoop(int rndvz_fd){

    while (true) {


        /*  Accept incoming connection request of the client
        *
        *  cnnct_fd = socket file descriptor
        *  addr = source adress
        *  addr_len = size of source adress
        */
        //  Struct for the connection between client and server
        struct sockaddr_in client;
        //Length of the Client-Data
        socklen_t client_len = sizeof(client);
        int cnnct_fd = accept(rndvz_fd, (struct sockaddr *) &client, &client_len);
        if(cnnct_fd < 0) {
            majorError("Error while accept()");
        }

        // return value of fork is 0 if child process, parent process has the value > 0 (process ID of newly created child)
        if(fork() == 0){

            // Subscriber Process
            if (fork() == 0) {
                //Kills the child if parent dies
                prctl(PR_SET_PDEATHSIG, SIGTERM);
                Notification notification;
                while (1) {
                    // Waits for pid from another client and sends message if there is one in the queue
                    msgrcv(messageQueueID, &notification, sizeof(Notification), getppid(), 0);
                    write(cnnct_fd, notification.msg, strlen(notification.msg));
                }
                exit(0);
            }

            clientHandler(cnnct_fd);
            //For terminating the child
            exit(0);
        }

        //Close the accept to the socket that is given to child
        close(cnnct_fd);

    }
}

void subscriberAction(){

    while(1){




    }




}