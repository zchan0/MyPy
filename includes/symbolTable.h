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
  SymbolTable(const SymbolTable* p): nodes(), symbols(), parent(p) {}
  ~SymbolTable() {}

  const Node* getNode(const std::string& name) const;
  const Literal* getValue(const std::string& name) const;
  void setNode(const std::string& name, const Node* node);
  void setValue(const std::string& name, const Literal* val);

  SymbolTable(const SymbolTable&) = delete;
  SymbolTable& operator=(const SymbolTable&) = delete;

private:
  std::map<std::string, const Node*> nodes;
  std::map<std::string, const Literal*> symbols;
  const SymbolTable* parent;
};

#endif
