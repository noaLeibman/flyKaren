//
// Created by noa on 25/12/2019.
//

#include "IfCommand.h"
#include "SymbolTable.h"

bool IfCommand::checkCondition(Expression *first, Expression *second, string op) {
    double epsilon = 0.001;
    double x = first->calculate();
    double y = second->calculate();
    double diff = x - y;
    //check condition by operator
    if (op.compare("==") == 0) {
        return ((diff < epsilon && diff > -epsilon));
    } else if (op.compare("!=") == 0) {
        return (diff > epsilon && diff < -epsilon);
    } else if (op.compare(">") == 0) {
        return diff > epsilon;
    } else if (op.compare("<") == 0) {
        return diff < -epsilon;
    } else if (op.compare(">=") == 0) {
        return diff >= epsilon;
    } else if (op.compare(">=") == 0) {
        return diff <= -epsilon;
    }
}

int IfCommand::execute(int i) {
    mutex mutex_lock;
    vector<string> vec = MapHolder::getMapHolder()->getTokens();
    //critical section
    mutex_lock.lock();
    Interpreter *interpreter = MapHolder::getMapHolder()->getInterpreter();
    interpreter->setVarMap(SetVariables::getSetVariables()->getVarMap());
    mutex_lock.unlock();
    Expression *first = interpreter->interpret(vec[i + 1]);
    string op = vec[i + 2];
    Expression *second = interpreter->interpret(vec[i + 3]);

    int j = i + 5;
    if (this->checkCondition(first, second, op)) {
      //executes all commands in scope
        while (vec[j].compare("}") != 0) {
            mutex_lock.lock();
            Command *currCommand = MapHolder::getMapHolder()->findCommand(vec[j]);
            Var *currvar = SymbolTable::getSymbolTable()->findVar(vec[j]);
            mutex_lock.unlock();
            if (currCommand != nullptr) {
                j += currCommand->execute(j);
            } else if (currvar != nullptr) {
                j += currvar->execute(j);
            }
        }
    }
    return j - i + 1;
}