//
// Created by noa on 23/12/2019.
//
#include "ConnectCommand.h"
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>
#include "SetVariables.h"

using namespace std;

int ConnectCommand::execute(int i) {
    vector<string> tokens = MapHolder::getMapHolder()->getTokens();
    const char* ip = tokens[i + 1].c_str();

    //connecting to server
    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (this->client_socket == -1) {
        //error
        cout << "Could not create a socket" << endl;
        return -1;
    }
    sockaddr_in address; //in means IP4
    Interpreter *interpreter = new Interpreter();
    interpreter->setVarMap(SetVariables::getSetVariables()->getVarMap());
    Expression *ex1 = interpreter->interpret(tokens[i+2]);
    address.sin_family = AF_INET;//IP4
    address.sin_addr.s_addr = inet_addr(ip);  //the localhost address
    address.sin_port = htons(ex1->calculate());

    int is_connect = connect(client_socket, (struct sockaddr *) &address, sizeof(address));
    if (is_connect == -1) {
        std::cout << "Could not connect to host server" << std::endl;
        return -2;
    }

    std::thread clientThread(&ConnectCommand::sendToServer, this);
    clientThread.detach();

    return 3;
}

void ConnectCommand::sendToServer() {
  mutex mutex_lock;

  //loop continues while "stop-program" condition is false
    while (!MapHolder::getMapHolder()->getStopProgram()) {
      mutex_lock.lock();
      //if "string-to-send" is not empty
      if (MapHolder::getMapHolder()->getStringToSend().compare("") != 0) {
          std::stringstream streamSend(MapHolder::getMapHolder()->getStringToSend());
          std::string stringToSend;
          std::getline(streamSend, stringToSend, '\n');
          string toSend = stringToSend;
          MapHolder::getMapHolder()->setStringToSend(MapHolder::getMapHolder()->getStringToSend().substr(toSend.length()));
          toSend=toSend+"\r\n";
          int stringLength = toSend.length();
          char c[stringLength + 1];
          strcpy(c, toSend.c_str());
          int is_sent = send(client_socket, c, stringLength, 0);
          if (is_sent == -1) {
              std::cout << "Error sending message" << std::endl;
          }
          MapHolder::getMapHolder()->setStringEmpty();
      }
      mutex_lock.unlock();
    }
    //closing socket when program ends
    close(this->client_socket);
}