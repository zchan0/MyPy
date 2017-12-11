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

const SymbolTable* TableManager::currentTable() {
    return tables[currentScope];
}

int TableManager::getCurrentScope() const {
    return currentScope;
}

const Node* TableManager::getFunc(const std::string& name) {
    const Node* res = tables[currentScope]->getFunc(name);
    if (!res) {
        int lookupScope = currentScope - 1;
        while (lookupScope >= 0) {
            res = tables[lookupScope]->getFunc(name);
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

void TableManager::setFunc(const std::string& name, const Node* node) {
    tables[currentScope]->setFunc(name, node);
}

void TableManager::setValue(const std::string& name, const Literal* val) {
    tables[currentScope]->setValue(name, val);
}

void TableManager::print() const {
    std::cout << "current scope: " << currentScope << std::endl;
    tables[currentScope]->print();
}
