//
// Created by Tobias Mai on 06.06.22.
//

#ifndef BS_GRUPPE_29_KEYVALSTORE_H
#define BS_GRUPPE_29_KEYVALSTORE_H

#define LENGTH 100
#define STORESIZE 100

typedef struct key_ {
    char keyName[LENGTH];
    char keyValue[LENGTH];
    int subscribers[LENGTH];
}Key;

#include "main.h"
#include <stdio.h>
#include <string.h>


int search(char* key, Key *ptrkeyval);
int put(char* key, char* value, Key *ptrkeyval);
char* get(char* key, Key *ptrkeyval);
int del(char* key, Key *ptrkeyval);
void ausgabeKeyValStore(Key *ptrkeyval);


#endif //BS_GRUPPE_29_KEYVALSTORE_H
