//
// Created by hani on 01/01/2020.
//

#include <regex>
#include "SetVariables.h"

SetVariables::SetVariables() {
    this->var_map = unordered_map<string, double>();
}

SetVariables *SetVariables::instance = 0;

//The getter checks if an instance already exists and if it doesn't, calls the constructor.
SetVariables *SetVariables::getSetVariables() {
    if (instance == 0) {
        instance = new SetVariables();
    }
    return instance;
}

//inserts a variable. checks if the variable name already exists, and then updates it.
void SetVariables::addVariable(string str1, double value1) {
    if (var_map.find(str1) != var_map.end()) {
        var_map[str1] = value1;
    } else {
        this->var_map.insert({str1, value1});
    }
}

unordered_map<string, double> SetVariables::getVarMap() {
    return this->var_map;
}
