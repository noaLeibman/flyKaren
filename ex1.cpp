//
// Created by noa on 06/11/2019.
//

#include "Expression.h"
#include "ex1.h"


using namespace std;

//binary operator class
BinaryOperator::BinaryOperator(Expression* l, Expression* r) {
    this->left = l;
    this->right = r;
}

BinaryOperator::~BinaryOperator() {
    delete this->right;
    delete this->left;
}


//unary operator class
UnaryOperator::UnaryOperator(Expression* expression){
    this->exp = expression;
}

UnaryOperator::~UnaryOperator(){
    delete this->exp;
}


//value class
double Value::calculate(){
    return this->num;
}


//variable class
Variable::Variable(string name_str, double val) {
    this->name = name_str;
    this->value = val;
}

double Variable::calculate() {
    return this->value;
}

Variable& Variable::operator++() {
    this->value += 1;
    return *this;
}

Variable& Variable::operator--() {
    this->value -= 1;
    return *this;
}

Variable& Variable::operator+=(double num) {
    this->value += num;
    return *this;
}

Variable& Variable::operator-=(double num) {
    this->value -= num;
    return *this;
}

Variable& Variable::operator++(int num) {
    num++;
    this->value++;
    return *this;
}

Variable& Variable::operator--(int num) {
    num++;
    this->value--;
    return *this;
}


//plus class
double Plus::calculate() {
  return this->left->calculate() + this->right->calculate();
}

Plus::Plus(Expression *l, Expression *r): BinaryOperator(l, r) {}

//Minus class
double Minus::calculate() {
  return this->right->calculate() - this->left->calculate();
}
Minus::Minus(Expression *l, Expression* r) : BinaryOperator(l, r) {}

//Mul class
Mul::Mul(Expression *l, Expression *r): BinaryOperator(l, r) {}

double Mul::calculate() {
    return this->left->calculate() * this->right->calculate();
}

//div class
Div::Div(Expression *l, Expression *r): BinaryOperator(l, r) {}

double Div::calculate() {
  if (this->right->calculate() == 0.0) {
    throw "division by zero";
  }
  return this->left->calculate() / this->right->calculate();
}

//UPlus class
UPlus::UPlus(Expression* expression): UnaryOperator(expression){}

double UPlus::calculate() {
    return this->exp->calculate();
}

//UMinus class
UMinus::UMinus(Expression* expression): UnaryOperator(expression){}

double UMinus::calculate() {
    return -this->exp->calculate();
}


//Interpreter class
Interpreter::Interpreter() {
  //operators and their priority
  this->op_map = {{"-", 0}, {"+", 0}, {"*", 1},
                            {"/", 1}, {"(", 0}, {"#", 2}, {"$", 2}};
}

/*replaces all unary plus and minus operators with different signs*/
void Interpreter::FindUnaries(string *str) {
  unsigned i = 0;
  int found;
  while (i < str->length()) {
    found = str->find("-", i);
    if (found < 0) {
      break;
    }
    if (found == 0 || str->at(found - 1) == '(') {
      str->replace(found, 1, "#");
    }
    i = found + 1;
  }
  i = 0;
  while (i < str->length()) {
    found = str->find("+", i);
    if (found < 0) {
      break;
    }
    if (found == 0 || str->at(found - 1) == '(') {
      str->replace(found, 1, "$");
    }
    i = found + 1;
  }
}

Expression* Interpreter::interpret(string str) {
  //replace unary operators with other symbols and tokenize
  this->FindUnaries(&str);
  this->tokenize(&str);

  //make reverse polish notation queue (out_queue)
  for (string &token : tokens) {
    if (token.empty()) {
      break;
    }
    if (this->op_map.find(token) != this->op_map.end()) {
      if (token.compare("(") != 0) {
        while (!op_stack.empty() && (this->op_map.find(op_stack.top())->second > this->op_map.find(token)->second)) {
          this->out_queue.push(this->op_stack.top());
          this->op_stack.pop();
        }
      }
      this->op_stack.push(token);
    }
    else if (token.compare(")") == 0) {
      while (!op_stack.empty() && this->op_stack.top().compare("(") != 0) {
        this->out_queue.push(this->op_stack.top());
        this->op_stack.pop();
      }
      if (op_stack.top().compare("(") != 0) {
        throw "invalid brackets logic";
      }
      this->op_stack.pop();
    }
    else if (token.at(0) >= '0' && token.at(0) <='9') {
      this->out_queue.push(token);
    }
    else if (isalpha(token.at(0))) {
      double value = this->var_map.find(token)->second;
      this->out_queue.push(to_string(value));
    }
    else {
      throw "bad input";
    }
  }
  //pop remaining operators from stack into queue
  while (!this->op_stack.empty()) {
    out_queue.push(op_stack.top());
    op_stack.pop();
  }
  return this->MakeFinalExpression();
}

void Interpreter::tokenize(string* str) {
  int j = 0, open_brackets = 0, close_brackets = 0;
  smatch s;
  regex not_pattern("[^0-9a-zA-Z-+*/().$#]|[+*/#$-][+*/#$-]|^[*/+-]");
  regex_search(*str, s, not_pattern);
//  for (auto x : s) {
//    cout << x << " ";
//  }
  if(!s.empty()) {
    throw "illegal math expression";
  }
  regex pattern("[-+*/#$]|[()]|([a-zA-Z][a-zA-Z_]*([0-9])*)|[0-9]+(\\.)?[0-9]*");
  auto words_begin = sregex_iterator(str->begin(), str->end(), pattern);
  auto words_end = sregex_iterator();

  for (sregex_iterator i = words_begin; i != words_end; ++i) {
    smatch match = *i;
    string token = match.str();
    this->tokens[j] = token;
    j++;
    if (token.compare("(") == 0) {
      open_brackets++;
    } else if (token.compare(")") == 0) {
      close_brackets++;
    }
  }
  if (open_brackets != close_brackets) {
    throw "illegal math expression";
  }
}

void Interpreter::setVariables(string str) {
  int j = 0;
  smatch s;
  //check for illegal expressions
  regex not_pattern("[^a-zA-z0-9_=;.-]|=[^0-9-]|(=[0-9]*[^0-9;.-]+)");
  regex_search(str, s, not_pattern);
  if(!s.empty()) {
    throw "illegal variable assignment! in interpreter->setVariables";
  }
  regex pattern("[a-zA-Z][a-zA-z_0-9]*=[0-9]+(\\.)*[0-9]*");
  auto words_begin = sregex_iterator(str.begin(), str.end(), pattern);
  auto words_end = sregex_iterator();
  for (sregex_iterator i = words_begin; i != words_end; ++i) {
    smatch match = *i;
    insertMap(match.str());
    j++;
  }
}

void Interpreter::insertMap(string str) {
  //gets string with the form- "var=value" and inserts map
  char delimiter = '=';
  size_t equal = str.find(delimiter, 0);
  string var = str.substr(0, equal);
  string val = str.substr(equal + 1, str.length() - 1);
  if (!isalpha(var.at(0))) {
    throw "invalid variable";
  }
  regex not_number("[^0-9.]");
  smatch s;
  regex_search(val, s, not_number);
  if (!s.empty()) {
    throw "illegal variable assignment!";
  }
  double value = stod(val);
  if (var_map.find(var) != var_map.end()) {
    var_map[var] = value;
  } else {
    this->var_map.insert({var, value});
  }
}

Expression* Interpreter::MakeFinalExpression() {
  Expression* ex1;
  Expression* ex2;
  //poping elements from queue and turning them to expressions
  while (!this->out_queue.empty()) {
    string str = out_queue.front();
    out_queue.pop();
    if (str.compare("-") == 0) {
      ex1 = final_stack.top();
      final_stack.pop();
      ex2 = final_stack.top();
      final_stack.pop();
      final_stack.push(new Minus(ex1, ex2));
    }
    else if (isalpha(str.at(0))) {
      this->final_stack.push(new Variable(str, op_map.find(str)->second));
    }
    else if (str.compare("+") == 0) {
      ex1 = final_stack.top();
      final_stack.pop();
      ex2 = final_stack.top();
      final_stack.pop();
      final_stack.push(new Plus(ex1, ex2));
    }
    else if (str.at(0) >= '0' && str.at(0) <= '9' ||
        (str.at(0) == '-' && (str.at(1) >= '0' && str.at(1)))) {
      this->final_stack.push(new Value(stod(str)));
    }
    else if (str.compare("*") == 0) {
      ex1 = final_stack.top();
      final_stack.pop();
      ex2 = final_stack.top();
      final_stack.pop();
      final_stack.push(new Mul(ex1, ex2));
    }
    else if (str.compare("/") == 0) {
      ex1 = final_stack.top();
      final_stack.pop();
      ex2 = final_stack.top();
      final_stack.pop();
      final_stack.push(new Div(ex2, ex1));
    }
    else if (str.compare("#") == 0) {
      ex1 = final_stack.top();
      final_stack.pop();
      final_stack.push(new UMinus(ex1));
    }
    else if (str.compare("$") == 0) {
      ex1 = final_stack.top();
      final_stack.pop();
      final_stack.push(new UMinus(ex1));
    }
    else {
      cout<<str<<endl;
      throw "invalid token in out_queue";
    }
  }
  ex1 = final_stack.top();
  final_stack.pop();
  if (!final_stack.empty()) {
    throw "invalid postfix expression";
  }
  return ex1;
}
