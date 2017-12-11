#include <cmath>

#include "node.h"
#include "poolOfNodes.h"

class Literal : public Node {
public:
  virtual ~Literal() {}

  virtual const Literal* operator+(const Literal& rhs) const =0;
  virtual const Literal* opPlus(float) const =0;
  virtual const Literal* opPlus(int) const =0;

  virtual const Literal* operator*(const Literal& rhs) const =0;
  virtual const Literal* opMult(float) const =0;
  virtual const Literal* opMult(int) const =0;

  virtual const Literal* operator-(const Literal& rhs) const =0;
  virtual const Literal* opSubt(float) const =0;
  virtual const Literal* opSubt(int) const =0;

  virtual const Literal* operator/(const Literal& rhs) const =0;
  virtual const Literal* opDiv(float) const =0;
  virtual const Literal* opDiv(int) const =0;

  virtual const Literal* intDiv(const Literal& rhs) const = 0;
  virtual const Literal* opIntDiv(float) const = 0;
  virtual const Literal* opIntDiv(int) const = 0;

  virtual const Literal* operator%(const Literal& rhs) const = 0;
  virtual const Literal* opMod(float) const = 0;
  virtual const Literal* opMod(int) const = 0;

  virtual const Literal* operator^(const Literal& rhs) const = 0;
  virtual const Literal* opExp(float) const = 0;
  virtual const Literal* opExp(int) const = 0;

  // comparison

  virtual const Literal* operator<(const Literal& rhs) const = 0;
  virtual const Literal* opLess(float) const = 0;
  virtual const Literal* opLess(int) const = 0;

  virtual const Literal* operator>(const Literal& rhs) const = 0;
  virtual const Literal* opGreater(float) const = 0;
  virtual const Literal* opGreater(int) const = 0;

  virtual const Literal* operator==(const Literal& rhs) const = 0;
  virtual const Literal* opEqual(float) const = 0;
  virtual const Literal* opEqual(int) const = 0;

  virtual const Literal* operator>=(const Literal& rhs) const = 0;
  virtual const Literal* opGrtEq(float) const = 0;
  virtual const Literal* opGrtEq(int) const = 0;

  virtual const Literal* operator<=(const Literal& rhs) const = 0;
  virtual const Literal* opLessEq(float) const = 0;
  virtual const Literal* opLessEq(int) const = 0;

  // val
  virtual const Literal* eval() const = 0;
  virtual const Literal* unopVal(char op) const = 0;
  virtual bool boolValue() const = 0;

  virtual void print() const {
    std::cout << "No Way" << std::endl;
  }
};

class FloatLiteral: public Literal {
public:
  FloatLiteral(float _val): val(_val) {}

  virtual const Literal* operator+(const Literal& rhs) const  {
    return rhs.opPlus(val);
  }
  virtual const Literal* opPlus(float lhs) const  {
    const Literal* node = new FloatLiteral(lhs + val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opPlus(int lhs) const  {
    const Literal* node = new FloatLiteral(lhs + val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* operator-(const Literal& rhs) const  {
    return rhs.opSubt(val);
  }
  virtual const Literal* opSubt(float lhs) const  {
    const Literal* node = new FloatLiteral(lhs - val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opSubt(int lhs) const  {
    const Literal* node = new FloatLiteral(lhs - val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* operator*(const Literal& rhs) const  {
    return rhs.opMult(val);
  }
  virtual const Literal* opMult(float lhs) const  {
    const Literal* node = new FloatLiteral(lhs * val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opMult(int lhs) const  {
    const Literal* node = new FloatLiteral(static_cast<float>(lhs) * val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* operator/(const Literal& rhs) const  {
    return rhs.opDiv(val);
  }
  virtual const Literal* opDiv(float lhs) const  {
    if ( val == 0 ) throw std::string("Zero Division Error");
    const Literal* node = new FloatLiteral(lhs / val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opDiv(int lhs) const  {
    if ( val == 0 ) throw std::string("Zero Division Error");
    const Literal* node = new FloatLiteral(lhs / val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* intDiv(const Literal& rhs) const {
    return rhs.opIntDiv(val);
  }
  virtual const Literal* opIntDiv(float lhs) const {
    if ( val == 0 ) throw std::string("Zero Division Error");
    const Literal* node = new FloatLiteral(std::floor(lhs / val));
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opIntDiv(int lhs) const {
    return this->opIntDiv((float)lhs);
  }

  virtual const Literal* operator%(const Literal& rhs) const {
    return rhs.opMod(val);
  }
  virtual const Literal* opMod(float lhs) const {
    if ( val == 0 ) throw std::string("Zero Division Error");
    float r = fmod((fmod(lhs, val) + val), val);
    const Literal* node = new FloatLiteral(r);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opMod(int lhs) const {
    return this->opMod((float)lhs);
  }

  virtual const Literal* operator^(const Literal& rhs) const {
    return rhs.opExp(val);
  }
  virtual const Literal* opExp(float lhs) const {
    if ( lhs == 0 && val < 0 ) {
      throw std::string("ZeroDivisionError: 0.0 cannot be raised to a negative power");
    }
    const Literal* node = new FloatLiteral(pow(lhs, val));
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opExp(int lhs) const {
    if ( lhs == 0 && val < 0 ) {
      throw std::string("ZeroDivisionError: 0 cannot be raised to a negative power");
    }
    const Literal* node = new FloatLiteral(pow(lhs, val));
    PoolOfNodes::getInstance().add(node);
    return node;
  }


  virtual const Literal* operator<(const Literal& rhs) const {
    return rhs.opLess(val);
  }
  virtual const Literal* opLess(float lhs) const {
    const Literal* node;
    if (lhs < val) {
      node = new FloatLiteral(1);
    } else {
      node = new FloatLiteral(0);
    }
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opLess(int lhs) const {
    return this->opLess((float)lhs);
  }

  virtual const Literal* operator>(const Literal& rhs) const {
    return rhs.opGreater(val);
  }
  virtual const Literal* opGreater(float lhs) const {
    const Literal* node;
    if (lhs > val) {
      node = new FloatLiteral(1);
    } else {
      node = new FloatLiteral(0);
    }
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opGreater(int lhs) const {
    return this->opGreater((float)lhs);
  }

  virtual const Literal* operator==(const Literal& rhs) const {
    return rhs.opEqual(val);
  }
  virtual const Literal* opEqual(float lhs) const {
    const Literal* node;
    if (lhs == val) {
      node = new FloatLiteral(1);
    } else {
      node = new FloatLiteral(0);
    }
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opEqual(int lhs) const {
    return this->opEqual((float)lhs);
  }

  virtual const Literal* operator>=(const Literal& rhs) const {
    return rhs.opGrtEq(val);
  }
  virtual const Literal* opGrtEq(float lhs) const {
    const Literal* node;
    if (lhs >= val) {
      node = new FloatLiteral(1);
    } else {
      node = new FloatLiteral(0);
    }
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opGrtEq(int lhs) const {
    return this->opGrtEq((float)lhs);
  }

  virtual const Literal* operator<=(const Literal& rhs) const {
    return rhs.opLessEq(val);
  }
  virtual const Literal* opLessEq(float lhs) const {
    const Literal* node;
    if (lhs <= val) {
      node = new FloatLiteral(1);
    } else {
      node = new FloatLiteral(0);
    }
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opLessEq(int lhs) const {
    return this->opLessEq((float)lhs);
  }

  virtual const Literal* eval() const { return this; }
  virtual const Literal* unopVal(char op) const {
    switch(op) {
      case '-': {
        const Literal* node = new FloatLiteral(-val);
        PoolOfNodes::getInstance().add(node);
        return node;
      }
      case '+':
      case '~':
      default:
        return this;
    };
  }

  virtual bool boolValue() const {
    return val != 0.0; // true: not equal to 0
  }

  virtual void print() const {
    if ((int)val == val) {
      std::cout << val << ".0" << std::endl;
    } else {
      std::cout << val << std::endl;
    }
  }
private:
  float val;
};

class IntLiteral: public Literal {
public:
 IntLiteral(int _val): val(_val) {}

  virtual const Literal* operator+(const Literal& rhs) const  {
    return rhs.opPlus(val);
  }
  virtual const Literal* opPlus(float lhs) const  {
    const Literal* node = new FloatLiteral(static_cast<float>(val) + lhs);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opPlus(int lhs) const  {
    const Literal* node = new IntLiteral(lhs + val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* operator-(const Literal& rhs) const  {
    return rhs.opSubt(val);
  }
  virtual const Literal* opSubt(float lhs) const  {
    const Literal* node = new FloatLiteral(lhs - val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opSubt(int lhs) const  {
    const Literal* node = new IntLiteral(lhs - val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* operator*(const Literal& rhs) const  {
    return rhs.opMult(val);
  }
  virtual const Literal* opMult(float lhs) const  {
    const Literal* node = new FloatLiteral(lhs * val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opMult(int lhs) const  {
    const Literal* node = new IntLiteral(lhs * val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* operator/(const Literal& rhs) const  {
    return rhs.opDiv(val);
  }
  virtual const Literal* opDiv(float lhs) const  {
    if ( val == 0 ) throw std::string("Zero Division Error");
    const Literal* node = new FloatLiteral(lhs / val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opDiv(int lhs) const  {
    if ( val == 0 ) throw std::string("Zero Division Error");
    float res = (float)lhs / val;
    const Literal* node = new IntLiteral(std::floor(res));
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* intDiv(const Literal& rhs) const {
    return rhs.opIntDiv(val);
  }
  virtual const Literal* opIntDiv(float lhs) const {
    if ( val == 0 ) throw std::string("Zero Division Error");
    const Literal* node = new FloatLiteral(std::floor(lhs / val));
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opIntDiv(int lhs) const {
    if ( val == 0 ) throw std::string("Zero Division Error");
    float res = (float)lhs / val;
    const Literal* node = new IntLiteral(std::floor(res));
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* operator%(const Literal& rhs) const {
    return rhs.opMod(val);
  }

  virtual const Literal* opMod(float lhs) const {
    if ( val == 0 ) throw std::string("Zero Division Error");
    float r = fmod((fmod(lhs, val) + val), val);
    const Literal* node = new FloatLiteral(r);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opMod(int lhs) const {
    if ( val == 0 ) throw std::string("Zero Division Error");
    int r = ((lhs % val) + val) % val;
    const Literal* node = new IntLiteral(r);
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* operator^(const Literal& rhs) const {
    return rhs.opExp(val);
  }
  virtual const Literal* opExp(float lhs) const {
    if ( lhs == 0 && val < 0 ) {
      throw std::string("ZeroDivisionError: 0.0 cannot be raised to a negative power");
    }
    const Literal* node = new FloatLiteral(pow(lhs, val));
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opExp(int lhs) const {
    if ( lhs == 0 && val < 0 ) {
      throw std::string("ZeroDivisionError: 0 cannot be raised to a negative power");
    }
    const Literal* node = new IntLiteral(pow(lhs, val));
    PoolOfNodes::getInstance().add(node);
    return node;
  }


  virtual const Literal* operator<(const Literal& rhs) const {
    return rhs.opLess(val);
  }
  virtual const Literal* opLess(float lhs) const {
    const Literal* node;
    if (lhs < val) {
      node = new IntLiteral(1);
    } else {
      node = new IntLiteral(0);
    }
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opLess(int lhs) const {
    return this->opLess((float)lhs);
  }

  virtual const Literal* operator>(const Literal& rhs) const {
    return rhs.opGreater(val);
  }
  virtual const Literal* opGreater(float lhs) const {
    const Literal* node;
    if (lhs > val) {
      node = new IntLiteral(1);
    } else {
      node = new IntLiteral(0);
    }
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opGreater(int lhs) const {
    return this->opGreater((float)lhs);
  }

  virtual const Literal* operator==(const Literal& rhs) const {
    return rhs.opEqual(val);
  }
  virtual const Literal* opEqual(float lhs) const {
    const Literal* node;
    if (lhs == val) {
      node = new IntLiteral(1);
    } else {
      node = new IntLiteral(0);
    }
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opEqual(int lhs) const {
    return this->opEqual((float)lhs);
  }

  virtual const Literal* operator>=(const Literal& rhs) const {
    return rhs.opGrtEq(val);
  }
  virtual const Literal* opGrtEq(float lhs) const {
    const Literal* node;
    if (lhs >= val) {
      node = new IntLiteral(1);
    } else {
      node = new IntLiteral(0);
    }
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opGrtEq(int lhs) const {
    return this->opGrtEq((float)lhs);
  }

  virtual const Literal* operator<=(const Literal& rhs) const {
    return rhs.opLessEq(val);
  }
  virtual const Literal* opLessEq(float lhs) const {
    const Literal* node;
    if (lhs <= val) {
      node = new IntLiteral(1);
    } else {
      node = new IntLiteral(0);
    }
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opLessEq(int lhs) const {
    return this->opLessEq((float)lhs);
  }

  virtual const Literal* eval() const { return this; }
  virtual const Literal* unopVal(char op) const {
    switch(op) {
      case '-': {
        const Literal* node = new IntLiteral(-val);
        PoolOfNodes::getInstance().add(node);
        return node;
      }
      case '+':
      case '~':
      default:
        return this;
    };
  }
  virtual bool boolValue() const {
    return val != 0;
  }

  virtual void print() const {
    std::cout << val << std::endl;
  }
private:
  int val;
};

class NoneLiteral: public Literal {
public:
  NoneLiteral(): val("None") {}
  virtual const Literal* operator+(const Literal& rhs) const  {
    return rhs.opPlus(0);
  }
  virtual const Literal* opPlus(float lhs) const {
    throw std::string("TypeError: unsupported operand type(s) for +: NoneType and ") + std::to_string(lhs);
  }
  virtual const Literal* opPlus(int lhs) const {
    throw std::string("TypeError: unsupported operand type(s) for +: NoneType and ") + std::to_string(lhs);
  }

  virtual const Literal* operator-(const Literal& rhs) const  {
    return rhs.opSubt(0);
  }
  virtual const Literal* opSubt(float lhs) const {
    throw std::string("TypeError: unsupported operand type(s) for -: NoneType and ") + std::to_string(lhs);
  }
  virtual const Literal* opSubt(int lhs) const {
    throw std::string("TypeError: unsupported operand type(s) for -: NoneType and ") + std::to_string(lhs);
  }

  virtual const Literal* operator*(const Literal& rhs) const  {
    return rhs.opMult(0);
  }
  virtual const Literal* opMult(float lhs) const {
    throw std::string("TypeError: unsupported operand type(s) for *: NoneType and ") + std::to_string(lhs);
  }
  virtual const Literal* opMult(int lhs) const {
    throw std::string("TypeError: unsupported operand type(s) for *: NoneType and ") + std::to_string(lhs);
  }

  virtual const Literal* operator/(const Literal& rhs) const  {
    return rhs.opDiv(0);
  }
  virtual const Literal* opDiv(float lhs) const {
    throw std::string("TypeError: unsupported operand type(s) for /: NoneType and ") + std::to_string(lhs);
  }
  virtual const Literal* opDiv(int lhs) const {
    throw std::string("TypeError: unsupported operand type(s) for /: NoneType and ") + std::to_string(lhs);
  }

  virtual const Literal* intDiv(const Literal& rhs) const {
    return rhs.opIntDiv(0);
  }
  virtual const Literal* opIntDiv(float lhs) const {
    throw std::string("TypeError: unsupported operand type(s) for //: NoneType and ") + std::to_string(lhs);
  }
  virtual const Literal* opIntDiv(int lhs) const {
    throw std::string("TypeError: unsupported operand type(s) for //: NoneType and ") + std::to_string(lhs);
  }

  virtual const Literal* operator%(const Literal& rhs) const {
    return rhs.opMod(0);
  }
  virtual const Literal* opMod(float lhs) const {
    throw std::string("TypeError: unsupported operand type(s) for %: NoneType and ") + std::to_string(lhs);
  }
  virtual const Literal* opMod(int lhs) const {
    throw std::string("TypeError: unsupported operand type(s) for %: NoneType and ") + std::to_string(lhs);
  }

  virtual const Literal* operator^(const Literal& rhs) const {
    return rhs.opExp(0);
  }
  virtual const Literal* opExp(float lhs) const {
    throw std::string("TypeError: unsupported operand type(s) for **: NoneType and ") + std::to_string(lhs);
  }
  virtual const Literal* opExp(int lhs) const {
    throw std::string("TypeError: unsupported operand type(s) for **: NoneType and ") + std::to_string(lhs);
  }

  virtual const Literal* operator<(const Literal& rhs) const {
    return rhs.opLess(0);
  }
  virtual const Literal* opLess(float lhs) const {
    throw std::string("TypeError: unsupported operand type(s) for <: NoneType and ") + std::to_string(lhs);
  }
  virtual const Literal* opLess(int lhs) const {
    throw std::string("TypeError: unsupported operand type(s) for <: NoneType and ") + std::to_string(lhs);
  }

  virtual const Literal* operator>(const Literal& rhs) const {
    return rhs.opGreater(0);
  }
  virtual const Literal* opGreater(float lhs) const {
    throw std::string("TypeError: unsupported operand type(s) for >: NoneType and ") + std::to_string(lhs);
  }
  virtual const Literal* opGreater(int lhs) const {
    throw std::string("TypeError: unsupported operand type(s) for >: NoneType and ") + std::to_string(lhs);
  }

  virtual const Literal* operator==(const Literal& rhs) const {
    return rhs.opEqual(0);
  }
  virtual const Literal* opEqual(float lhs) const {
    throw std::string("TypeError: unsupported operand type(s) for ==: NoneType and ") + std::to_string(lhs);
  }
  virtual const Literal* opEqual(int lhs) const {
    throw std::string("TypeError: unsupported operand type(s) for ==: NoneType and ") + std::to_string(lhs);
  }

  virtual const Literal* operator>=(const Literal& rhs) const {
    return rhs.opGrtEq(0);
  }
  virtual const Literal* opGrtEq(float lhs) const {
    throw std::string("TypeError: unsupported operand type(s) for >=: NoneType and ") + std::to_string(lhs);
  }
  virtual const Literal* opGrtEq(int lhs) const {
    throw std::string("TypeError: unsupported operand type(s) for >=: NoneType and ") + std::to_string(lhs);
  }

  virtual const Literal* operator<=(const Literal& rhs) const {
    return rhs.opLessEq(0);
  }
  virtual const Literal* opLessEq(float lhs) const {
    throw std::string("TypeError: unsupported operand type(s) for <=: NoneType and ") + std::to_string(lhs);
  }
  virtual const Literal* opLessEq(int lhs) const {
    throw std::string("TypeError: unsupported operand type(s) for <=: NoneType and ") + std::to_string(lhs);
  }

  virtual const Literal* eval() const { return this; }
  virtual const Literal* unopVal(char op) const {
    throw std::string("TypeError: unsupported operation on NoneType for") + std::to_string(op);
  }
  virtual bool boolValue() const {
    return false;
  }

  virtual void print() const {
    std::cout << val << std::endl;
  }

private:
  std::string val;
};