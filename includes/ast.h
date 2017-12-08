#pragma once

//  Declarations for a calculator that builds an AST
//  and a graphical representation of the AST.
//  by Brian Malloy

#include <iostream>
#include <string>
#include <map>
#include "literal.h"

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
  AsgBinaryNode(Node* left, Node* right);
  virtual const Literal* eval() const;
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
  GrtEqBinaryNode(Node* left, Node* right) : BinaryNode(left,right) {}
  virtual const Literal* eval() const;
};

class lesEqBinaryNode : public BinaryNode {
public:
  lesEqBinaryNode(Node* left, Node* right) : BinaryNode(left,right) {}
  virtual const Literal* eval() const;
};
