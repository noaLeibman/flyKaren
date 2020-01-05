//
// Created by noa on 23/12/2019.
//
#pragma once
#ifndef EX3__CONECTCOMMAND_H_
#define EX3__CONECTCOMMAND_H_
#include "MapHolder.h"

/*Client class. connects to server and sends messages*/
class ConnectCommand : public Command {

private:
    int client_socket;

public:

  //connects to server
    int execute(int);

  //sends messages to server
    void sendToServer();
};

#endif //EX3__CONECTCOMMAND_H_
