#include <stdio.h>
#include <string.h>
#include "keyValStore.h"

#define LENGHT 100
#define SIZE 5


typedef struct key_ {
    char* keyName;
    char* keyValue;
}Key;


Key keyValueStore[SIZE];
int pos = 0;


int search(char* key){
    for(int i=0; i < SIZE; i++){
        if(keyValueStore[i].keyName != NULL){
            if(strcmp (key, keyValueStore[i].keyName) == 0){
                return i;
            }
        }
    }
    return -1;
}


int put(char* key, char* value){
    Key tempKey;
    tempKey.keyName = key;
    tempKey.keyValue = value;

    int i = search(key);
    if( i >= 0){
        keyValueStore[i] = tempKey;
        return 1;
    }else{
        keyValueStore[pos] = tempKey;
        pos++;
        return 0;
    }
}

char* get(char* key){
    int i = search(key);
    if(i >= 0){
        return keyValueStore[i].keyValue;
    }

    return "key non existent";
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