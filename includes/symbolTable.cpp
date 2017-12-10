#include <map>
#include <algorithm>
#include "symbolTable.h"
#include "literal.h"

const Literal* SymbolTable::getValue(const std::string& name) const {
  std::map<std::string, const Literal*>::const_iterator it = symbols.find(name);
  if (it == symbols.end()) {
    throw name + std::string(" not found");
  }
  return it->second;
}

void SymbolTable::setValue(const std::string& name, const Literal* val) {
  symbols[name] = val;
}

const Node* SymbolTable::getNode(const std::string& name) const {
  std::map<std::string, const Node*>::const_iterator it = nodes.find(name);
  if (it == nodes.end()) {
    throw name + std::string(" not found");
  }
  return it->second;
}

void SymbolTable::setNode(const std::string& name, const Node* node) {
  nodes[name] = node;
}
