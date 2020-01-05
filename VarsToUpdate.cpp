//
// Created by hani on 30/12/2019.
//

#include "VarsToUpdate.h"

VarsToUpdate::VarsToUpdate() {
    this->vars_to_update = unordered_map<int,Var*>();
}
VarsToUpdate *VarsToUpdate::instance =0;
//checks if there's already an instance, else creates one and returns it.
VarsToUpdate *VarsToUpdate::getVarsToUpdate() {
    if (instance == 0) {
        instance = new VarsToUpdate();

    }
    return instance;
}
void VarsToUpdate::setVarsToUpdate(unordered_map<int,Var*> map) {
    this->vars_to_update=map;
}
//iterator to the begining of the map.
unordered_map<int,Var*>::iterator VarsToUpdate::getBeginMap(){
    return this->vars_to_update.begin();
}
//iterator to the end of the map.
unordered_map<int,Var*>::iterator VarsToUpdate::getEndMap(){
    return this->vars_to_update.end();
}