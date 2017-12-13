#include "tableManager.h"

TableManager& TableManager::getInstance() {
    static TableManager instance;
    return instance;
}

TableManager::~TableManager() {
    for (SymbolTable* table : tables) {
        if (table != nullptr) delete table;
    }
}

void TableManager::pushScope() {
    if (tables.size() >= stackLimit) return;
    SymbolTable* table = new SymbolTable();
    tables.push_back(table);
    ++currentScope;
}

void TableManager::popScope() {
    if (currentScope == 0) return;
    tables.pop_back();
    --currentScope;
}

int TableManager::getCurrentScope() const {
    return currentScope;
}

const Node* TableManager::getFunc(const std::string& name) {
    std::vector<SymbolTable*>::reverse_iterator rit = tables.rbegin();
    while (rit != tables.rend()) {
        if ((*rit)->findFunc(name))
            return (*rit)->getFunc(name);
        ++rit;
    }
    throw std::string("NameError: function ") + name + std::string(" is not defined");
    return nullptr;
}

const Literal* TableManager::getValue(const std::string& name) {
    std::vector<SymbolTable*>::reverse_iterator rit = tables.rbegin();
    while (rit != tables.rend()) {
        if ((*rit)->findValue(name))
            return (*rit)->getValue(name);
        ++rit;
    }
    throw std::string("NameError: symbol ") + name + std::string(" is not defined");
    return nullptr;
}

void TableManager::setFunc(const std::string& name, const Node* node) {
    tables[currentScope]->setFunc(name, node);
}

void TableManager::setValue(const std::string& name, const Literal* val) {
    tables[currentScope]->setValue(name, val);
}

bool TableManager::needReturnValue() const {
    return tables[currentScope]->findValue("__RETURN__");
}

const Literal* TableManager::getReturnValue() {
    return tables[currentScope]->getValue("__RETURN__");
}

void TableManager::setReturnValue(const Literal* val) {
    tables[currentScope]->setValue("__RETURN__", val);
}

void TableManager::print() const {
    std::cout << "current scope: " << currentScope << std::endl;
    for (int i = tables.size() - 1; i >= 0; --i) {
        std::cout << "scope " << i << std::endl;
        tables[i]->print();
    }
}