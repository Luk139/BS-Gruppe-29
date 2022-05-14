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


Key keyValueStore[SIZE];


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


int put(char* key, char* value, int pos){
    Key tempKey;
    tempKey.keyName = key;
    tempKey.keyValue = value;




    int i = search(key);
    if( i >= 0){
        keyValueStore[i] = tempKey;
        return 1;
    }
    else{
        keyValueStore[pos] = tempKey;
        return 0;
    }
}

char* get(char* key){
    if(search(key) >= 0){
        int i = search(key);
        char stringReturn[LENGTH];
        strcpy(stringReturn, keyValueStore[i].keyValue);
        return   stringReturn;
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

//Hilfsfunktion Ausgabe keyValueStore
void ausgabeKeyValStore(){
    int j = 0;
    //keyValueStore[i].keyValue != NULL
    while(j <= 2){
        printf("%s\n", keyValueStore[j].keyName);
        printf("%s\t", keyValueStore[j].keyValue);

        j++;
    }


}