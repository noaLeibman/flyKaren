//
// Created by noa on 23/12/2019.
//

#include "DefineVarCommand.h"

int DefineVarCommand::execute(int i) {
  mutex mutex_lock;
  vector<string> vec = MapHolder::getMapHolder()->getTokens();
  //var parameters
  string name = vec[i + 1];
  string direction = vec[i + 2];
  string sim = vec[i + 3];
  bool d;

  if (direction.compare("->") == 0) {
    d = true;
    sim = sim.substr(2, sim.length() - 3);
  } else if (direction.compare("<-") == 0) {
    d = false;
    sim = sim.substr(2, sim.length() - 3);
    //when there is no direction, there's "="
  } else {
    try {
      //interpret the expression that's after the "=" sign
      Interpreter* interpreter = new Interpreter();
      interpreter->setVarMap(SetVariables::getSetVariables()->getVarMap());
      Expression* e = interpreter->interpret(sim);
      double value = e->calculate();
      d = true;
      sim = "";
      SetVariables::getSetVariables()->addVariable(name, value);
      delete interpreter;
    } catch (char const* e) {
      cout<<e<<endl;
      return 4;
    }
  }
  //define new varianle
  Var *var = new Var(name, sim, d);
  //critical section
  mutex_lock.lock();

  SymbolTable::getSymbolTable()->addSymbol(name, var);
  //updating variables with direction "<-" in map
  if (!d) {
      this->vars_to_update[MapHolder::getMapHolder()->getIndexMap().find(sim)->second]=var;
    VarsToUpdate::getVarsToUpdate()->getVarsToUpdate()->setVarsToUpdate(this->vars_to_update);
  }
  mutex_lock.unlock();

  return 4;
}

DefineVarCommand::DefineVarCommand() {
    this->vars_to_update=unordered_map<int,Var*>();
}