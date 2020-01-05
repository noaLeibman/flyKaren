//
// Created by hani on 23/12/2019.
//
#pragma once
#ifndef EX3_PRINTCOMMAND_H
#define EX3_PRINTCOMMAND_H
#include "MapHolder.h"

/**
 * This command prints to the console a given string or values that need to be interpreted.
 */
class PrintCommand : public Command {
private:
    MapHolder *map;
public:
    PrintCommand();
  //the command execute function - receives the index of the current command and returns the index of advancement
  //for the parser
    int execute(int i);
    virtual ~PrintCommand();
};


#endif //EX3_PRINTCOMMAND_H
