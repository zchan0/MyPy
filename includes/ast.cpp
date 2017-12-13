#include <iostream>
#include <typeinfo>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include "ast.h"

const Literal* IdentNode::eval() const {
  const Literal* val = TableManager::getInstance().getValue(ident);
  if (!val) {
    throw std::string("UnboundLocalError: local variable ") + ident + std::string(" referenced before assignment");
  }
  return val;
}

const Literal* PrintNode::eval() const {
  // NEWLINE
  if (!node) {
    std::cout << std::endl;
  }

  const Literal* res = node->eval();
  if (!res) {
    throw std::string("print node eval is null");
  }
  res->print();

  return nullptr;
}

const Literal* IfNode::eval() const {
  if (!comparison) {
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

// precook for eval
// rule:
//    if there are AsgBinaryNodes, mark identifier(lval) as nullptr.
//    for TableManager, it can find a ident for current scope, while its value is nullptr
//    handle nullptr in IdentNode->eval()
void SuiteNode::preeval() const {
    if (stmts.empty()) return;

    for (Node* stmt : stmts) {
      if (!stmt) continue;

      const AsgBinaryNode* asg = dynamic_cast<AsgBinaryNode*>(stmt);
      if (asg) {
        std::string ident = asg->getIdent();
        TableManager::getInstance().setValue(ident, nullptr);
      }
    }
}
const Literal* SuiteNode::eval() const {
  if (stmts.empty()) {
    return nullptr;
  }

  // call preeval here to make sure the scope is correct
  preeval();

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
  if (params) {
    TableManager::getInstance().setParams(name, params);
  }
  return nullptr;
}

void ParamNode::append(Node* param) {
  params.push_back(param);
}
const std::vector<Node*> ParamNode::getParams() {
  return params;
}
const Literal* ParamNode::eval() const {
  return nullptr;
}
// for debug
void ParamNode::print() const {
  std::cout << params.size() << " params: " << std::endl;
  for (const Node* n : params) {
    n->eval()->print();
  }
}

const Literal* CallNode::eval() const {
  TableManager& tm = TableManager::getInstance();
  const Literal* res = new NoneLiteral();
  const Node* func = tm.getFunc(funcName);

  // if function has parameters, handle parameters firstly.
  if (tm.findParams(funcName)) {
    Node* paramsNode = tm.getParams(funcName);
    const std::vector<Node*> params = static_cast<ParamNode*>(paramsNode)->getParams();
    const std::vector<Node*> args = static_cast<ParamNode*>(arguments)->getParams();
    // check whether arguments is valid
    // TODO: support *args, **kwwargs
    if (params.size() != args.size()) {
      throw std::string("TypeError:") + funcName + std::string("() takes exactly ")
          + std::to_string(params.size()) + std::string(" arguments") + std::string("(") + std::to_string(args.size()) + std::string(" given)");
    }

    tm.pushScope();
    // evaluate args
    for (unsigned long i = 0; i < args.size(); ++i) {
      const std::string param = static_cast<IdentNode*>(params[i])->getIdent();
      const Literal* val = args[i]->eval();
      tm.setValue(param, val);
    }
  }

  // already push scope above
  if (!tm.findParams(funcName)) {
    tm.pushScope();
  }

  func->eval();
  if (tm.needReturnValue()) {
    res =tm.getReturnValue();
  }
  tm.popScope();
  tm.setValue(funcName, res);

  return res;
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

const Literal* AsgBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("Error: left or right of BinaryNode is null");
  }
  const Literal* res = right->eval();
  const std::string n = getIdent();
  TableManager::getInstance().setValue(n, res);
  return res;
}
const std::string AsgBinaryNode::getIdent() const {
  return static_cast<IdentNode*>(left)->getIdent();
}

const Literal* AddBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("Error: left or right of BinaryNode is null");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  //return (*x+*y);
  return (*x).operator+(*y);
}

const Literal* SubBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("Error: left or right of BinaryNode is null");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return ((*x)-(*y));
}

const Literal* MulBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("Error: left or right of BinaryNode is null");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return ((*x)*(*y));
}

const Literal* DivBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("Error: left or right of BinaryNode is null");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return ((*x)/(*y));
}

const Literal* IntDivBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("Error: left or right of BinaryNode is null");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return (*x).intDiv(*y);
}

const Literal* ModBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("Error: left or right of BinaryNode is null");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return ((*x) % (*y));
}

const Literal* ExpBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("Error: left or right of BinaryNode is null");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return (*x) ^ (*y);
}


const Literal* LessBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("Error: left or right of BinaryNode is null");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return (*x) < (*y);
}

const Literal* GreaterBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("Error: left or right of BinaryNode is null");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return (*x) > (*y);
}

const Literal* EqualBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("Error: left or right of BinaryNode is null");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return (*x) == (*y);
}

const Literal* GrtEqBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("Error: left or right of BinaryNode is null");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return (*x) >= (*y);
}

const Literal* LessEqBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("Error: left or right of BinaryNode is null");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return (*x) <= (*y);
}