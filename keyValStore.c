#include "keyValStore.h" //Hilfsfunktion Ausgabe ptrkeyvalvoid ausgabeKeyValStore(Key *ptrkeyval){     for(int i=0; i < STORESIZE; i++){        if((ptrkeyval[i].keyName[0] != '\0')) {            printf("%s\n", ptrkeyval[i].keyName);            printf("%s\t", ptrkeyval[i].keyValue);        }    }}int search(char* key, Key *ptrkeyval){    for(int i=0; i < STORESIZE; i++){        /*if(ptrkeyval[i].keyName != NULL){            if(strcmp (key, ptrkeyval[i].keyName) == 0){*/            if(strcmp (key, ptrkeyval[i].keyName) == 0){                return i;            }    }    return -1;}int put(char* key, char* value, Key *ptrkeyval){    int i = search(key, ptrkeyval);    if(i >= 0){        strcpy(ptrkeyval[i].keyValue,value);        return 0;    }    i = search("", ptrkeyval);    if(i >= 0){        strcpy(ptrkeyval[i].keyValue,value);        strcpy(ptrkeyval[i].keyName,key);        return 0;    }        return 0;}char* get(char* key, Key *ptrkeyval){    //printf("keyvalue vor dem search in get: %s \n", ptrkeyval[0].keyValue);    int i = search(key, ptrkeyval);    //printf("keyvalue nach dem search in get: %s \n", ptrkeyval[0].keyValue);    if(i >= 0){        //char stringReturn[LENGTH];        //strcpy(stringReturn, ptrkeyval[i].keyValue);        return ptrkeyval[i].keyValue;    }    return "key non existent\n";}int del(char* key, Key *ptrkeyval){    int i = search(key, ptrkeyval);    if(i >= 0){        ptrkeyval[i].keyName[0] = '\0';        return 0;    }    return -1;}