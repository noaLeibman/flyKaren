//
// Created by noa on 23/12/2019.
//

#include "Var.h"

int Var::execute(int i) {
  mutex mutex_lock;
  //this->mh = mh->getMapHolder();
  mutex_lock.lock();
  vector<string> vec = MapHolder::getMapHolder()->getTokens();
  Interpreter *varInterpreter = new Interpreter();
//  Interpreter *interpreter = MapHolder::getMapHolder()->getInterpreter();
  varInterpreter->setVarMap(SetVariables::getSetVariables()->getVarMap());
  //updating value
  string to_interpret = vec[i + 2];
  try {
    Expression *ex = varInterpreter->interpret(to_interpret);
    double val = ex->calculate();
    this->value = val;
    string var_str = this->name;
    var_str =var_str +"=";
    var_str=var_str+to_string(val);
    SetVariables::getSetVariables()->addVariable(this->name,this->value);
    varInterpreter->setVariables(var_str);
  } catch (char const* e) {
    cout<<e<<endl;
  }
  string command;
  command="set ";
  command = command+this->sim;
  command=command+" ";
  command=command+to_string(this->value)+"\n";
//  command=command+"\r\n";
  MapHolder::getMapHolder()->setStringToSend(command);
//  MapHolder::getMapHolder()->setStringFlag(1);
  mutex_lock.unlock();
  return 3;
}

Var::Var(std::string n, std::string s, bool d) {
this->name = n;
this->sim = s;
this->direction = d;
}
void Var::setValue(double value){
    this->value=value;
//    Interpreter *interpreter = MapHolder::getMapHolder()->getInterpreter();

//    string var_str = this->name;
//    var_str = var_str + "=";
//    var_str = var_str + to_string(value);
    try {
        SetVariables::getSetVariables()->addVariable(this->name,this->value);
//        interpreter->setVariables(var_str);
    }
    catch(char const* e){
        cout<<e<<endl;
    }

}