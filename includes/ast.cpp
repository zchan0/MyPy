#include <iostream>
#include <typeinfo>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include "ast.h"
#include "tableManager.h"

const Literal* IdentNode::eval() const {
  const Literal* val = TableManager::getInstance().getValue(ident);
  return val;
}

const Literal* PrintNode::eval() const {
  if (node->isNull()) {
    throw std::string("print node is null");
  }
  node->eval()->print();
  return nullptr;
}

const Literal* IfNode::eval() const {
  if (comparison->isNull()) {
    throw std::string("comparison is null");
  }
  if (!comparison->eval()) {
    throw std::string("comparison cannot evaluate");
  }

  if (comparison->eval()->boolValue()) {
    return ifBranch->eval();
  } else {
    return elseBranch->eval();
  }
}

const Literal* SuiteNode::eval() const {
  if (stmts.empty()) {
    return nullptr;
  }

  for (Node* stmt : stmts) {
    FuncNode* func = dynamic_cast<FuncNode*>(stmt);
    if (func) continue;

    ReturnNode* ret = dynamic_cast<ReturnNode*>(stmt);
    if (ret) {
      return ret->eval();
    } else {
      stmt->eval();
    }
  }

  return nullptr;
}

void SuiteNode::append(Node* n) {
  stmts.push_back(n);
}

const Literal* FuncNode::eval() const {
  SuiteNode* suiteNode = dynamic_cast<SuiteNode*>(suite);
  if (!suiteNode) {
    throw std::string("Error: cannot cast to SuiteNode");
  }
  const Literal* res = suiteNode->eval();
  // no return statement
  if (!res) res = new NoneLiteral();
  return res;
}

const Literal* CallNode::eval() const {
  if (!ident) {
    throw std::string("Error: ident is null");
  }
  std::string funcName = static_cast<IdentNode*>(ident)->getIdent();
  // if no function named name, Tablemanager will throw exception
  const Node* func = TableManager::getInstance().getFunc(funcName);
  TableManager::getInstance().pushScope();
  const Literal* res = func->eval();
  TableManager::getInstance().popScope();
  return res;
}

const Literal* ReturnNode::eval() const {
  if (!testlist) {
    return new NoneLiteral();
  } else {
    return testlist->eval();
  }
}

const Literal* UnaryNode::eval() const {
  const Literal* absVal = node->eval();
  return absVal->unopVal(op);
}

AsgBinaryNode::AsgBinaryNode(Node* left, Node* right) :
  BinaryNode(left, right) {
  const Literal* res = right->eval();
  const std::string n = static_cast<IdentNode*>(left)->getIdent();
  TableManager::getInstance().setValue(n, res);
}
const Literal* AsgBinaryNode::eval() const {
  if (left->isNull() || right->isNull()) {
    throw std::string("Error: left or right of BinaryNode is null");
  }
  const Literal* res = right->eval();
  const std::string n = static_cast<IdentNode*>(left)->getIdent();
  TableManager::getInstance().setValue(n, res);
  return res;
}

const Literal* AddBinaryNode::eval() const {
  if (left->isNull() || right->isNull()) {
    throw std::string("Error: left or right of BinaryNode is null");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  //return (*x+*y);
  return (*x).operator+(*y);
}

const Literal* SubBinaryNode::eval() const {
  if (left->isNull() || right->isNull()) {
    throw std::string("Error: left or right of BinaryNode is null");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return ((*x)-(*y));
}

const Literal* MulBinaryNode::eval() const {
  if (left->isNull() || right->isNull()) {
    throw std::string("Error: left or right of BinaryNode is null");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return ((*x)*(*y));
}

const Literal* DivBinaryNode::eval() const {
  if (left->isNull() || right->isNull()) {
    throw std::string("Error: left or right of BinaryNode is null");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return ((*x)/(*y));
}

const Literal* IntDivBinaryNode::eval() const {
  if (left->isNull() || right->isNull()) {
    throw std::string("Error: left or right of BinaryNode is null");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return (*x).intDiv(*y);
}

const Literal* ModBinaryNode::eval() const {
  if (left->isNull() || right->isNull()) {
    throw std::string("Error: left or right of BinaryNode is null");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return ((*x) % (*y));
}

const Literal* ExpBinaryNode::eval() const {
  if (left->isNull() || right->isNull()) {
    throw std::string("Error: left or right of BinaryNode is null");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return (*x) ^ (*y);
}


const Literal* LessBinaryNode::eval() const {
  if (left->isNull() || right->isNull()) {
    throw std::string("Error: left or right of BinaryNode is null");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return (*x) < (*y);
}

const Literal* GreaterBinaryNode::eval() const {
  if (left->isNull() || right->isNull()) {
    throw std::string("Error: left or right of BinaryNode is null");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return (*x) > (*y);
}

const Literal* EqualBinaryNode::eval() const {
  if (left->isNull() || right->isNull()) {
    throw std::string("Error: left or right of BinaryNode is null");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return (*x) == (*y);
}

const Literal* GrtEqBinaryNode::eval() const {
  if (left->isNull() || right->isNull()) {
    throw std::string("Error: left or right of BinaryNode is null");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return (*x) >= (*y);
}

const Literal* LessEqBinaryNode::eval() const {
  if (left->isNull() || right->isNull()) {
    throw std::string("Error: left or right of BinaryNode is null");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return (*x) <= (*y);
}