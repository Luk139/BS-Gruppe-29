//
// Created by Tobias Mai on 08.06.22.
//

#include "pubSub.h"


void subscribe (char *key)
{
    int subscriberIndex = -1;
    int index = search(key, sharMem);
    if (index == -1) {
        return;
    }

    for (int i = 0; i < LENGTH; i++) {
        if (sharMem[index].subscribers[i] == 0) {
            subscriberIndex = i;
            break;
        }
    }
    if (subscriberIndex == -1) {
        return;
    }

    sharMem[index].subscribers[subscriberIndex] = getpid();
}


void notify (char *command, int keyIndex, char *key, char *value)
{
    Notification notification;
    sprintf(notification.msg, "%s:%s:%s\n", command, key, value);

    for (int i = 0; i < LENGTH; i++) {
        int subscriberId = sharMem[keyIndex].subscribers[i];
        notification.subscriberId = subscriberId;

        if (subscriberId != 0 && subscriberId != getpid()) {
            msgsnd(messageQueueID, &notification, sizeof(Notification), 0);
        }
    }
}

void deleteSubscribers(){
    for (int i = 0; i < STORESIZE; i++) {
        for (int j = 0; j < LENGTH; j++) {
            if(getpid() == sharMem[i].subscribers[j]) {
                sharMem[i].subscribers[j] = 0;
            }
        }
    }
}