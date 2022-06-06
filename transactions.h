#ifndef BS_GRUPPE_29_TRANSACTIONS_H
#define BS_GRUPPE_29_TRANSACTIONS_H
#include <stdbool.h>


extern bool exclusive;

bool exclusiveMode();
void initializeSem();
void semaphoreUp();
void semaphoreDown();
void closeSemaphore();


#endif //BS_GRUPPE_29_TRANSACTIONS_H
