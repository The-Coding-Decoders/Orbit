#include "lexer.h"
#include "parser.h"
#include "codegen.h"
#include "llvm/Support/raw_ostream.h"
#include <iostream>

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <input file>" << std::endl;
    return 1;
  }

  Lexer lexer(argv[1]);
  Parser parser(lexer);
  ASTNode *node = parser.parse();
  if (!node) {
    std::cerr << "Error parsing input" << std::endl;
    return 1;
  }

  CodeGen codegen;
  codegen.generate(node);

  codegen.dump(llvm::outs());

  return 0;
}
