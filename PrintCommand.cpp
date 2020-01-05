//
// Created by hani on 23/12/2019.
//

#include <iostream>
#include "PrintCommand.h"
#include "SetVariables.h"

using namespace std;

/**
 *
 * @param i the position of the Print command
 * @return the number of indexes to advace in the parser
 */
int PrintCommand::execute(int i) {
    std::vector<string> tokens = this->map->getTokens();
    string str = tokens[i + 1];

  //if there are quotation marks, need to print a string, else print a value after interpretation.
    if (str.find("\"") == string::npos) {
        Interpreter *printInterpreter = new Interpreter;
        printInterpreter->setVarMap(SetVariables::getSetVariables()->getSetVariables()->getVarMap());
        Expression *ex = printInterpreter->interpret(tokens[i+1]);
        cout << to_string(ex->calculate()) << endl;
    } else {
        string cut = str.substr(1, str.length() - 2);
        cout << cut << endl;
    }

    return 2;
}

PrintCommand::~PrintCommand() {}

PrintCommand::PrintCommand() {
    this->map = MapHolder::getMapHolder();
}