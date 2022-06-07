//
// Created by Tobias Mai on 06.06.22.
//

#ifndef BS_GRUPPE_29_MAIN_H
#define BS_GRUPPE_29_MAIN_H

#define LENGTH 100
typedef struct key_ {
    char keyName[LENGTH];
    char keyValue[LENGTH];
    bool exclusive;
}Key;

extern Key *sharMem;



#endif //BS_GRUPPE_29_MAIN_H
