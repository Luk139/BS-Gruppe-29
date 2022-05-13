#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>


#define LENGTH 100
#define SIZE 50

int counter = 0;



typedef struct Key_{

    char * keyName;
    char * keyVal;

}Key;

Key* keyValueStore[SIZE];




int put(char * key, char * value){

        Key handover;
        handover.keyName = key;
        handover.keyVal = value;
        keyValueStore[counter] = &handover;
        /*
        keyValueStore[counter]->keyName = key;
        keyValueStore[counter]->keyVal = value;
        */
        counter++;




    return -1;
}


/*
int get(char * key[], char * res[]){

    printf("%s", keyValueStore[0]->keyName );
    printf("%s", keyValueStore[0]->keyVal );

    return -1;
};
*/


int del(char * key[]){

    return -1;
};

int main(){

    char string1[LENGTH][LENGTH] = {"name1", "name2", "name3"};
    char string2[LENGTH][LENGTH] = {"wert1", "wert2", "wert3"};


    put(string1[counter],string2[counter]);
    printf("%s", keyValueStore[counter - 1]->keyName );
    printf("%s", keyValueStore[counter - 1]->keyVal );
    put(string1[counter],string2[counter]);
    printf("%s", keyValueStore[counter - 1]->keyName );
    printf("%s", keyValueStore[counter - 1]->keyVal );
    put(string1[counter],string2[counter]);
    printf("%s", keyValueStore[counter - 1]->keyName );
    printf("%s", keyValueStore[counter - 1]->keyVal );
    return 0;
}