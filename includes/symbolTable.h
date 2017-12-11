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
  SymbolTable(): nodes(), symbols() {}
  ~SymbolTable() {}

  const Node* getFunc(const std::string& name) const;
  const Literal* getValue(const std::string& name) const;
  void setFunc(const std::string& name, const Node* node);
  void setValue(const std::string& name, const Literal* val);
  bool findFunc(const std::string&) const;
  bool findSymbol(const std::string&) const;

  void print() const;
  SymbolTable(const SymbolTable&) = delete;
  SymbolTable& operator=(const SymbolTable&) = delete;

private:
  std::map<std::string, const Node*> nodes;
  std::map<std::string, const Literal*> symbols;
};

#endif
