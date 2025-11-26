#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

enum Token {
  TOK_EOF = -1,
  TOK_DEF = -2,
  TOK_EXTERN = -3,
  TOK_IDENTIFIER = -4,
  TOK_NUMBER = -5,
};

class Lexer {
public:
  Lexer(const std::string &filename);
  int getTok();
  std::string getIdentifier() const { return identifier; }
  double getNumVal() const { return numVal; }

private:
  std::string source;
  int lastChar;
  int currentIndex;
  std::string identifier;
  double numVal;
};

#endif
