//
// Created by hani on 23/12/2019.
//
#pragma once
#ifndef EX3_COMMAND_H
#define EX3_COMMAND_H

/**
Base Abstract class for all commands (interface)
*/
class Command{
public:
  /*Every command can execute with it's own implementation*/
    virtual int execute(int) =0;
  /*Destructor*/
    virtual ~Command(){}
};
#endif //EX3_COMMAND_H
