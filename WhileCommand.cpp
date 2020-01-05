//
// Created by noa on 25/12/2019.
//

#include "WhileCommand.h"
#include "SymbolTable.h"
#include "SetVariables.h"

bool WhileCommand::checkCondition(Expression *first, Expression *second, string op) {
    double epsilon = 0.001;
    double x, y;
    try {
        x = first->calculate();
        y = second->calculate();
    } catch (char const *e) {
        cout << e << endl;
    }
    double diff = x - y;
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
    } else if (op.compare("<=") == 0) {
        return diff <= -epsilon;
    }
}

int WhileCommand::execute(int i) {
    mutex mutex_lock;
    vector<string> vec = MapHolder::getMapHolder()->getTokens();
    //critical section
    mutex_lock.lock();
    Interpreter *whileInterpreter = new Interpreter();
  try {
    whileInterpreter->setVarMap(SetVariables::getSetVariables()->getVarMap());
    Expression *first = whileInterpreter->interpret(vec[i + 1]);
    string op = vec[i + 2];
    Expression *second = whileInterpreter->interpret(vec[i + 3]);
    mutex_lock.unlock();
    int j = i + 5;

    //this loop creates commands vector, so we can execute it many times
    if (this->checkCondition(first, second, op)) {
      while (vec[j].compare("}") != 0) {
        mutex_lock.lock();
        Var *currvar = SymbolTable::getSymbolTable()->findVar(vec[j]);
        Command *c1 = MapHolder::getMapHolder()->findCommand(vec[j]);
        if (c1 != nullptr) {
          this->commands.push_back(c1);
          j += 2;
        } else if (currvar != nullptr) {
          this->commands.push_back(currvar);
          j++;
        } else {
          j++;
        }
        mutex_lock.unlock();
      }

      //this loop executes all commands until condition is false
      while (true) {
        mutex_lock.lock();
        if (this->checkCondition(first, second, op)) {
          j = i + 5;
          for (auto &c : this->commands) {
            j += c->execute(j);
          }
          Interpreter *whileInterpreterCondition = new Interpreter();
          whileInterpreterCondition->setVarMap(SetVariables::getSetVariables()->getVarMap());
          first = whileInterpreterCondition->interpret(vec[i + 1]);
          second = whileInterpreterCondition->interpret(vec[i + 3]);
        } else {
          mutex_lock.unlock();
          break;
        }
        mutex_lock.unlock();
      }
    //in case the condition was never true, find the end of the scope
    } else {
      while (vec[j].compare("}") != 0) {
        j++;
      }
    }
    this->commands = vector<Command *>();
    delete whileInterpreter;
    return j - i + 1;
  } catch (char const* e) {
    cout<<e<<endl;
  }
}