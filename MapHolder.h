//
// Created by noa on 23/12/2019.
//
#pragma once
#ifndef EX3__MAPHOLDER_H_
#define EX3__MAPHOLDER_H_

#include "Command.h"
#include "ex1.h"
#include <thread>
#include <mutex>
#include <unordered_map>

using namespace std;

/**
 *  singelton class that holds global variables that different classes use
 * */
class MapHolder {
public:
  //used by lexer to set the vector of strings from reading the txt file
    void setTokens(vector<string> vec);
  //token getter
    vector<string> getTokens();
  //map from "sim" address to index (by XML file)
    unordered_map<string, int> getIndexMap();

    Interpreter *getInterpreter();
  //singelton instance getter
    static MapHolder *getMapHolder();

    ~MapHolder() {
        delete this->interpreter;
    }

    void setStringToSend(string aVal);

    void setStringFlag(int value);

    string getStringToSend();

    void setStringEmpty();

    void setStopProgram(bool value);

    bool getStopProgram();

    void setCommandMap(unordered_map<string,Command*> map);

    Command* findCommand(string s);


private:

    static MapHolder *instance;
    //flag: true when program ends
    bool stop_program;
    //message for server
    string send_buffer;
    vector<string> tokens;
    //map from command name to command class
    unordered_map<string, Command*> command_map;
    unordered_map<string, int> sim_to_index;
    Interpreter *interpreter;

    void creatIndexMap();

    MapHolder();
};

#endif //EX3__MAPHOLDER_H_
