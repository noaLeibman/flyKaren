//
// Created by noa on 25/12/2019.
//
#pragma once
#ifndef EX3__CONDITIONCOMMAND_H_
#define EX3__CONDITIONCOMMAND_H_
#include "MapHolder.h"

using namespace std;

/*Base class for If and While commands*/
class ConditionCommand : public Command {
public:
  //vector of all the commands in the condition scope
    vector<Command*> commands;
};


#endif //EX3__CONDITIONCOMMAND_H_
