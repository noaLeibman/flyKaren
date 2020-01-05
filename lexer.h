//
// Created by hani on 21/12/2019.
//
#pragma once
#ifndef EX3_LEXER_H
#define EX3_LEXER_H
#include <cstdlib>
#include <vector>
#include <fstream>
#include <sstream>
#include "MapHolder.h"

using namespace std;

class lexer {
private:
    //the vector of the tokens
    std::vector<string> stringArray;
public:
    //returns the tokens separated by the lexer
    std::vector<string> getTokens();

    /**
     *
     * @param fileName the given fly.txt to interpret.
     */
    lexer(std::string fileName);

    //destructor
    ~lexer();
};

#endif //EX3_LEXER_H