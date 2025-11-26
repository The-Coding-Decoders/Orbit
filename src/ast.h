#ifndef AST_H
#define AST_H

class ASTNode {
public:
  virtual ~ASTNode() {}
};

class NumberNode : public ASTNode {
public:
  NumberNode(int value) : value(value) {}
  int getValue() const { return value; }

private:
  int value;
};

class BinaryOpNode : public ASTNode {
public:
  BinaryOpNode(char op, ASTNode *left, ASTNode *right)
      : op(op), left(left), right(right) {}
  char getOp() const { return op; }
  ASTNode *getLeft() const { return left; }
  ASTNode *getRight() const { return right; }

private:
  char op;
  ASTNode *left;
  ASTNode *right;
};

#endif
