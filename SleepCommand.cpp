//
// Created by hani on 23/12/2019.
//

#include "SleepCommand.h"
#include <chrono>
#include <thread>
#include "SetVariables.h"

int SleepCommand::execute(int i) {
  //since the value given can be an expression that needs to be interpreted, we send it to an interpreter,
  //and then sleep by the calculated value.
    std::vector<string> tokens = MapHolder::getMapHolder()->getTokens();
    Interpreter *sleepInterpreter = new Interpreter();
    sleepInterpreter->setVarMap(SetVariables::getSetVariables()->getVarMap());
    Expression* ex = sleepInterpreter->interpret(tokens[i + 1]);
    int timeToSleep = ex->calculate();
    std::this_thread::sleep_for(std::chrono::milliseconds(timeToSleep));
    delete sleepInterpreter;
    return 2;
}