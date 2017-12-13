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

const Node* SymbolTable::getFunc(const std::string& name) const {
  std::map<std::string, const Node*>::const_iterator it = functions.find(name);
  if (it == functions.end()) {
    return nullptr;
  }
  return it->second;
}

void SymbolTable::setFunc(const std::string& name, const Node* node) {
  functions[name] = node;
}

Node* SymbolTable::getParams(const std::string& name) const {
  std::map<std::string, Node*>::const_iterator it = params.find(name);
  if (it == params.end()) {
    return nullptr;
  }
  return it->second;
}

void SymbolTable::setParams(const std::string& name, Node* node) {
  params[name] = node;
}

bool SymbolTable::findValue(const std::string& name) const {
  return symbols.find(name) != symbols.end();
}

bool SymbolTable::findFunc(const std::string& name) const {
  return functions.find(name) != functions.end();
}

bool SymbolTable::findParams(const std::string& name) const {
  return params.find(name) != params.end();
}

void SymbolTable::print() const {
  std::cout << "symbols: " << std::endl;
  std::map<std::string, const Literal*>::const_iterator it = symbols.cbegin();
  while (it != symbols.cend()) {
    std::cout << it->first << std::endl;
    it->second->eval()->print();
    ++it;
  }
  std::cout << "functions: ";
  std::map<std::string, const Node*>::const_iterator itr = functions.cbegin();
  while (itr != functions.cend()) {
    std::cout << itr->first << " ";
    ++itr;
  }
  std::cout << std::endl << "params for : ";
  std::map<std::string, Node*>::const_iterator pit = params.cbegin();
  while (pit != params.cend()) {
    std::cout << pit->first << " ";
    ++pit;
  }
  std::cout << std::endl << std::endl;
}
