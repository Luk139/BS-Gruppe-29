#ifndef BS_GRUPPE_29_TRANSACTIONS_H
#define BS_GRUPPE_29_TRANSACTIONS_H
#include <stdbool.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdio.h>
#include "sub.h"

extern bool exclusive;

bool exclusiveModeEnter();
bool exclusiveModeLeave();
void initializeSem();
void semaphoreUp();
void semaphoreDown();
void closeSemaphore();


#endif //BS_GRUPPE_29_TRANSACTIONS_H
