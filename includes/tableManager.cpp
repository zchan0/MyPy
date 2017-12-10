#include "tableManager.h"

TableManager& TableManager::getInstance() {
    static TableManager instance;
    return instance;
}

TableManager::~TableManager() {
    while (!tableStack.empty()) {
        delete tableStack.top();
        tableStack.pop();
    }
}

void TableManager::pushScope() {
    if (tableStack.size() >= stackLimit) return;
    SymbolTable* table = new SymbolTable(tableStack.top());
    tableStack.push(table);
}

void TableManager::popScope() {
    if (!tableStack.empty()) {
        tableStack.pop();
    }
}

const SymbolTable* TableManager::currentTable() {
    return tableStack.top();
}

const Node* TableManager::getNode(const std::string& name) {
    return tableStack.top()->getNode(name);
}

const Literal* TableManager::getValue(const std::string& name) {
    return tableStack.top()->getValue(name);
}

void TableManager::setEntry(const std::string& name, const Node* node) {
    tableStack.top()->setNode(name, node);
}

void TableManager::setEntry(const std::string& name, const Literal* val) {
    tableStack.top()->setValue(name, val);
}