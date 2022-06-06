//
// Created by Tobias Mai on 06.06.22.
//

#ifndef BS_GRUPPE_29_KEYVALSTORE_H
#define BS_GRUPPE_29_KEYVALSTORE_H


#include "main.h"

#define LENGTH 100
#define STORESIZE 100

int search(char* key, Key *ptrkeyval);
int put(char* key, char* value, int pos, Key *ptrkeyval);
char* get(char* key, Key *ptrkeyval);
int del(char* key, Key *ptrkeyval);
void ausgabeKeyValStore(Key *ptrkeyval);





#endif //BS_GRUPPE_29_KEYVALSTORE_H
