#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>


#define LENGTH 100
#define SIZE 50

<<<<<<< Updated upstream
int counter = 0;



typedef struct Key_{

    char * keyName;
    char * keyVal;

}Key;

Key* keyValueStore[SIZE];



=======
typedef struct key_ {
    char* keyName;
    char* keyValue;
}Key;

Key* keyValueStore[SIZE];

int search(char* key){
    // TODO probable error i seems to be responsible for key to get overwritten
    for(int i=0; i < SIZE; i++){
        if(keyValueStore[i]->keyName != NULL){
            if(strcmp (key, keyValueStore[i]->keyName) == 0){
                return i;
            }
        }
    }
    return -1;
}
>>>>>>> Stashed changes

int put(char * key, char * value){

<<<<<<< Updated upstream
        Key handover;
        handover.keyName = key;
        handover.keyVal = value;
        keyValueStore[counter] = &handover;
        /*
        keyValueStore[counter]->keyName = key;
        keyValueStore[counter]->keyVal = value;
        */
        counter++;



=======
int put(char* key, char* value, int pos){
    Key tempKey1 = {key, value}, *tempKey2 = &tempKey1;

    /*int i = search(key);
    if( i >= 0){
        keyValueStore[i] = &tempKey;
        return 1;
    }*/
    //else{
        keyValueStore[pos] = tempKey2;
        printf("nach dem put: %s \n", keyValueStore[0]->keyValue);
        return 0;
    //}
}

char* get(char* key){
    printf("vor dem search in get: %s \n", keyValueStore[0]->keyValue);
    int i = search(key);
    printf("nach dem search in get: %s \n", keyValueStore[0]->keyValue);

    if(i >= 0){
        //char stringReturn[LENGTH];
        //strcpy(stringReturn, keyValueStore[i]->keyValue);
        return   keyValueStore[i]->keyValue;
    }
>>>>>>> Stashed changes

    return -1;
}

<<<<<<< Updated upstream

/*
int get(char * key[], char * res[]){

    printf("%s", keyValueStore[0]->keyName );
    printf("%s", keyValueStore[0]->keyVal );
=======
//TODO: Key nachrücken
int del(char* key){
    int i = search(key);
    if(i >= 0){
        keyValueStore[i]->keyName = NULL;
        keyValueStore[i]->keyValue = NULL;
        return 0;
    }
>>>>>>> Stashed changes

    return -1;
};
*/


int del(char * key[]){

    return -1;
};

<<<<<<< Updated upstream
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
=======
//Hilfsfunktion Ausgabe keyValueStore
void ausgabeKeyValStore(){
    int j = 0;
    //keyValueStore[i].keyValue != NULL
    while(j <= 2){
        printf("%s\n", keyValueStore[j]->keyName);
        printf("%s\t", keyValueStore[j]->keyValue);

        j++;
    }
}

>>>>>>> Stashed changes
