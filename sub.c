#include "sub.h"



#define SIZE 25
#define LENGTH 100


void majorError (const char *errMessage){
    perror(errMessage);
    exit(EXIT_FAILURE);
}

void input(char * userInput, int cnnct_fd){


    // Get rid of the trash at the end of the telnet message
    char delimiter1[] = "\r";
    char *ptr;
    ptr = strtok(userInput, delimiter1);

    // /x20 delimiter is a space
    char delimiter[] = "\x20";

    //Array for storing the prts of the string [0] will store the value, [1] for the key and [2] for the value
    char arr[SIZE][LENGTH];
    int i = 0;
    int sendBytes = 0;



    //First Part, should be the commands GET, PUT, DEL
    ptr = strtok(ptr, delimiter);
    sendBytes = strlen(ptr);


    while (ptr != NULL) {
        strcpy(arr[i], ptr);
        write(cnnct_fd, ptr, sendBytes);
        //add : to the message to the client
        // if put value skip last :
        if (i <= 1) {
            write(cnnct_fd, ":", 1);
        }
        // create next
        ptr = strtok(NULL, delimiter);

        //Dont set the integer to NULL in the last execution
        if (ptr != NULL) {
            sendBytes = strlen(ptr);
        }
        i++;
    }

    char *wrongInput = "Please use a proper value.\n";
    int wrngInptLength = strlen(wrongInput);





    char *value;
    //Check the Input for a Command GET, PUT, DEL


    if (strcasecmp(arr[0], "BEG") == 0) {
        exclusiveModeEnter();
        //sharMem->exclusive = true;
        write(cnnct_fd, "\n", 2);
    }

    else if (strcasecmp(arr[0], "END") == 0) {
        exclusiveModeLeave();
        //sharMem->exclusive = false;
        write(cnnct_fd, "\n", 2);
    }

    else if (strcasecmp(arr[0], "GET") == 0) {
        //printf("%d", sharMem->exclusive);
        value = get(arr[1], sharMem);
        write(cnnct_fd, value, strlen(value));
        write(cnnct_fd, "\n", 2);
    }

    else if (strcasecmp(arr[0], "PUT") == 0) {
        put(arr[1], arr[2], sharMem);
        write(cnnct_fd, "\n", 2);
        //printf("positions counter: %d\n", pos);
    }

    else if (strcasecmp(arr[0], "DEL") == 0) {
        int is = del(arr[1], sharMem);
        if (is >= 0) {
            write(cnnct_fd, "key_deleted\n", 12);
        } else {
            write(cnnct_fd, "key_nonexistent\n", 16);
        }
    }

    else if (strcasecmp(arr[0], "SUB") == 0) {
        subscribe(arr[1]);
        value = get(arr[1], sharMem);
        write(cnnct_fd, value, strlen(value));
        write(cnnct_fd, "\n", 2);
    }

    else if (strcasecmp(arr[0], "ALL") == 0) {
        ausgabeKeyValStore(sharMem);
    }

    else {
        write(cnnct_fd, wrongInput, wrngInptLength);
    }


}