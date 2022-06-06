#include <stdio.h>
#include <stdlib.h>

void majorError (const char *errMessage){
    perror(errMessage);
    exit(EXIT_FAILURE);
}