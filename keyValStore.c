#include <stdio.h>
#include <string.h>
#include "keyValStore.h"


#define LENGTH 100
#define SIZE 25

//use(*ptrkeyval);



//Key* ptrkeyval[SIZE];

 //Hilfsfunktion Ausgabe ptrkeyval
void ausgabeKeyValStore(Key *ptrkeyval){
    int j = 0;
    while(j <= 2){
        if((ptrkeyval[j].keyName != NULL)) {
            printf("%s\n", ptrkeyval[j].keyName);
            printf("%s\t", ptrkeyval[j].keyValue);
        }
        j++;
    }
}

int search(char* key, Key *ptrkeyval){
    // TODO probable error i seems to be responsible for key to get overwritten
    for(int i=0; i < SIZE; i++){
        /*if(ptrkeyval[i].keyName != NULL){
            if(strcmp (key, ptrkeyval[i].keyName) == 0){*/

        if((ptrkeyval[i].keyName != NULL) && (ptrkeyval[i].keyName[0] != '\0')){
            if(strcmp (&key, &ptrkeyval[i].keyName) == 0){

                return i;
            }
        }
    }
    return -1;
}


int put(char* key, char* value, int pos, Key *ptrkeyval){
    Key tempKey1 = {key, value}, *tempKey2 = &tempKey1;

    /*int i = search(key);
    if( i >= 0){
        ptrkeyval[i] = &tempKey;
        return 1;
    }*/
    //else{
        ptrkeyval[pos] = *tempKey2;
        printf("keyvalue nach dem put: %s \n", ptrkeyval[0].keyValue);

        return 0;
    //}
}

char* get(char* key, Key *ptrkeyval){
    printf("keyvalue vor dem search in get: %s \n", ptrkeyval[0].keyValue);

    int i = search(key, ptrkeyval);
    printf("keyvalue nach dem search in get: %s \n", ptrkeyval[0].keyValue);


    if(i >= 0){
        //char stringReturn[LENGTH];
        //strcpy(stringReturn, ptrkeyval[i].keyValue);
        return   ptrkeyval[i].keyValue;
    }

    return "key non existent\n";
}

//TODO: Key nachrücken
int del(char* key, Key *ptrkeyval){
    int i = search(key, ptrkeyval);
    if(i >= 0){
        ptrkeyval[i].keyName = '\0';
        ptrkeyval[i].keyValue = '\0';
        return 0;
    }

    return -1;
}