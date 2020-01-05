//
// Created by hani on 01/01/2020.
//
#pragma once
#ifndef EX3_SETVARIABLES_H
#define EX3_SETVARIABLES_H
#include <unordered_map>
#include <string>

using namespace std;

/**
 * This class is a singleton - it keeps track of the variables and their values, and it is used
 * to update the var and the interpreter calculates by it.
 */
class SetVariables {
private:
    static SetVariables *instance;
  //the map of the name of the variable name and the value.
    std:: unordered_map<std::string, double> var_map;
    SetVariables();
 public:
  //returns singelton instance
  static SetVariables *getSetVariables();
  //adds a variable by its name and its current value. Updates the value if the variable already exists.
  void addVariable(string s,double value);
  //returns the variable map
    unordered_map<string,double> getVarMap();
};



#endif //EX3_SETVARIABLES_H
