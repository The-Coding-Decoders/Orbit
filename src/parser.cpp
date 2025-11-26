#include "parser.h"
#include <map>

static std::map<char, int> BinopPrecedence;

Parser::Parser(Lexer &lexer) : lexer(lexer), curTok(0) {
  BinopPrecedence['<'] = 10;
  BinopPrecedence['+'] = 20;
  BinopPrecedence['-'] = 20;
  BinopPrecedence['*'] = 40; 
}

int Parser::getNextToken() { return curTok = lexer.getTok(); }

ASTNode *Parser::parseNumberExpr() {
  auto result = new NumberNode(lexer.getNumVal());
  getNextToken(); // consume the number
  return result;
}

ASTNode *Parser::parseExpression() {
  ASTNode *LHS = parsePrimary();
  if (!LHS)
    return nullptr;
  return parseBinOpRHS(0, LHS);
}

ASTNode *Parser::parsePrimary() {
    return parseNumberExpr();
}

ASTNode *Parser::parseBinOpRHS(int exprPrec, ASTNode *LHS) {
  while (true) {
    int tokPrec = BinopPrecedence[curTok];

    if (tokPrec < exprPrec) {
      return LHS;
    }

    int binOp = curTok;
    getNextToken(); // eat binop

    ASTNode *RHS = parsePrimary();
    if (!RHS)
      return nullptr;

    int nextPrec = BinopPrecedence[curTok];
    if (tokPrec < nextPrec) {
      RHS = parseBinOpRHS(tokPrec + 1, RHS);
      if (!RHS)
        return nullptr;
    }

    LHS = new BinaryOpNode(binOp, LHS, RHS);
  }
}

ASTNode *Parser::parse() {
  getNextToken();
  return parseExpression();
}
