//
// Created by Tobias Mai on 06.06.22.
//

#include "transactions.h"
#include <stdbool.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>


bool exclusive = false;

// Initialize structs for Semaphore
struct sembuf enter = {.sem_num=0, .sem_op=-1, .sem_flg=SEM_UNDO};
struct sembuf leave = {.sem_num=0, .sem_op=1, .sem_flg=SEM_UNDO};
int semaphoreId;

void initializeShmSem(){


// Store the Semaphore ID
        semaphoreId = semget(IPC_PRIVATE, 1, IPC_CREAT | 0644);
        if (semaphoreId <0){
            majorError("semget()");
        }

        unsigned short initiateSpecs[1] = {1};
// If you need to set several semaphores
//    unsigned short initiateSpecs[2] = {1, 1};



/*  id = Identifier for the semaphoregrp
 *  nsem = Counter of the semaphore in the grp
 *  cmd = SETALL set values of the semaphore
 *  arg = Options for setall need to be of type array to set the values
 */

        int semaphoreCTL = semctl(semaphoreId, 1, SETALL, initiateSpecs);
        if (semaphoreCTL <0){
            perror("Error while semctl()");
            majorError("semget()");
        }




};





bool exclusiveMode(){

    if(!exclusive){
        semop(semaphoreId, &enter, 1); // Enter critical Zone
        exclusive = true;
        return true;
    }
    else{
        semop(semaphoreId, &leave, 1); // Leave critical Zone
        exclusive = false;
        return true;
    }

    return false;

}