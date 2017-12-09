#include <iostream>
#include <typeinfo>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include "ast.h"
#include "symbolTable.h"

const Literal* IdentNode::eval() const {
  const Literal* val = SymbolTable::getInstance().getValue(ident);
  return val;
}

const Literal* PrintNode::eval() const {
  if (node->isNull()) {
    return nullptr;
  }
  node->eval()->print();
  return nullptr;
}

const Literal* IfNode::eval() const {
  if (comparison->isNull()) {
    throw std::string("comparison is null");
    return nullptr;
  }
  if (!comparison->eval()) {
    throw std::string("comparison cannot evaluate");
    return nullptr;
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
    stmt->eval();
  }

  return nullptr;
}

void SuiteNode::push(Node* n) {
  stmts.push_back(n);
}

const Literal* UnaryNode::eval() const {
  const Literal* absVal = node->eval();
  return absVal->unopVal(op);
}

AsgBinaryNode::AsgBinaryNode(Node* left, Node* right) :
  BinaryNode(left, right) {
  const Literal* res = right->eval();
  const std::string n = static_cast<IdentNode*>(left)->getIdent();
  SymbolTable::getInstance().setValue(n, res);
}
const Literal* AsgBinaryNode::eval() const {
  if (left->isNull() || right->isNull()) {
    throw std::string("Error: left or right of BinaryNode is null");
  }
  const Literal* res = right->eval();
  const std::string n = static_cast<IdentNode*>(left)->getIdent();
  SymbolTable::getInstance().setValue(n, res);
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