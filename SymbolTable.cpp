//
// Created by hani on 30/12/2019.
//

#include "SymbolTable.h"

SymbolTable::SymbolTable() {
    this->symbol_table=unordered_map<string,Var*>();
}
SymbolTable *SymbolTable::instance=0;

//the getter of this class checks if there's already an instance, else it creates one and returns it.
SymbolTable* SymbolTable::getSymbolTable() {
    if (instance == 0) {
        instance = new SymbolTable();
    }
    return instance;
}

//adds a var by its name.
void SymbolTable::addSymbol(string name, Var *var) {
  this->symbol_table.insert({name, var});
}

//looks for a variable by its name in the map. if there's no var with that name, returns a nullptr.
Var* SymbolTable::findVar(string s){
    auto iter = this->symbol_table.find(s);
    if (iter != this->symbol_table.end()) {
        return iter->second;
    } else {
        return nullptr;
    }
}
