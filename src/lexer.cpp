#include "lexer.h"
#include <fstream>
#include <cctype>

Lexer::Lexer(const std::string &filename) : lastChar(' '), currentIndex(0) {
  std::ifstream file(filename);
  if (file.is_open()) {
    source.assign((std::istreambuf_iterator<char>(file)),
                  (std::istreambuf_iterator<char>()));
  }
}

int Lexer::getTok() {
  while (isspace(lastChar)) {
    lastChar = source[currentIndex++];
  }

  if (isalpha(lastChar)) { // identifier: [a-zA-Z][a-zA-Z0-9]*
    identifier = lastChar;
    while (isalnum((lastChar = source[currentIndex++])))
      identifier += lastChar;

    if (identifier == "def")
      return TOK_DEF;
    if (identifier == "extern")
      return TOK_EXTERN;
    return TOK_IDENTIFIER;
  }

  if (isdigit(lastChar) || lastChar == '.') { // Number: [0-9.]+
    std::string numStr;
    do {
      numStr += lastChar;
      lastChar = source[currentIndex++];
    } while (isdigit(lastChar) || lastChar == '.');

    numVal = strtod(numStr.c_str(), 0);
    return TOK_NUMBER;
  }

  if (lastChar == '#') {
    // Comment until end of line.
    do
      lastChar = source[currentIndex++];
    while (lastChar != EOF && lastChar != '\n' && lastChar != '\r');

    if (lastChar != EOF)
      return getTok();
  }

  if (currentIndex > source.length())
    return TOK_EOF;

  int thisChar = lastChar;
  lastChar = source[currentIndex++];
  return thisChar;
}
