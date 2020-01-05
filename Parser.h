//
// Created by noa on 29/12/2019.
//
#pragma once
#ifndef EX3__PARSER_H_
#define EX3__PARSER_H_
#include "Command.h"
#include "MapHolder.h"
#include "ConnectCommand.h"
#include "OpenServerCommand.h"
#include "IfCommand.h"
#include "PrintCommand.h"
#include "SleepCommand.h"
#include "WhileCommand.h"
#include "DefineVarCommand.h"
#include "lexer.h"
#include "Var.h"

class Parser {
public:
    unordered_map<string, Command*> getCommandMap() {
        return this->command_map;
    }
    unordered_map<string, Command*> command_map;

    void creatCommandMap();

    Parser() {
        creatCommandMap();
    }
    void parse();


};

#endif //EX3__PARSER_H_
