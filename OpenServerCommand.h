//
// Created by hani on 23/12/2019.
//
#pragma once
#ifndef EX3_OPENSERVERCOMMAND_H
#define EX3_OPENSERVERCOMMAND_H
#include "MapHolder.h"
#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <vector>
#include <map>
#include "VarsToUpdate.h"
using namespace std;

/**
 * This class opens the flight simulator as a server that sends us data that we read and interpret.
 */
class OpenServerCommand : public Command {
private:
  //The fields needed to open a connection with the server.
    sockaddr_in address;
    int socketfd;
    int client_socket;
public:
  //This function opens the server with the correct port, and creates the thread that
  //reads the data from the simulator, and updates the data received in our maps.
  int execute(int);
  //This is the function that is opened in a thread and then detached. It reads the data from teh simulator,
  //and updates the data in our maps.
  void ReadFromSim();
  virtual ~OpenServerCommand();
};

#endif //EX3_OPENSERVERCOMMAND_H