#ifndef PARSER_H
#define PARSER_H

#include "ast.h"
#include "lexer.h"

class Parser {
public:
  Parser(Lexer &lexer);
  ASTNode *parse();

private:
  Lexer &lexer;
  int curTok;
  ASTNode *parseExpression();
  ASTNode *parsePrimary();
  ASTNode *parseBinOpRHS(int exprPrec, ASTNode *LHS);
  ASTNode *parseNumberExpr();
  int getNextToken();
};

#endif
