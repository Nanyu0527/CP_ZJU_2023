#include "AST.h"
#include "CodeGenerator.hpp"



llvm::Value *IfStmNode::genCode(CodeGenerator & gen) {
    llvm::Function* func = gen.currentFunc;
    llvm::BasicBlock*  condition_block = llvm::BasicBlock::Create(globalContext, "C_block", func);
    llvm::BasicBlock*  if_block = llvm::BasicBlock::Create(globalContext, "I_block", func);
    llvm::BasicBlock*  end_block = llvm::BasicBlock::Create(globalContext, "E_block", func);
    llvm::Value* condition_value = exp->genCode(gen);
    Builder.CreateCondBr(condition_value, if_block, end_block);

    Builder.SetInsertPoint(if_block);
    gen.symbolTable_stack.push_back({});
    block->genCode(gen);
    gen.symbolTable_stack.pop_back();
    if (!Builder.GetInsertBlock()->getTerminator()){
        Builder.CreateBr(end_block);
    }

    Builder.SetInsertPoint(end_block);
    return nullptr;
}

llvm::Value *IfElseStmNode::genCode(CodeGenerator & gen) {
    llvm::Function* func = gen.currentFunc;
    llvm::BasicBlock*  condition_block = llvm::BasicBlock::Create(globalContext, "C_block", func);
    llvm::BasicBlock*  if_block = llvm::BasicBlock::Create(globalContext, "I_block", func);
    llvm::BasicBlock*  else_block = llvm::BasicBlock::Create(globalContext, "EL_block", func);
    llvm::BasicBlock*  end_block = llvm::BasicBlock::Create(globalContext, "E_block", func);
    llvm::Value* condition_value = exp->genCode(gen);
    Builder.CreateCondBr(condition_value, if_block, else_block);

    Builder.SetInsertPoint(if_block);
    gen.symbolTable_stack.push_back({});
    ifblock->genCode(gen);
    gen.symbolTable_stack.pop_back();
    if (!Builder.GetInsertBlock()->getTerminator()){
        Builder.CreateBr(end_block);
    }

    Builder.SetInsertPoint(else_block);
    gen.symbolTable_stack.push_back({});
    elseblock->genCode(gen);
    gen.symbolTable_stack.pop_back();
    if (!Builder.GetInsertBlock()->getTerminator()){
        Builder.CreateBr(end_block);
    }
    
    Builder.SetInsertPoint(end_block);
    return nullptr;
}