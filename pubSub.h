//
// Created by Tobias Mai on 08.06.22.
//

#ifndef BS_GRUPPE_29_PUBSUB_H
#define BS_GRUPPE_29_PUBSUB_H

#include "keyValStore.h"

typedef struct Notification_struct {
    long subscriberId;
    // len(command + key + value + 2*":" + '\0')
    char msg[LENGTH*2 + 6]
} Notification;


void subscribe (char *key);
void notify (char *command, int keyIndex, char *key, char *value);
void deleteSubscribers();


#endif BS_GRUPPE_29_PUBSUB_H
