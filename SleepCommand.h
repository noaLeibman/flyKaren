//
// Created by hani on 23/12/2019.
//
#pragma once
#ifndef EX3_SLEEPCOMMAND_H
#define EX3_SLEEPCOMMAND_H

#include "MapHolder.h"

/**
 * This class is responsible for receiving a numerical value and sleeping the thread with the given value.
 */
class SleepCommand : public Command {
public:
  //the command execute function - receives the index of the current command and returns the index of advancement
  //for the parser
    int execute(int);
};


#endif //EX3_SLEEPCOMMAND_H
