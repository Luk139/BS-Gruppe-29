//
// Created by Tobias Mai on 06.06.22.
//

#ifndef BS_GRUPPE_29_MAIN_H
#define BS_GRUPPE_29_MAIN_H
#include "transactions.h"
#include "keyValStore.h"
#include "sub.h"
#include "networkCommunication.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>


void initIPC();
void freeIPC();

extern Key *sharMem;
extern int messageQueueID;


#endif //BS_GRUPPE_29_MAIN_H
