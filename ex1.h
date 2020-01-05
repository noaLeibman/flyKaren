//
// Created by noa on 08/11/2019.
//
#pragma once
#ifndef EXERCISE1_EX1_H
#define EXERCISE1_EX1_H
#define ARRAY_MAX 40


#include <cstdlib>
#include <queue>
#include <regex>
#include <iostream>
#include <unordered_map>
#include "Expression.h"

using namespace std;

/*base class for Minus, Plus, Div, Mul*/
class BinaryOperator: public Expression {
protected:
    Expression* left;
    Expression* right;
public:
    BinaryOperator(Expression* l, Expression* r);
    virtual ~BinaryOperator();
};

/*base class for UMinus, UPlus*/
class UnaryOperator: public Expression {
protected:
    Expression* exp;
public:
    UnaryOperator(Expression* expression);
    virtual ~UnaryOperator();
};

class Value: public Expression {
private:
    const double num;

public:
    Value(double number) : num(number){}
    double calculate() override ;
};

class Variable: public  Expression {
private:
    string name;
    double value;

public:
    Variable(string name_str, double val);
    double calculate() override;
    Variable& operator++();
    Variable& operator--();
    Variable& operator+=(double num);
    Variable& operator-=(double num);
    Variable& operator++(int num);
    Variable& operator--(int num);
};

class Plus: public BinaryOperator {
 public:
    Plus(Expression* l, Expression* r);
    double calculate() override;
};

class Minus: public BinaryOperator {
 public:
    Minus(Expression* l, Expression* r);
    double calculate() override;
};

class Mul: public BinaryOperator {
 public:
    Mul(Expression* l, Expression* r);
    double  calculate() override;
};

class Div: public BinaryOperator {
 public:
    Div(Expression* l, Expression* r);
    double  calculate() override;
};

class UPlus: public UnaryOperator {
 public:
    UPlus(Expression* expression);
    double  calculate() override;
};

class UMinus: public UnaryOperator {
 public:
    UMinus(Expression* expression);
    double  calculate() override;
};

/*interprets complicated expressions with shunting yard algorithm*/
class Interpreter {
 private:
    map<string, int> op_map;
    unordered_map<string, double> var_map;
    stack<string> op_stack;
    stack<Expression*> final_stack;
    std::queue<string> out_queue;
    string tokens[ARRAY_MAX];

 public:
    void setVarMap(unordered_map<string,double> map){
        this->var_map=map;
    }
    Interpreter();
    virtual ~Interpreter() {}
    Expression* interpret(string str);
    void setVariables(string str);
    void insertMap(string str);
    void tokenize(string* str);
    void FindUnaries(string* str);
    Expression* MakeFinalExpression();
};
#endif //EXERCISE1_EX1_H
