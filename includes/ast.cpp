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
  // NEWLINE
  if (node->isNull()) {
    std::cout << std::endl;
  }

  // Print CallNode
  const CallNode* call = dynamic_cast<CallNode*>(node);
  const Literal* res;
  if (call) {
    res = TableManager::getInstance().getValue(call->getIdent());
    res->print();
    return nullptr;
  }

  res = node->eval();
  if (!res) {
    throw std::string("print node eval is null");
  }
  res->print();

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
    if (!stmt) continue;
    stmt->eval();
    if (TableManager::getInstance().needReturnValue())
      break;
  }

  return nullptr;
}

void SuiteNode::append(Node* n) {
  stmts.push_back(n);
}

const Literal* FuncNode::eval() const {
  TableManager::getInstance().setFunc(name, suite);
  return nullptr;
}

const Literal* CallNode::eval() const {
  if (!ident) {
    throw std::string("Error: ident is null");
  }

  TableManager& tm = TableManager::getInstance();
  const Literal* res = new NoneLiteral();
  std::string funcName = getIdent();
  const Node* func = tm.getFunc(funcName);

  tm.pushScope();
  func->eval();
  if (tm.needReturnValue()) {
    res =tm.getReturnValue();
  }
  tm.popScope();
  tm.setValue(funcName, res);

  return res;
}
const std::string CallNode::getIdent() const {
  return static_cast<IdentNode*>(ident)->getIdent();
}

const Literal* ReturnNode::eval() const {
  const Literal* res;
  if (!testlist) {
    res = new NoneLiteral();
  } else {
    res = testlist->eval();
  }
  TableManager::getInstance().setReturnValue(res);
  return nullptr;
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