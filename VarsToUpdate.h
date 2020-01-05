//
// Created by hani on 30/12/2019.
//
#pragma once
#ifndef EX3_VARSTOUPDATE_H
#define EX3_VARSTOUPDATE_H
#include "Var.h"
#include <unordered_map>

/**
 * This class is a singleton - it keeps track of the variables that need to by updated by the server.
 * Each var has its index given by the XML, so we know which value belongs to which var.
 */
class VarsToUpdate {
private:
    static VarsToUpdate *instance;
  //the map of the vars that need to be updated by the server.
    unordered_map<int, Var *> vars_to_update;
    VarsToUpdate();
 public:
    static VarsToUpdate *getVarsToUpdate();
  //sets the map from DefineVarCommand, which is where we know if there's a variable to update.
    void setVarsToUpdate(unordered_map<int,Var*> map);
    unordered_map<int,Var*>::iterator getBeginMap();
    unordered_map<int,Var*>::iterator getEndMap();
};


#endif //EX3_VARSTOUPDATE_H
