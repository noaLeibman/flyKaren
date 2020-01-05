//
// Created by noa on 25/12/2019.
//
#pragma once
#ifndef EX3__WHILECOMMAND_H_
#define EX3__WHILECOMMAND_H_

#include "MapHolder.h"
#include "ConditionCommand.h"
#include "SymbolTable.h"

class WhileCommand : public ConditionCommand {
public:
    int execute(int i);
  //returns true if the expression "first-op-second" is correct, false otherwise
    bool checkCondition(Expression *first, Expression *second, string op);
};

#endif //EX3__WHILECOMMAND_H_
