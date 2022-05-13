#include <stdio.h>

#define LENGHT 100
#define SIZE 5


typedef struct key_ {
    char* keyName;
    char* keyValue;
}Key;

Key key1 = {"key1", "abc123"};
Key key2 = {"key2", "def456"};
Key key3 = {"key3", "hij789"};

Key keyValueStore[SIZE];



int put(char* key, char* value){
    Key tempKey;
    tempKey.keyName = key;
    tempKey.keyValue = value;

    int pos = 0;
    for(int i=0; i < SIZE; i++){
        if(i == pos){
            keyValueStore[i] = tempKey;
        }
    }

    return 1;
}


int get(char* key, char* res);


int del(char* key);



int main() {

    /*keyValueStore[0] = key1;
    printf("%s", keyValueStore[0].keyName);
    printf("%s", keyValueStore[0].keyValue);*/

    char keyName[LENGHT] = {"A"};
    char keyValue[LENGHT] = {"B"};

    put(keyName, keyValue);

    printf("%s", keyValueStore[0].keyName);
    printf("%s", keyValueStore[0].keyValue);

    return 0;
}
