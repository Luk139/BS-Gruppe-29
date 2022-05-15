#include <stdio.h>
#include <string.h>
#include "keyValStore.h"
#include "main.h"

#define LENGTH 100
#define SIZE 25




typedef struct key_ {
    char* keyName;
    char* keyValue;
}Key;

//Key* keyValueStore[SIZE];

/* //Hilfsfunktion Ausgabe keyValueStore
void ausgabeKeyValStore(){
    int j = 0;
    while(j <= 2){
        if((keyValueStore[j]->keyName != NULL)) {
            printf("%s\n", keyValueStore[j]->keyName);
            printf("%s\t", keyValueStore[j]->keyValue);
        }
        j++;
    }
} */

int search(char* key){
    // TODO probable error i seems to be responsible for key to get overwritten
    for(int i=0; i < SIZE; i++){
        if(keyValueStore[i].keyName != NULL){
            if(strcmp (key, keyValueStore[i].keyName) == 0){
        /*
        if((keyValueStore[i]->keyName != NULL) && (keyValueStore[i]->keyName[0] != '\0')){
            if(strcmp (&key, &keyValueStore[i]->keyName) == 0){
            */
                return i;
            }
        }
    }
    return -1;
}


int put(char* key, char* value, int pos){

    Key tempKey1 = {key, value}, *tempKey2 = &tempKey1;

    /*int i = search(key);
    if( i >= 0){
        keyValueStore[i] = &tempKey;
        return 1;
    }*/
    //else{
        keyValueStore[pos] = tempKey2;
        printf("keyvalue nach dem put: %s \n", keyValueStore[0]->keyValue);

        return 0;
    //}
}

char* get(char* key){
    printf("keyvalue vor dem search in get: %s \n", keyValueStore[0]->keyValue);

    int i = search(key);
    printf("keyvalue nach dem search in get: %s \n", keyValueStore[0]->keyValue);


    if(i >= 0){
        //char stringReturn[LENGTH];
        //strcpy(stringReturn, keyValueStore[i]->keyValue);
        return   keyValueStore[i]->keyValue;
    }

    return "key non existent\n";
}

//TODO: Key nachrücken
int del(char* key){
    int i = search(key);
    if(i >= 0){
        keyValueStore[i].keyName = NULL;
        keyValueStore[i].keyValue = NULL;      
        return 0;
    }

    return -1;
}