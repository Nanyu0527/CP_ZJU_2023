#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <string>
#include <exception>
#include <llvm/IR/Value.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/IR/IRPrintingPasses.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/GlobalVariable.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/IR/ValueSymbolTable.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Verifier.h>
#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/ExecutionEngine/Interpreter.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/SectionMemoryManager.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/ManagedStatic.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/DynamicLibrary.h>
#include <llvm/Target/TargetMachine.h>
using namespace std;
stack<llvm::BasicBlock *> GlobalAfterBB;

llvm::Value *IdentifierNode::genCode(CodeGenerator & gen){
    cout << "IdentifierNode : " << name << endl;

    llvm::Value* variable = gen.findVariable(name);
    if(variable == nullptr){
        std::cerr << "undeclared variable " << name << endl;
        return nullptr;
    }
    llvm::Type* tp = variable->getType()->getPointerElementType();
    llvm::outs()<<"identifier type:"<<*tp;
    cout<<endl;

    llvm::Value* res = nullptr;
    if(tp->isArrayTy()) {
        vector<llvm::Value*> indexList;
        indexList.push_back(Builder.getInt32(0));
        indexList.push_back(Builder.getInt32(0));
        res = Builder.CreateInBoundsGEP(variable->getType(), variable, indexList, "tmpstring");
    }
    else {
        res = new llvm::LoadInst(tp, variable, "LoadInst", false, Builder.GetInsertBlock());
    }
    return res;
}

llvm::Value *IntNode::genCode(CodeGenerator & gen){
    cout << "IntNode : " << value <<endl;
    return llvm::ConstantInt::get(gen.context, llvm::APInt(32, intValue, true));
}

llvm::Value *CharNode::genCode(CodeGenerator & gen){
    cout << "CharNode : " << value <<endl;
    if (this->value.size() == 3)
        return Builder.getInt8(this->value.at(1));
    else {
        if (this->value.compare("'\\n'") == 0) {
            return Builder.getInt8('\n');
        } else if (this->value.compare("'\\\\'") == 0){
            return Builder.getInt8('\\');
        } else if (this->value.compare("'\\a'") == 0){
            return Builder.getInt8('\a');
        } else if (this->value.compare("'\\b'") == 0){
            return Builder.getInt8('\b');
        } else if (this->value.compare("'\\f'") == 0){
            return Builder.getInt8('\f');
        } else if (this->value.compare("'\\t'") == 0){
            return Builder.getInt8('\t');
        } else if (this->value.compare("'\\v'") == 0){
            return Builder.getInt8('\v');
        } else if (this->value.compare("'\\''") == 0){
            return Builder.getInt8('\'');
        } else if (this->value.compare("'\\\"'") == 0){
            return Builder.getInt8('\"');
        } else if (this->value.compare("'\\0'") == 0){
            return Builder.getInt8('\0');
        } else {
            throw logic_error("[ERROR] char not defined: " + this->value);
        }
    }
    return nullptr;
}

llvm::Value *DoubleNode::genCode(CodeGenerator & gen){
    cout << "DoubleNode : " << value <<endl;
    return llvm::ConstantFP::get(gen.context, llvm::APFloat(doubleValue));
}

llvm::Value *StringNode::genCode(CodeGenerator &gen) {
    string str = value.substr(1, value.length() - 2);
    string after = string(1, '\n');
    int pos = str.find("\\n");
    while(pos != string::npos) {
        str = str.replace(pos, 2, after);
        pos = str.find("\\n");
    }
    llvm::Constant *strConst = llvm::ConstantDataArray::getString(globalContext, str);
    llvm::Value *globalVar = new llvm::GlobalVariable(*gen.myModule, strConst->getType(), true, llvm::GlobalValue::PrivateLinkage, strConst, "_Const_String_");

    llvm::Value *zeroIndex = llvm::ConstantInt::get(llvm::Type::getInt32Ty(globalContext), 0);
    llvm::Value *indices[] = { zeroIndex, zeroIndex };

    llvm::Value *varPtr = Builder.CreateInBoundsGEP(globalVar->getType(), globalVar, indices, "tmpstring");
    return varPtr;
}

llvm::Value *ArrayEleNode::genCode(CodeGenerator & gen){
    cout << "ArrayElementNode : " << identifier.name << "[]" << endl;

    llvm::Value* arrayValue = gen.findVariable(identifier.name);
    if(arrayValue == nullptr){
        cerr << "undeclared array " << identifier.name << endl;
		return nullptr;
    }

    llvm::Value* indexValue = index.genCode(gen);
    vector<llvm::Value*> indexList;

    // 如果是一个指针
    if(arrayValue->getType()->getPointerElementType()->isPointerTy()) {
        arrayValue = Builder.CreateLoad(arrayValue->getType()->getPointerElementType(), arrayValue);
        indexList.push_back(indexValue);    
    }
    // 如果是一个数组 
    else {
        indexList.push_back(Builder.getInt32(0));
        indexList.push_back(indexValue);    
    }

    llvm::Value* elePtr =  Builder.CreateInBoundsGEP(arrayValue->getType(),arrayValue, llvm::ArrayRef<llvm::Value*>(indexList), "tmparray");
    return Builder.CreateLoad(elePtr->getType()->getPointerElementType(), elePtr, "tmpvar");
    
}

llvm::Value *ArrayAssNode::genCode(CodeGenerator & gen){
    cout<<"assign for arrayElementNode:"<<identifier.name<<"[]"<<endl;

    llvm::Value* arrayValue = gen.findVariable(identifier.name);
    if(arrayValue == nullptr){
        cerr << "undeclared array " << identifier.name << endl;
		return nullptr;
    }
    // llvm::Value* arrayValue = gen.getTop()[identifier.name];
    llvm::Value* indexValue = index.genCode(gen);
    vector<llvm::Value*> indexList;


    llvm::outs()<<"arrayIdentifier type:"<<*(arrayValue->getType());
    cout<<endl;

    // 如果是一个指针
    if(arrayValue->getType()->getPointerElementType()->isPointerTy()) {
        arrayValue = Builder.CreateLoad(arrayValue->getType()->getPointerElementType(), arrayValue);
        indexList.push_back(indexValue);    
    }
    // 如果是一个数组 
    else {
        indexList.push_back(Builder.getInt32(0));
        indexList.push_back(indexValue);    
    }
    llvm::Value* left =  Builder.CreateInBoundsGEP(arrayValue, llvm::ArrayRef<llvm::Value*>(indexList), "tmpvar");
    llvm::Value *right = rhs.genCode(gen);

    llvm::outs()<<*(left->getType()->getPointerElementType());

    if (right->getType() != left->getType()->getPointerElementType())
        right = typeCast(right, left->getType()->getPointerElementType());

    return Builder.CreateStore(right, left);
    //return nullptr;
}

llvm::Value *FunCallNode::genCode(CodeGenerator & gen){
    if(identifier->getname() == "printf"){ //若调用 printf 函数
        return gen.emitPrintf(gen, args);
    } else if(identifier->getname() == "scanf"){ //若调用 scanf 函数
        return gen.emitScanf(gen, args);
    } else if(identifier->getname() == "gets") { // 若调用 gets 函数
        return gen.emitGets(gen, args);
    }

    // 在module中查找以identifier命名的函数
    llvm::Function *func = gen.myModule->getFunction(identifier->name->c_str());
    if (func == NULL) {
        std::cerr << "no such function " << *(identifier->name) << endl;
    }

    vector<llvm::Value*> tmp;
    vector<ExpNode*>::iterator i;
    for(auto i : args){  //对每个ExpressionNode进行emit 并将结果存入tmp中
        tmp.push_back((*i).genCode(gen));
        if (tmp.back()->getType()->isPointerTy()) {
            tmp.back() = Builder.CreateLoad(tmp.back()->getType(), tmp.back());
        }
    }
    //调用
    llvm::CallInst *call = llvm::CallInst::Create(func, llvm::makeArrayRef(tmp), "", Builder.GetInsertBlock());
    return call;

}

llvm::Value *BinOpNode::genCode(CodeGenerator & gen){
    cout << "BinaryOpNode : " << op << endl;
    llvm::Value* left = lhs.genCode(gen);
    llvm::Value* right = rhs.genCode(gen);
    llvm::Instruction::BinaryOps bi_op;

    if(op == PLUS || op == MINUS || op == MUL || op == DIV){
        if(op == PLUS){bi_op = left->getType()->isFloatTy() ? llvm::Instruction::FAdd : llvm::Instruction::Add;}
        else if(op == MINUS){bi_op = left->getType()->isFloatTy() ? llvm::Instruction::FSub : llvm::Instruction::Sub;}
        else if(op == MUL){bi_op = left->getType()->isFloatTy() ? llvm::Instruction::FMul : llvm::Instruction::Mul;}
        else if(op == DIV){bi_op = left->getType()->isFloatTy() ? llvm::Instruction::FDiv : llvm::Instruction::SDiv;}
        return llvm::BinaryOperator::Create(bi_op,left,right,"", Builder.GetInsertBlock());
    }
    else if(op == AND){
        return Builder.CreateAnd(left, right, "tmpAnd");
    }
    else if (op == OR) {
        return Builder.CreateOr(left, right, "tmpOR");
    }
    else if (op == EQU) {
        return (left->getType() == llvm::Type::getFloatTy(myContext)) ? Builder.CreateFCmpOEQ(left, right, "fcmptmp") : Builder.CreateICmpEQ(left, right, "icmptmp");
    }
    else if (op == GEQ) {
        return (left->getType() == llvm::Type::getFloatTy(myContext)) ? Builder.CreateFCmpOGE(left, right, "fcmptmp") : Builder.CreateICmpSGE(left, right, "icmptmp");
    }
    else if (op == LEQ) {
        return (left->getType() == llvm::Type::getFloatTy(myContext)) ? Builder.CreateFCmpOLE(left, right, "fcmptmp") : Builder.CreateICmpSLE(left, right, "icmptmp");
    }
    else if (op == GREATERT) {
        return (left->getType() == llvm::Type::getFloatTy(myContext)) ? Builder.CreateFCmpOGT(left, right, "fcmptmp") : Builder.CreateICmpSGT(left, right, "icmptmp");
    }
    else if (op == LESST) {
        return (left->getType() == llvm::Type::getFloatTy(myContext)) ? Builder.CreateFCmpOLT(left, right, "fcmptmp") : Builder.CreateICmpSLT(left, right, "icmptmp");
    }
    else if (op == NEQ) {
        return (left->getType() == llvm::Type::getFloatTy(myContext)) ? Builder.CreateFCmpONE(left, right, "fcmptmp") : Builder.CreateICmpNE(left, right, "icmptmp");
    }
    return NULL;

}

llvm::Value *getAddrNode::genCode(CodeGenerator & gen){
    cout << "getAddrNode : " << rhs.name << endl;
    // 在符号表和全局变量中查找
    llvm::Value* result = gen.findVariable(rhs.name);
    if(result == nullptr){
        cerr << "undeclared variable " << rhs.name << endl;
		return nullptr;
    }
    return result;
}

llvm::Value *getArrayAddrNode::genCode(CodeGenerator & gen){

}

llvm::Value *AssignNode::genCode(CodeGenerator & gen){
    cout << "AssignmentNode,lhs: " << lhs.name << endl;
    
    // 在符号表和全局变量中查找
    llvm::Value* result = gen.findVariable(lhs.name);
    if(result == nullptr){
        cerr << "undeclared variable " << lhs.name << endl;
		return nullptr;
    }

    llvm::Value* right = rhs.genCode(gen);
    // 定位 block
    auto CurrentBlock = Builder.GetInsertBlock();
    
    if (right->getType() != result->getType()->getPointerElementType())
        right = typeCast(right, result->getType()->getPointerElementType());

    return new llvm::StoreInst(right, result, false, CurrentBlock);
}


llvm::Value *BlockNode::genCode(CodeGenerator & gen){
    llvm::Value* tmp = NULL;
    for(auto i : stmlist){
        cout << "Generating code for " << typeid(*i).name() << endl;
        tmp = (*i).genCode(gen);
        // 若当前语句为 reutrn , 则后面的语句需要截断
        if(gen.hasReturn == true)
            break;
    }
    cout << "" << endl;
	return tmp;
}

llvm::Value *ExpStmNode::genCode(CodeGenerator & gen){
    cout << "Generating code for " << typeid(expression).name() << endl;
	return expression.genCode(gen);
}

llvm::Value *BreakStmNode::genCode(CodeGenerator & gen){
    gen.hasReturn = true;
    return Builder.CreateBr(GlobalAfterBB.top());
}


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
    llvm::BasicBloack*  condition_block = llvm::BasicBlock::Create(globalContext, "C_block", func);
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

llvm::Value *WhileStmNode::genCode(CodeGenerator & gen){
    cout << "Generating code for while "<<endl;

    llvm::Function *TheFunction = gen.currentFunc;

    llvm::BasicBlock *condBB = llvm::BasicBlock::Create(myContext, "cond", TheFunction);
    llvm::BasicBlock *loopBB = llvm::BasicBlock::Create(myContext, "loop", TheFunction);
    llvm::BasicBlock *afterBB = llvm::BasicBlock::Create(myContext, "afterLoop", TheFunction);

    GlobalAfterBB.push(afterBB);

    Builder.CreateBr(condBB);
    Builder.SetInsertPoint(condBB);

    llvm::Value *condValue = expression.genCode(gen);
    condValue = Builder.CreateICmpNE(condValue, llvm::ConstantInt::get(llvm::Type::getInt1Ty(myContext), 0, true), "whileCond");
    auto branch = Builder.CreateCondBr(condValue, loopBB, afterBB);
    condBB = Builder.GetInsertBlock();

    Builder.SetInsertPoint(loopBB);

    // 将 while 的域放入栈顶
    gen.pushBlock();
    block.genCode(gen);
    if(gen.hasReturn)
        gen.hasReturn = false;
    else
        Builder.CreateBr(condBB);

    // while 结束, 将 while 的域弹出栈顶
    gen.popBlock();
    Builder.SetInsertPoint(afterBB);

    GlobalAfterBB.pop();
    return branch;
}

llvm::Value *ReturnNullStmNode::genCode(CodeGenerator & gen){
    
    cout << "Generating return code for void " << endl;
    gen.hasReturn = true;
    return Builder.CreateBr(gen.returnBB);
}

llvm::Value *ReturnStmNode::genCode(CodeGenerator & gen){
    cout << "Generating return code for " << typeid(expression).name() << endl;
	llvm::Value *rv = expression.genCode(gen);
    if (rv->getType() != gen.returnVal->getType()->getPointerElementType())
        rv = typeCast(rv, gen.returnVal->getType()->getPointerElementType());
    Builder.CreateStore(rv, gen.returnVal);

    gen.hasReturn = true;
    return Builder.CreateBr(gen.returnBB);
}

llvm::Value *VarDecNode::genCode(CodeGenerator & gen){
    if(size == 0){ //普通变量
        llvm::Type* llvmType = getLLvmType(type.name);
        
        // 若当前函数为空, 说明是全局变量
        if(gen.currentFunc == nullptr) {
            cout << "Creating global variable declaration " << type.name << " " << identifier.name<< endl;
            llvm::Value *tmp = gen.myModule->getGlobalVariable(identifier.name, true);
            if(tmp != nullptr){
                throw logic_error("Redefined Global Variable: " + identifier.name);
            }
            llvm::GlobalVariable* globalVar = new llvm::GlobalVariable(*(gen.myModule), llvmType, false, llvm::GlobalValue::PrivateLinkage, 0, identifier.name);
            globalVar->setInitializer(llvm::ConstantInt::get(llvmType, 0));
            return nullptr;
        } else {
            cout << "Creating local variable declaration " << type.name << " " << identifier.name<< endl;
            auto *block = Builder.GetInsertBlock();
            llvm::AllocaInst *alloc = new llvm::AllocaInst(llvmType,block->getParent()->getParent()->getDataLayout().getAllocaAddrSpace(),(identifier.name.c_str()), block);
            // 
            if(gen.getTop().count(identifier.name) != 0) {
                // 当前域中有该变量, 重复定义
                throw logic_error("Redefined Local Variable: " + identifier.name);
            }

            // 将新定义的变量类型和地址存入符号表中
            gen.getTopType()[identifier.name] = llvmType;
            gen.getTop()[identifier.name] = alloc;
            if (assignmentExpression != NULL) {
                AssignmentNode assn(identifier, *assignmentExpression,lineNo);
                assn.genCode(gen);
            }
            return alloc;
        }
    }
    else{ //数组
        llvm::Type* llvmType = getArrayLLvmType(type.name, size); 
        if(gen.currentFunc == nullptr) { //当前函数为空，为全局数组定义
            cout << "Creating global array declaration " << type.name << " " << identifier.name<< endl;
            llvm::Value *tmp = gen.myModule->getGlobalVariable(identifier.name, true);
            if(tmp != nullptr){
                throw logic_error("Redefined Global Array: " + identifier.name);
            }
            llvm::GlobalVariable* globalVar = new llvm::GlobalVariable(*(gen.myModule), llvmType, false, llvm::GlobalValue::PrivateLinkage, 0, identifier.name);
            
            std::vector<llvm::Constant*> constArrayElem;
            llvm::Constant* constElem = llvm::ConstantInt::get(llvmType->getArrayElementType(), 0);
            for (int i = 0; i < llvmType->getArrayNumElements(); i++) {
                constArrayElem.push_back(constElem);
            }
            llvm::Constant* constArray = llvm::ConstantArray::get(llvm::ArrayType::get(llvmType->getArrayElementType(), llvmType->getArrayNumElements()), constArrayElem);
            globalVar->setInitializer(constArray);
            return nullptr;
            
        }
        else {
            if(gen.getTop().count(identifier.name) != 0) {
                // 当前域中有该变量, 重复定义
                throw logic_error("Redefined Local Variable: " + identifier.name);
            }

            if(gen.isArgs) {
                // 如果是函数中定义的数组需要返回 指针类型
                cout << "Creating args array declaration " << type.name << " " << identifier.name<< endl;
                llvmType = getPtrLLvmType(type.name);
            } else {
                cout << "Creating local array declaration " << type.name << " " << identifier.name<< endl;
            }
            gen.getTopType()[identifier.name] = llvmType;
            auto *block = Builder.GetInsertBlock();
            llvm::AllocaInst *alloc = new llvm::AllocaInst(llvmType,block->getParent()->getParent()->getDataLayout().getAllocaAddrSpace(),(identifier.name.c_str()), block);
            gen.getTop()[identifier.name] = alloc;
            return alloc;
        }
    }

}

llvm::Value *FunDecNode::genCode(CodeGenerator & gen){
    vector<llvm::Type*> argTypes;
    for(auto it : args){
        if(it->size == 0)
            argTypes.push_back(getLLvmType(it->type.name));
        else {
            argTypes.push_back(getPtrLLvmType(it->type.name));
        }
    }
	llvm::FunctionType *ftype = llvm::FunctionType::get(getLLvmType(type.name), makeArrayRef(argTypes), false);
	llvm::Function *function = llvm::Function::Create(ftype, llvm::GlobalValue::ExternalLinkage, identifier.name.c_str(), gen.myModule);
	llvm::BasicBlock *bblock = llvm::BasicBlock::Create(myContext, "entry", function, 0);

    Builder.SetInsertPoint(bblock);
    gen.currentFunc = function;
    gen.returnBB = llvm::BasicBlock::Create(myContext, "return", function, 0);

    // 定义一个变量用来存储函数的返回值
    if(type.name.compare("void") != 0) {
        gen.returnVal = new llvm::AllocaInst(getLLvmType(type.name), bblock->getParent()->getParent()->getDataLayout().getAllocaAddrSpace(), "", bblock);
    }
 
	gen.pushBlock();

 
	llvm::Function::arg_iterator argsValues = function->arg_begin();
    llvm::Value* argumentValue;

    gen.isArgs = true;
    for(auto it : args){
        (*it).genCode(gen);
        argumentValue = &*argsValues++;
        argumentValue->setName((it)->identifier.name.c_str());
        llvm::StoreInst *inst = new llvm::StoreInst(argumentValue, gen.getTop()[(it)->identifier.name], false, bblock);
	}
    gen.isArgs = false;
	
	block.genCode(gen);
    gen.hasReturn = false;

    Builder.SetInsertPoint(gen.returnBB);
    if(type.name.compare("void") == 0) {
        Builder.CreateRetVoid();
    } else {
        llvm::Value* ret = Builder.CreateLoad(getLLvmType(type.name), gen.returnVal, "");
        Builder.CreateRet(ret);
    }

	gen.popBlock();
    gen.currentFunc = nullptr;
	std::cout << "Creating function: " << identifier.name << endl;
	return function;
}

llvm:: Value* emitPrintf(CodeGenerator & gen,vector<ExpNode*> args){
    vector<llvm::Value *> *printf_args = getPrintfArgs(gen, args);
    return Builder.CreateCall(gen.printf, *printf_args, "printf");
}

llvm:: Value* emitScanf(CodeGenerator & gen,vector<ExpNode*> args){
    vector<llvm::Value *> *scanf_args = getScanfArgs(gen, args);
    return Builder.CreateCall(gen.scanf, *scanf_args, "scanf");
}

llvm:: Value* emitGets(CodeGenerator & gen,vector<ExpNode*> args){
    vector<llvm::Value *> *gets_args = getGetsArgs(gen, args);
    return Builder.CreateCall(gen.gets, *gets_args, "gets");
}

