//
// Created by noa on 29/12/2019.
//

#include "Parser.h"

/*reads vector of strings and executes command*/
void Parser::parse() {
  vector<string> tokens = MapHolder::getMapHolder()->getTokens();
  mutex mutex_lock;
  int i = 0, end = tokens.size();
  while (i != end) {
    mutex_lock.lock();
    auto command_iter = command_map.find(tokens[i]);
    if (command_iter != command_map.end()) {
      i += command_iter->second->execute(i);
    } else {
      auto sym_iter = SymbolTable::getSymbolTable()->getSymbolMap().find(tokens[i]);
      i += sym_iter->second->execute(i);
    }
    mutex_lock.unlock();
  }
}

/*Creates command map and sends it to the global class MapHolder*/
void Parser::creatCommandMap() {
    this->command_map.insert({"openDataServer", new OpenServerCommand});
    this->command_map.insert({"connectControlClient", new ConnectCommand});
    this->command_map.insert({"var", new DefineVarCommand});
    this->command_map.insert({"Print", new PrintCommand});
    this->command_map.insert({"Sleep", new SleepCommand});
    this->command_map.insert({"if", new IfCommand});
    this->command_map.insert({"while", new WhileCommand});
    MapHolder::getMapHolder()->setCommandMap(this->getCommandMap());
}

