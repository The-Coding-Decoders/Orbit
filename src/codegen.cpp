#include "codegen.h"
#include "llvm/ADT/APFloat.h"

CodeGen::CodeGen() : builder(context) {
  module = new llvm::Module("MyModule", context);
}

void CodeGen::generate(ASTNode *node) { visit(node); }

void CodeGen::dump(llvm::raw_ostream &out) { module->print(out, nullptr); }

llvm::Value *CodeGen::visit(ASTNode *node) {
  if (auto numberNode = dynamic_cast<NumberNode *>(node)) {
    return visit(numberNode);
  } else if (auto binaryOpNode = dynamic_cast<BinaryOpNode *>(node)) {
    return visit(binaryOpNode);
  }
  return nullptr;
}

llvm::Value *CodeGen::visit(NumberNode *node) {
  return llvm::ConstantFP::get(context, llvm::APFloat((double)node->getValue()));
}

llvm::Value *CodeGen::visit(BinaryOpNode *node) {
  llvm::Value *L = visit(node->getLeft());
  llvm::Value *R = visit(node->getRight());
  if (!L || !R) {
    return nullptr;
  }

  switch (node->getOp()) {
  case '+':
    return builder.CreateFAdd(L, R, "addtmp");
  case '-':
    return builder.CreateFSub(L, R, "subtmp");
  case '*':
    return builder.CreateFMul(L, R, "multmp");
  case '<':
    L = builder.CreateFCmpULT(L, R, "cmptmp");
    return builder.CreateUIToFP(L, llvm::Type::getDoubleTy(context),
                                "booltmp");
  default:
    return nullptr;
  }
}
