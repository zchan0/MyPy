#pragma once
#include <iostream>

class Literal;

class Node {
public:
  Node() {}
  virtual ~Node() {}
  virtual const Literal* eval() const = 0;
  virtual bool isNull() const {
    return this->eval() == nullptr;
  }
  virtual void print() const {
    std::cout << "NODE" << std::endl;
  }
};

