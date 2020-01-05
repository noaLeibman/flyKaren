//
// Created by noa on 23/12/2019.
//
#pragma once
#ifndef EX3__DEFINEVARCOMMAND_H_
#define EX3__DEFINEVARCOMMAND_H_
#include "VarsToUpdate.h"
#include "SymbolTable.h"
#include "SetVariables.h"
#include <unordered_map>

using namespace std;

/*Make a new variable, executes when "Var" is read*/
class DefineVarCommand : public Command{
 private:
  //map of variables that should be updates from client
    unordered_map<int,Var*> vars_to_update;
 public:
  DefineVarCommand();
  int execute(int);
};

#endif //EX3__DEFINEVARCOMMAND_H_
