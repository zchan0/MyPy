#include <stack>
#include <string>
#include "symbolTable.h"

class TableManager {
public:
    static TableManager& getInstance();
    ~TableManager();

    void pushScope();
    void popScope();
    const SymbolTable* currentTable();
    const Node* getNode(const std::string&);
    const Literal* getValue(const std::string&);
    // use function overfload for eash-call
    void setEntry(const std::string&, const Node*);
    void setEntry(const std::string&, const Literal*);

    TableManager(const TableManager&) = delete;
    TableManager& operator=(const TableManager&) = delete;

private:
    TableManager(): tableStack(), stackLimit(1000) {
        tableStack.push(new SymbolTable(nullptr));
    }

    // for stack, the top is current scope
    std::stack<SymbolTable*> tableStack;

    // the maximum depth of the Python interpreter stack,
    // prevents infinite recursion from causing an overflow of the C stack
    // according to some sources, the default recursion limit is set to 1000
    // https://stackoverflow.com/a/3323013
    const int stackLimit;
};