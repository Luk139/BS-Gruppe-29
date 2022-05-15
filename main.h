#define LENGTH 100
typedef struct key_ {
    char keyName[LENGTH];
    char keyValue[LENGTH];
}Key;

extern Key *sharMem;