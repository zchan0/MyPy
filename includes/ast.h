#pragma once

//  Declarations for a calculator that builds an AST
//  and a graphical representation of the AST.
//  by Brian Malloy

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "literal.h"
#include "tableManager.h"

extern void yyerror(const char*);
extern void yyerror(const char*, const char);

class IdentNode : public Node {
public:
  IdentNode(const std::string id) : Node(), ident(id) { }
  virtual ~IdentNode() {}
  const std::string getIdent() const { return ident; }
  virtual const Literal* eval() const;
private:
  std::string ident;
};

class NullNode : public Node {
public:
  static NullNode* getInstance() {
    if (!instance) instance = new NullNode();
    return instance;
  }
  virtual ~NullNode() { if (instance) delete instance; }
  virtual const Literal* eval() const { return val; }
  NullNode(const NullNode&) = delete;
  NullNode& operator=(const NullNode&) = delete;
private:
  NullNode() : Node(), val(nullptr) {}
  Literal* val;
  static NullNode* instance;
};

class PrintNode : public Node {
public:
  PrintNode(Node* n) : Node(), node(n) {}
  virtual ~PrintNode() {}
  virtual const Literal* eval() const;
  Node* getNode() const { return node; }
  PrintNode(const PrintNode&) = delete;
  PrintNode& operator=(const PrintNode&) = delete;
private:
  Node* node;
};

class IfNode : public Node {
public:
  IfNode(Node* cmp, Node* if_branch, Node* else_branch) : Node(), comparison(cmp), ifBranch(if_branch), elseBranch(else_branch) {}
  virtual ~IfNode() {}
  virtual const Literal* eval() const;
  Node* getIfBranch() const { return ifBranch; }
  Node* getElseBranch() const { return elseBranch; }
  IfNode(const IfNode&) = delete;
  IfNode& operator=(const IfNode&) = delete;
private:
  Node* comparison; // cannot be null
  Node* ifBranch;
  Node* elseBranch;
};

class SuiteNode : public Node {
public:
  SuiteNode() : Node(), stmts() {}
  virtual ~SuiteNode() {}
  virtual const Literal* eval() const;
  void preeval() const;
  void append(Node*);
  SuiteNode(const SuiteNode&) = delete;
  SuiteNode& operator=(const SuiteNode&) = delete;
private:
  std::vector<Node*> stmts;
};

class FuncNode : public Node {
public:
  FuncNode(char* n, Node* p, Node* s) : Node(), name(n), suite(s), params(p) {}
  virtual ~FuncNode() {}
  virtual const Literal* eval() const;
  FuncNode(const FuncNode&) = delete;
  FuncNode& operator=(const FuncNode&) = delete;
private:
  std::string name;
  Node* suite, *params;
};

class ParamNode : public Node {
public:
  ParamNode() : Node(), params() {}
  virtual ~ParamNode() {}
  virtual const Literal* eval() const;
  void append(Node*);
  void print() const;
  const std::vector<Node*> getParams();
  ParamNode(const ParamNode&) = delete;
  ParamNode& operator=(const ParamNode&) = delete;
private:
  std::vector<Node*> params;
};

class CallNode : public Node {
public:
  CallNode(const std::string& n, Node* a)  : Node(), funcName(n), arguments(a) { }
  virtual ~CallNode() {}
  virtual const Literal* eval() const;
  CallNode(const CallNode&) = delete;
  CallNode& operator=(const CallNode&) = delete;
private:
  std::string funcName;
  Node* arguments;
};

class ReturnNode : public Node {
public:
  ReturnNode() : Node(), testlist(nullptr) {}
  ReturnNode(Node* n) : Node(), testlist(n) {}
  virtual ~ReturnNode() {}
  virtual const Literal* eval() const;
  ReturnNode(const ReturnNode&)  = delete;
  ReturnNode& operator=(const ReturnNode&) = delete;
private:
  Node* testlist;
};

class UnaryNode : public Node {
public:
  UnaryNode(char c, Node* n) : Node(), op(c), node(n) {}
  virtual ~UnaryNode() {}
  virtual const Literal* eval() const;
  Node* getNode() const { return node; }
  UnaryNode(const UnaryNode&) = delete;
  UnaryNode& operator=(const UnaryNode&) = delete;
private:
  char op; // unary operator: +, -, ~
  Node* node;
};

class BinaryNode : public Node {
public:
  BinaryNode(Node* l, Node* r) : Node(), left(l), right(r) {}
  virtual const Literal* eval() const = 0;
  Node* getLeft()  const { return left; }
  Node* getRight() const { return right; }
  BinaryNode(const BinaryNode&) = delete;
  BinaryNode& operator=(const BinaryNode&) = delete;
protected:
  Node *left;
  Node *right;
};

class AsgBinaryNode : public BinaryNode {
public:
  AsgBinaryNode(Node* left, Node* right) : BinaryNode(left, right) { }
  virtual const Literal* eval() const;
  const std::string getIdent() const;
};

class AddBinaryNode : public BinaryNode {
public:
  AddBinaryNode(Node* left, Node* right) : BinaryNode(left, right) { }
  virtual const Literal* eval() const;
};

class SubBinaryNode : public BinaryNode {
public:
  SubBinaryNode(Node* left, Node* right) : BinaryNode(left, right) { }
  virtual const Literal* eval() const;
};

class MulBinaryNode : public BinaryNode {
public:
  MulBinaryNode(Node* left, Node* right) : BinaryNode(left, right) {}
  virtual const Literal* eval() const;
};

class DivBinaryNode : public BinaryNode {
public:
  DivBinaryNode(Node* left, Node* right) : BinaryNode(left, right) { }
  virtual const Literal* eval() const;
};

class IntDivBinaryNode : public BinaryNode {
public:
  IntDivBinaryNode(Node* left, Node* right) : BinaryNode(left, right) { }
  virtual const Literal* eval() const;
};

class ModBinaryNode : public BinaryNode {
public:
  ModBinaryNode(Node* left, Node* right) : BinaryNode(left, right) { }
  virtual const Literal* eval() const;
};

class ExpBinaryNode : public BinaryNode {
public:
  ExpBinaryNode(Node* left, Node* right) : BinaryNode(left, right) { }
  virtual const Literal* eval() const;
};

class LessBinaryNode : public BinaryNode {
public:
  LessBinaryNode(Node* left, Node* right) : BinaryNode(left, right) {}
  virtual const Literal* eval() const;
};

class GreaterBinaryNode : public BinaryNode {
public:
  GreaterBinaryNode(Node* left, Node* right) : BinaryNode(left, right) {}
  virtual const Literal* eval() const;
};

class EqualBinaryNode : public BinaryNode {
public:
  EqualBinaryNode(Node* left, Node* right) : BinaryNode(left, right) {}
  virtual const Literal* eval() const;
};

class GrtEqBinaryNode : public BinaryNode {
public:
  GrtEqBinaryNode(Node* left, Node* right) : BinaryNode(left, right) {}
  virtual const Literal* eval() const;
};

class LessEqBinaryNode : public BinaryNode {
public:
  LessEqBinaryNode(Node* left, Node* right) : BinaryNode(left, right) {}
  virtual const Literal* eval() const;
};
