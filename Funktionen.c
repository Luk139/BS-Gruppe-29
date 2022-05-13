#include <stdio.h>
#include <string.h>

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



int del(char* key);



int main() {

    char keyName1[LENGHT] = {"ABC1"};
    char keyValue1[LENGHT] = {" O123Z"};

    char keyName2[LENGHT] = {"DEF2"};
    char keyValue2[LENGHT] = {" 4567Y"};

    put(keyName1, keyValue1);
    put(keyName2, keyValue2);

    /*printf("\n%s", keyValueStore[0].keyName);
    printf("%s", keyValueStore[0].keyValue);
    printf("\n%s", keyValueStore[1].keyName);
    printf("%s", keyValueStore[1].keyValue);
    printf("\n%s", keyValueStore[2].keyName);
    printf("%s", keyValueStore[2].keyValue);*/

    char keyName3[LENGHT] = {"ABC1"};
    char keyValue3[LENGHT] = {" 78910X"};

    put(keyName3, keyValue3);

    /*printf("\n%s", keyValueStore[0].keyName);
    printf("%s", keyValueStore[0].keyValue);
    printf("\n%s", keyValueStore[1].keyName);
    printf("%s", keyValueStore[1].keyValue);
    printf("\n%s", keyValueStore[2].keyName);
    printf("%s", keyValueStore[2].keyValue);*/

    //printf("\n %s", get("CDF"));

    printf("\n %s", get("DEF2"));
    del("DEF2");
    printf("\n %s", get("DEF2"));
    del("ASDIH");





    return 0;
}
