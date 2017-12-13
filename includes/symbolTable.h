#ifndef SYMBOLTABLE__H
#define SYMBOLTABLE__H

#include <iostream>
#include <string>
#include <map>
#include <algorithm>

class Node;
class Literal;

class SymbolTable {
public:
  SymbolTable(): functions(), symbols() {}
  ~SymbolTable() {}

  const Node* getFunc(const std::string& name) const;
  const Literal* getValue(const std::string& name) const;
  Node* getParams(const std::string& name) const;

  void setFunc(const std::string& name, const Node* node);
  void setValue(const std::string& name, const Literal* val);
  void setParams(const std::string& name, Node* node);

  bool findFunc(const std::string&) const;
  bool findValue(const std::string&) const;
  bool findParams(const std::string&) const;

  void print() const;
  SymbolTable(const SymbolTable&) = delete;
  SymbolTable& operator=(const SymbolTable&) = delete;

private:
  std::map<std::string, const Node*> functions;
  std::map<std::string, Node*> params;
  std::map<std::string, const Literal*> symbols;
};

#endif
