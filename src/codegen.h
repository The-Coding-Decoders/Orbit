#ifndef CODEGEN_H
#define CODEGEN_H

#include "ast.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"

class CodeGen {
public:
  CodeGen();
  void generate(ASTNode *node);
  void dump(llvm::raw_ostream &out);

private:
  llvm::LLVMContext context;
  llvm::IRBuilder<> builder;
  llvm::Module *module;
  llvm::Value *visit(ASTNode *node);
  llvm::Value *visit(NumberNode *node);
  llvm::Value *visit(BinaryOpNode *node);
};

#endif
