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

bool TableManager::needReturnValue() const {
    return tables[currentScope]->findSymbol("__RETURN__");
}

const SymbolTable* TableManager::localScope() {
    return tables[currentScope];
}

const Node* TableManager::getNode(const std::string& name) {
    const Node* res = tables[currentScope]->getNode(name);
    if (!res) {
        int lookupScope = currentScope - 1;
        while (lookupScope >= 0) {
            res = tables[lookupScope]->getNode(name);
            if (res) return res;
            --lookupScope;
        }
        throw std::string("NameError: name ") + name + std::string(" is not defined");
    }
    return res;
}

const Literal* TableManager::getValue(const std::string& name) {
    const Literal* res = tables[currentScope]->getValue(name);
    if (!res) {
        int lookupScope = currentScope - 1;
        while (lookupScope >= 0) {
            res = tables[lookupScope]->getValue(name);
            if (res) return res;
            --lookupScope;
        }
        throw std::string("NameError: name ") + name + std::string(" is not defined");
    }
    return res;
}

void TableManager::setNode(const std::string& name, const Node* node) {
    tables[currentScope]->setNode(name, node);
}

void TableManager::setValue(const std::string& name, const Literal* val) {
    tables[currentScope]->setValue(name, val);
}

const Literal* TableManager::getReturnValue() {
    return tables[currentScope]->getValue("__RETURN__");
}

void TableManager::setReturnValue(const Literal* val) {
    tables[currentScope]->setValue("__RETURN__", val);
}

void TableManager::print() const {
    std::cout << "current scope: " << currentScope << std::endl;
    tables[currentScope]->print();
}
