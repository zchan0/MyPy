#include <string>
#include <vector>
#include "symbolTable.h"

class TableManager {
public:
    static TableManager& getInstance();
    ~TableManager();

    void pushScope();
    void popScope();
    int getCurrentScope() const;

    const Node* getFunc(const std::string&);
    const Literal* getValue(const std::string&);
    Node* getParams(const std::string& name);
    void setFunc(const std::string&, const Node*);
    void setValue(const std::string&, const Literal*);
    void setParams(const std::string& name, Node*);
    void print() const;

    bool findValue(const std::string&) const;
    bool findFunc(const std::string&) const ;
    bool findParams(const std::string&) const;

    bool needReturnValue() const;
    const Literal* getReturnValue();
    void setReturnValue(const Literal*);

    TableManager(const TableManager&) = delete;
    TableManager& operator=(const TableManager&) = delete;

private:
    TableManager(): tables(), stackLimit(1000), currentScope(0) {
        tables.push_back(new SymbolTable());
    }

    // for stack, the top is current scope
    // std::stack<SymbolTable*> tableStack;
    std::vector<SymbolTable*> tables;

    // the maximum depth of the Python interpreter stack,
    // prevents infinite recursion from causing an overflow of the C stack
    // according to some sources, the default recursion limit is set to 1000
    // https://stackoverflow.com/a/3323013
    const unsigned long stackLimit;
    int currentScope;
};