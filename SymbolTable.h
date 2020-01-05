//
// Created by hani on 30/12/2019.
//
#pragma once
#ifndef EX3_SYMBOLTABLE_H
#define EX3_SYMBOLTABLE_H
#include <unordered_map>
#include <string>
#include "Var.h"

using namespace std;

/**
 * This class is a singleton - it keeps track of the variables names and all of their fields, and it is used
 * to update the var value.
 */
class SymbolTable {
private:
    static SymbolTable *instance;
  //the map of the string that connects to the variable and all its values.
    std::unordered_map<std::string, Var*> symbol_table;

public:
    SymbolTable();
    static SymbolTable *getSymbolTable();
  //returns the map of the string and its matching var.
    unordered_map<std::string,Var*> getSymbolMap(){
        return this->symbol_table;
    }
  //adds a variable
    void addSymbol(string name, Var* var);
    Var* findVar(string s);
};

#endif //EX3_SYMBOLTABLE_H
