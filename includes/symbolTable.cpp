#include <map>
#include <algorithm>
#include "symbolTable.h"
#include "literal.h"

const Literal* SymbolTable::getValue(const std::string& name) const {
  std::map<std::string, const Literal*>::const_iterator it = symbols.find(name);
  if (it == symbols.end()) {
    return nullptr;
  }
  return it->second;
}

void SymbolTable::setValue(const std::string& name, const Literal* val) {
  symbols[name] = val;
}

const Node* SymbolTable::getNode(const std::string& name) const {
  std::map<std::string, const Node*>::const_iterator it = nodes.find(name);
  if (it == nodes.end()) {
    return nullptr;
  }
  return it->second;
}

void SymbolTable::setNode(const std::string& name, const Node* node) {
  nodes[name] = node;
}

bool SymbolTable::findSymbol(const std::string& name) const {
  return symbols.find(name) != symbols.end();
}

bool SymbolTable::findNode(const std::string& name) const {
  return nodes.find(name) != nodes.end();
}

void SymbolTable::print() const {
  std::cout << "symbols: " << std::endl;
  std::map<std::string, const Literal*>::const_iterator it = symbols.cbegin();
  while (it != symbols.cend()) {
    std::cout << it->first << std::endl;
    it->second->eval()->print();
    ++it;
  }
  std::cout << "nodes: ";
  std::map<std::string, const Node*>::const_iterator itr = nodes.cbegin();
  while (itr != nodes.cend()) {
    std::cout << itr->first << " ";
    ++itr;
  }
  std::cout << std::endl << std::endl;
}
