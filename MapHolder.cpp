//
// Created by noa on 23/12/2019.
//

#include "MapHolder.h"

void MapHolder::setStringToSend(string toSend) {
    string currString = this->getStringToSend();
    if (currString.empty()) {
        this->send_buffer = toSend;
    } else {
        this->send_buffer = this->send_buffer + toSend;
    }
}

string MapHolder::getStringToSend() {
    return this->send_buffer;
}

void MapHolder::setStringEmpty() {
    this->send_buffer = "";
}

void MapHolder::setStopProgram(bool value) {
    this->stop_program = value;
}

bool MapHolder::getStopProgram() {
    return this->stop_program;
}


void MapHolder::creatIndexMap() {
    this->sim_to_index.insert({"instrumentation/airspeed-indicator/indicated-speed-kt", 0});
    this->sim_to_index.insert({"sim/time/warp", 1});
    this->sim_to_index.insert({"controls/switches/magnetos", 2});
    this->sim_to_index.insert({"instrumentation/heading-indicator/offset-deg", 3});
    this->sim_to_index.insert({"instrumentation/altimeter/indicated-altitude-ft", 4});
    this->sim_to_index.insert({"instrumentation/altimeter/pressure-alt-ft", 5});
    this->sim_to_index.insert({"instrumentation/attitude-indicator/indicated-pitch-deg", 6});
    this->sim_to_index.insert({"instrumentation/attitude-indicator/indicated-roll-deg", 7});
    this->sim_to_index.insert({"instrumentation/attitude-indicator/internal-pitch-deg", 8});
    this->sim_to_index.insert({"instrumentation/attitude-indicator/internal-roll-deg", 9});
    this->sim_to_index.insert({"instrumentation/encoder/indicated-altitude-ft", 10});
    this->sim_to_index.insert({"instrumentation/encoder/pressure-alt-ft", 11});
    this->sim_to_index.insert({"instrumentation/gps/indicated-altitude-ft", 12});
    this->sim_to_index.insert({"instrumentation/gps/indicated-ground-speed-kt", 13});
    this->sim_to_index.insert({"instrumentation/gps/indicated-vertical-speed", 14});
    this->sim_to_index.insert({"instrumentation/heading-indicator/indicated-heading-deg", 15});
    this->sim_to_index.insert({"instrumentation/magnetic-compass/indicated-heading-deg", 16});
    this->sim_to_index.insert({"instrumentation/slip-skid-ball/indicated-slip-skid", 17});
    this->sim_to_index.insert({"instrumentation/turn-indicator/indicated-turn-rate", 18});
    this->sim_to_index.insert({"instrumentation/vertical-speed-indicator/indicated-speed-fpm", 19});
    this->sim_to_index.insert({"controls/flight/aileron", 20});
    this->sim_to_index.insert({"controls/flight/elevator", 21});
    this->sim_to_index.insert({"controls/flight/rudder", 22});
    this->sim_to_index.insert({"controls/flight/flaps", 23});
    this->sim_to_index.insert({"controls/engines/engine/throttle", 24});
    this->sim_to_index.insert({"controls/engines/current-engine/throttle", 25});
    this->sim_to_index.insert({"controls/switches/master-avionics", 26});
    this->sim_to_index.insert({"controls/switches/starter", 27});
    this->sim_to_index.insert({"engines/active-engine/auto-start", 28});
    this->sim_to_index.insert({"controls/flight/speedbrake", 29});
    this->sim_to_index.insert({"sim/model/c172p/brake-parking", 30});
    this->sim_to_index.insert({"controls/engines/engine/primer", 31});
    this->sim_to_index.insert({"controls/engines/current-engine/mixture", 32});
    this->sim_to_index.insert({"controls/switches/master-bat", 33});
    this->sim_to_index.insert({"controls/switches/master-alt", 34});
    this->sim_to_index.insert({"engines/engine/rpm", 35});
}

MapHolder *MapHolder::instance = 0;

MapHolder *MapHolder::getMapHolder() {
    if (instance == 0) {
        instance = new MapHolder();
    }
    return instance;
}

void MapHolder::setTokens(vector<string> vec) {
    this->tokens = vec;
}

vector<string> MapHolder::getTokens() {
    return this->tokens;
}

unordered_map<string, int> MapHolder::getIndexMap() {
    return this->sim_to_index;
}

Interpreter *MapHolder::getInterpreter() {
    return this->interpreter;
}

MapHolder::MapHolder() {
    this->creatIndexMap();
    this->interpreter = new Interpreter();
    this->send_buffer = "";
    this->stop_program = false;
};

void MapHolder::setCommandMap(unordered_map<string, Command *> map) {
    this->command_map = map;
}

Command* MapHolder::findCommand(string s) {
  auto iter = this->command_map.find(s);
  if (iter != this->command_map.end()) {
    return iter->second;
  } else {
    return nullptr;
  }
}