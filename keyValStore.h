#include "main.h"

int search(char* key, Key *ptrkeyval);
int put(char* key, char* value, int pos, Key *ptrkeyval);
char* get(char* key, Key *ptrkeyval);
int del(char* key, Key *ptrkeyval);
void ausgabeKeyValStore(Key *ptrkeyval);
