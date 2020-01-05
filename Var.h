//
// Created by noa on 23/12/2019.
//
#pragma once
#ifndef EX3__VAR_H_
#define EX3__VAR_H_

//#include <string>
#include "MapHolder.h"
#include "SetVariables.h"
using namespace std;

class Var : public Command {
public:
    std::string name;
    std::string sim;
    double value;
    bool direction;
    void setValue(double value);
    Var(std::string n, std::string s, bool d) ;


    int execute(int i);
};

#endif //EX3__VAR_H_
