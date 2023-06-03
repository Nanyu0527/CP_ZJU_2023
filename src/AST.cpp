#include "AST.h"
#include "lab_yacc.hpp"
#include "CodeGenerator.hpp"

stack<llvm::BasicBlock *> GlobalAfterBB;
llvm::LLVMContext globalContext;
llvm::IRBuilder<> Builder(globalContext);

vector<llvm::Value *> *getPrintfArgs(CodeGenerator &Context,vector<ExpNode*>args){
    vector<llvm::Value *> *printf_args = new vector<llvm::Value *>;
    int flag=0;
    for(auto it: args) {
        llvm::Value* tmp = it->genCode(Context);
        if (flag)
            if (tmp->getType()->isPointerTy())   
                tmp = Builder.CreateLoad( tmp->getType()->getPointerElementType() ,tmp, "tmp_load");
        printf_args->push_back(tmp);
        flag++;
    }
    return printf_args;
}

vector<llvm::Value *> *getScanfArgs(CodeGenerator &Context,vector<ExpNode*>args){
    vector<llvm::Value *> *scanf_args = new vector<llvm::Value *>;
    for(auto it: args){
        llvm::Value* tmp = it->genCode(Context);
        scanf_args->push_back(tmp);
    }
    return scanf_args;
}
vector<llvm::Value *> *getGetsArgs(CodeGenerator &emitContext,vector<ExpNode*>args){
    vector<llvm::Value *> *gets_args = new vector<llvm::Value *>;
    for(auto it: args){
        llvm::Value* tmp = it->genCode(emitContext);
        gets_args->push_back(tmp);
    }
    return gets_args;
}
llvm:: Value* emitPrintf(CodeGenerator &Context,vector<ExpNode*> args){
    vector<llvm::Value *> *printf_args = getPrintfArgs(Context, args);    
    return Builder.CreateCall(Context.printf, *printf_args, "printf");
}

llvm:: Value* emitScanf(CodeGenerator &emitContext,vector<ExpNode*> args){
    vector<llvm::Value *> *scanf_args = getScanfArgs(emitContext, args);    
    return Builder.CreateCall(emitContext.scanf, *scanf_args, "scanf");
}
llvm:: Value* emitGets(CodeGenerator &emitContext,vector<ExpNode*> args){   
    vector<llvm::Value *> *gets_args = getGetsArgs(emitContext, args);    
    return Builder.CreateCall(emitContext.gets, *gets_args, "gets");
}

llvm::Type* getLLvmType(string type){ //通过type，返回对应的LLVM的Type
    if(type == "int"){return llvm::Type::getInt32Ty(globalContext);}
    else if(type == "float"){return llvm::Type::getFloatTy(globalContext);}
    else if(type == "char"){return llvm::Type::getInt8Ty(globalContext);}
    return llvm::Type::getVoidTy(globalContext);
}

llvm::Type* getPtrLLvmType(string type){ //对于指针形式，返回对应的LLVM的Type
    if(type == "int"){return llvm::Type::getInt32PtrTy(globalContext);}
    else if(type == "float"){return llvm::Type::getFloatPtrTy(globalContext);}
    else if(type == "char"){return llvm::Type::getInt8PtrTy(globalContext);}
    return llvm::Type::getVoidTy(globalContext);
}

llvm::Type* getArrayLLvmType(string type,int size){ //对于数组形式，返回对应的LLVM的Type
    if(type == "int"){ //int数组
        return llvm::ArrayType::get(llvm::Type::getInt32Ty(globalContext), size);
    }
    else if(type == "float"){
        return llvm::ArrayType::get(llvm::Type::getFloatTy(globalContext), size);
    }
    else if(type == "char"){
        return llvm::ArrayType::get(llvm::Type::getInt8Ty(globalContext), size);
    }
    else{return nullptr;}
}
llvm::Instruction::CastOps getCastInst(llvm::Type* src, llvm::Type* dst) {
    if (src == llvm::Type::getFloatTy(globalContext) && dst == llvm::Type::getInt32Ty(globalContext)) { //llvm下float到int
        return llvm::Instruction::FPToSI;  
    }
    else if (src == llvm::Type::getInt32Ty(globalContext) && dst == llvm::Type::getFloatTy(globalContext)) { //llvm下int到float
        return llvm::Instruction::SIToFP;
    }
    else if (src == llvm::Type::getInt8Ty(globalContext) && dst == llvm::Type::getFloatTy(globalContext)) {
        return llvm::Instruction::UIToFP;
    }
    else if (src == llvm::Type::getInt8Ty(globalContext) && dst == llvm::Type::getInt32Ty(globalContext)) {
        return llvm::Instruction::ZExt;
    }
    else if (src == llvm::Type::getInt32Ty(globalContext) && dst == llvm::Type::getInt8Ty(globalContext)) {
        return llvm::Instruction::Trunc;
    }
    else {
        throw logic_error("[ERROR] Wrong typecast");
    }
}
llvm::Value* typeCast(llvm::Value* src, llvm::Type* dst) {
    llvm::Instruction::CastOps op = getCastInst(src->getType(), dst);
    return Builder.CreateCast(op, src, dst, "tmptypecast");
}

llvm::Value *IdentifierNode::genCode(CodeGenerator & gen){
    cout << "IdentifierNode : " << *name << endl;

    llvm::Value* variable = gen.findVariable(*name);
    if(variable == nullptr){
        std::cerr << "undeclared variable " << *name << endl;
        return nullptr;
    }
    llvm::Type* tp = variable->getType()->getPointerElementType();
    llvm::outs()<<"identifier type:"<<*tp;
    cout<<endl;

    llvm::Value* res = nullptr;
    // 如果传入的是一个数组的 ID
    if(tp->isArrayTy()) {
        vector<llvm::Value*> indexList;
        indexList.push_back(Builder.getInt32(0));
        indexList.push_back(Builder.getInt32(0));
        //Builder.CreateInBoundsGEP(tp,variable,indexList,"arrayPtr");
        res = Builder.CreateInBoundsGEP(tp,variable, indexList, "arrayPtr");
        // llvm::ArrayRef<llvm::Value *> indexRef(indexList.data(), indexList.size());
        // llvm::Value *varPtr = Builder.CreateInBoundsGEP(variable, indexRef, "tmpstring");
    }
    else {
        res = new llvm::LoadInst(tp, variable, "LoadInst", false, Builder.GetInsertBlock());
    }
    return res;
}

llvm::Value *IntNode::genCode(CodeGenerator & gen){
    cout << "IntNode : " << value <<endl;
    //return llvm::ConstantInt::get(globalContext, llvm::APInt(32, value, true));
    return llvm::ConstantInt::get(llvm::Type::getInt32Ty(globalContext), value);
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

llvm::Value* DoubleNode::genCode(CodeGenerator &CodeGenContext) {
    return llvm::ConstantFP::get(globalContext, llvm::APFloat(value));
}


llvm::Value *ArrayEleNode::genCode(CodeGenerator & gen){
    cout << "ArrayElementNode : " << identifier->name << "[]" << endl;

    llvm::Value* arrayValue = gen.findVariable(*(identifier->name));
    if(arrayValue == nullptr){
        cerr << "undeclared array " << identifier->name << endl;
		return nullptr;
    }

    llvm::Value* indexValue = index->genCode(gen);
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
    cout<<"assign for arrayElementNode:"<<identifier->getname()<<"[]"<<endl;

    llvm::Value* arrayValue = gen.findVariable(identifier->getname());
    if(arrayValue == nullptr){
        cerr << "undeclared array " << identifier->getname() << endl;
		return nullptr;
    }

    llvm::Value* indexValue = index->genCode(gen);
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
    llvm::Value* left =  Builder.CreateInBoundsGEP(arrayValue->getType(),arrayValue, llvm::ArrayRef<llvm::Value*>(indexList), "tmpvar");
    llvm::Value *right = rhs->genCode(gen);

    llvm::outs()<<*(left->getType()->getPointerElementType());

    if (right->getType() != left->getType()->getPointerElementType())
        right = typeCast(right, left->getType()->getPointerElementType());

    return Builder.CreateStore(right, left);
}

llvm::Value *FunCallNode::genCode(CodeGenerator & gen){
    if(identifier->getname() == "printf"){ //若调用 printf 函数
        return emitPrintf(gen, args);
    } else if(identifier->getname() == "scanf"){ //若调用 scanf 函数
        return emitScanf(gen, args);
    } else if(identifier->getname() == "gets") { // 若调用 gets 函数
        return emitGets(gen, args);
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
    llvm::Value* left = l->genCode(gen);
    llvm::Value* right = r->genCode(gen);
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
    else if (op == EQ) {
        return (left->getType() == llvm::Type::getFloatTy(globalContext)) ? Builder.CreateFCmpOEQ(left, right, "fcmptmp") : Builder.CreateICmpEQ(left, right, "icmptmp");
    }
    else if (op == GE) {
        return (left->getType() == llvm::Type::getFloatTy(globalContext)) ? Builder.CreateFCmpOGE(left, right, "fcmptmp") : Builder.CreateICmpSGE(left, right, "icmptmp");
    }
    else if (op == LE) {
        return (left->getType() == llvm::Type::getFloatTy(globalContext)) ? Builder.CreateFCmpOLE(left, right, "fcmptmp") : Builder.CreateICmpSLE(left, right, "icmptmp");
    }
    else if (op == GT) {
        return (left->getType() == llvm::Type::getFloatTy(globalContext)) ? Builder.CreateFCmpOGT(left, right, "fcmptmp") : Builder.CreateICmpSGT(left, right, "icmptmp");
    }
    else if (op == LT) {
        return (left->getType() == llvm::Type::getFloatTy(globalContext)) ? Builder.CreateFCmpOLT(left, right, "fcmptmp") : Builder.CreateICmpSLT(left, right, "icmptmp");
    }
    else if (op == NE) {
        return (left->getType() == llvm::Type::getFloatTy(globalContext)) ? Builder.CreateFCmpONE(left, right, "fcmptmp") : Builder.CreateICmpNE(left, right, "icmptmp");
    }
    return NULL;

}

llvm::Value *getAddrNode::genCode(CodeGenerator & gen){
    cout << "getAddrNode : " << identifier->name << endl;
    // 在符号表和全局变量中查找
    llvm::Value* result = gen.findVariable(identifier->getname());
    if(result == nullptr){
        cerr << "undeclared variable " << identifier->name << endl;
		return nullptr;
    }
    return result;
}

llvm::Value *getArrayAddrNode::genCode(CodeGenerator & gen){
    cout<<"get arrayElement Addr:"<<identifier->name<<"[]"<<endl;

    llvm::Value* arrayValue = gen.findVariable(identifier->getname());
    if(arrayValue == nullptr){
        cerr << "undeclared array " << identifier->getname() << endl;
        return nullptr;
    }
    // llvm::Value* arrayValue = emitContext.getTop()[identifier.name];
    llvm::Value* indexValue = index->genCode(gen);
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

    //llvm::Value* elePtr =  Builder.CreateInBoundsGEP(arrayValue, llvm::ArrayRef<llvm::Value*>(indexList), "elePtr");
    llvm::Value* elePtr = Builder.CreateInBoundsGEP(arrayValue->getType(), arrayValue,llvm::ArrayRef<llvm::Value*>(indexList),"elePtr");

    return elePtr;
    //return nullptr;
}

llvm::Value *AssignNode::genCode(CodeGenerator & gen){
    cout << "AssignmentNode,lhs: " << lhs->getname() << endl;
    
    // 在符号表和全局变量中查找
    llvm::Value* result = gen.findVariable(lhs->getname());
    if(result == nullptr){
        cerr << "undeclared variable " << lhs->name << endl;
		return nullptr;
    }

    llvm::Value* right = rhs->genCode(gen);
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
    cout << "Generating code for " << typeid(exp).name() << endl;
	return exp->genCode(gen);
}

llvm::Value *BreakStmNode::genCode(CodeGenerator & gen){
    gen.hasReturn = true;
    return Builder.CreateBr(GlobalAfterBB.top());
}
llvm::Value *WhileStmNode::genCode(CodeGenerator & gen){
    cout << "Generating code for while "<<endl;

    llvm::Function *TheFunction = gen.currentFunc;

    llvm::BasicBlock *condBB = llvm::BasicBlock::Create(globalContext, "cond", TheFunction);
    llvm::BasicBlock *loopBB = llvm::BasicBlock::Create(globalContext, "loop", TheFunction);
    llvm::BasicBlock *afterBB = llvm::BasicBlock::Create(globalContext, "afterLoop", TheFunction);

    GlobalAfterBB.push(afterBB);

    Builder.CreateBr(condBB);
    Builder.SetInsertPoint(condBB);

    llvm::Value *condValue = exp->genCode(gen);
    condValue = Builder.CreateICmpNE(condValue, llvm::ConstantInt::get(llvm::Type::getInt1Ty(globalContext), 0, true), "whileCond");
    auto branch = Builder.CreateCondBr(condValue, loopBB, afterBB);
    condBB = Builder.GetInsertBlock();

    Builder.SetInsertPoint(loopBB);

    // 将 while 的域放入栈顶
    gen.pushBlock();
    block->genCode(gen);
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
    cout << "Generating return code for " << typeid(exp).name() << endl;
	llvm::Value *rv = exp->genCode(gen);
    if (rv->getType() != gen.returnVal->getType()->getPointerElementType())
        rv = typeCast(rv, gen.returnVal->getType()->getPointerElementType());
    Builder.CreateStore(rv, gen.returnVal);

    gen.hasReturn = true;
    return Builder.CreateBr(gen.returnBB);
}

llvm::Value* VarDecNode::genCode(CodeGenerator & gen) {  
    if(size == 0){ //非数组
        llvm::Type* llvmType = getLLvmType(*(type->name));
        // 全局变量
        if(gen.currentFunc == nullptr) {
            //cout << "Creating global variable declaration " << type.name << " " << identifier.name<< endl;
            //
            //查找变量防止重新定义
            llvm::StringRef Idfname(*(identifier->name));
            llvm::GlobalVariable *tmp = gen.myModule->getNamedGlobal(Idfname);
            if(tmp != nullptr){
                throw logic_error("Redefined Global Variable: " + *(identifier->name));
            }
            //新建全局变量
            llvm::GlobalVariable* New_globalVar = new llvm::GlobalVariable(*(gen.myModule), llvmType, false, llvm::GlobalValue::PrivateLinkage, 0, *(identifier->name));
            //类型 ， 非数组单个变量偏移为0
            New_globalVar->setInitializer(llvm::ConstantInt::get(llvmType, 0));
            return nullptr;
        } else {//函数内部变量
            //cout << "Creating local variable declaration " << type.name << " " << identifier.name<< endl;
            //指向当前函数块
            auto *block = Builder.GetInsertBlock();
            //
            // 当前域中已经有该变量, 重复定义        
            if(gen.getTop().count(*(identifier->name)) != 0) {
                throw logic_error("Redefined Local Variable: " + *(identifier->name));
            }
            //
            //空间声明
            llvm::AllocaInst *alloc = new llvm::AllocaInst(llvmType,block->getParent()->getParent()->getDataLayout().getAllocaAddrSpace(),(identifier->name->c_str()), block);
            // 将新定义的变量类型和地址存入符号表中
            gen.getTopType()[*(identifier->name)] = llvmType;
            gen.getTop()[*(identifier->name)] = alloc;
            //是否赋值
            if (exp != NULL) {
                AssignNode assign(identifier, exp);
                assign.genCode(gen);
            }
            return alloc;
        }
    }
    else{ //数组
        llvm::Type* llvmType = getArrayLLvmType(*(type->name), size); 
        if(gen.currentFunc == nullptr) { //当前函数为空，为全局数组定义
            //cout << "Creating global array declaration " << type.name << " " << identifier.name<< endl;
            //查找变量防止重新定义
            llvm::StringRef Idfname(*(identifier->name));
            llvm::GlobalVariable *tmp = gen.myModule->getNamedGlobal(Idfname);
            if(tmp != nullptr){
                throw logic_error("Redefined Global Variable(ARRAY): " + *(identifier->name));
            }
            llvm::GlobalVariable* New_globalVar = new llvm::GlobalVariable(*(gen.myModule), llvmType, false, llvm::GlobalValue::PrivateLinkage, 0, *(identifier->name));
            //???????
            std::vector<llvm::Constant*> constArrayElem;
            llvm::Constant* constElem = llvm::ConstantInt::get(llvmType->getArrayElementType(), 0);
            for (int i = 0; i < llvmType->getArrayNumElements(); i++) {
                constArrayElem.push_back(constElem);
            }
            llvm::Constant* constArray = llvm::ConstantArray::get(llvm::ArrayType::get(llvmType->getArrayElementType(), llvmType->getArrayNumElements()), constArrayElem);
            New_globalVar->setInitializer(constArray);
            return nullptr;
            
        }
        else {//非空 为内部变量
            if(gen.getTop().count(*(identifier->name)) != 0) {
                // 当前域中有该变量, 重复定义
                throw logic_error("Redefined Local Variable: " + *(identifier->name));
            }

            if(gen.isArgs) {
                // 如果是函数参数中定义的数组需要返回 指针类型
                //cout << "Creating args array declaration " << type.name << " " << identifier.name<< endl;
                llvmType = getPtrLLvmType(*(type->name));
            } else {
                //cout << "Creating local array declaration " << type.name << " " << identifier.name<< endl;
            }
            gen.getTopType()[*(identifier->name)] = llvmType;
            auto *block = Builder.GetInsertBlock();
            llvm::AllocaInst *alloc = new llvm::AllocaInst(llvmType,block->getParent()->getParent()->getDataLayout().getAllocaAddrSpace(),(identifier->name->c_str()), block);
            gen.getTop()[*(identifier->name)] = alloc;
            return alloc;
        }
    }

}
llvm::Value* FunDecNode::genCode(CodeGenerator & gen){
	vector<llvm::Type*> args_types;
    for(auto it : args){
        if(it->size == 0)//除数组外其它size赋值为0
            args_types.push_back(getLLvmType(*(it->type->name)));
        else//array 
        {
            args_types.push_back(getPtrLLvmType(*(it->type->name)));
        }
    }
    //FunctionType::get调用用于为给定的函数原型创建对应的FunctionType对象。
    //随后，FunctionType::get方法以args_types为参数类型、以单个type为返回值类型，
    //创建出一个参数个数不可变（最后一个参数false就是这个意思）的函数类型。
    llvm::FunctionType *Ftype = llvm::FunctionType::get(getLLvmType(*(type->name)), makeArrayRef(args_types), false);
    //
    // “ExternalLinkage”表示该函数可能定义于当前模块之外，且/或可以被当前模块之外的函数调用;name函数名;符号表注册
    llvm::Function *F = llvm::Function::Create(Ftype, llvm::Function::ExternalLinkage, identifier->name->c_str(), gen.myModule);
    //
    //新建了一个名为“entry”的基本块对象，稍后该对象将被插入F
    llvm::BasicBlock *basicblock = llvm::BasicBlock::Create(globalContext, "entry", F);
    //告诉Builder，后续的新指令应该插至刚刚新建的基本块的末尾处
    Builder.SetInsertPoint(basicblock);

    gen.currentFunc = F;
    gen.returnBB = llvm::BasicBlock::Create(globalContext, "return", F);
    
    
    //函数有返回值s
    if(type->name->compare("void") != 0) {
        //返回值空间分配
        gen.returnVal = new llvm::AllocaInst(getLLvmType(*(type->name)), basicblock->getParent()->getParent()->getDataLayout().getAllocaAddrSpace(), "", basicblock);
    }
    //压入新符号表
	gen.pushBlock();
	llvm::Function::arg_iterator args_Values = F->arg_begin();
    llvm::Value* Tmp_Value;
    //遍历参数
    gen.isArgs = true;// (*it).genCode(globalContext);用
    for(auto it : args){
        (*it).genCode(gen);
        //??     Tmp_Value = &*args_Values++;
        Tmp_Value = args_Values;
        args_Values++;
        Tmp_Value->setName((*it).identifier->name->c_str());
        //StoreInst (Value *Val, Value *Ptr, bool isVolatile, BasicBlock *InsertAtEnd)
        //          要插的值    ，目标存储指针，是否易变    ，插在哪块后面。
        llvm::StoreInst *inst = new llvm::StoreInst(Tmp_Value, gen.getTop()[*((*it).identifier->name)], false, basicblock);
	}
    gen.isArgs = false;
	//函数后函数块处理
	block->genCode(gen);
    //重置hasreturn
    gen.hasReturn = false;
    //return后操作
    Builder.SetInsertPoint(gen.returnBB);
    if((type->name)->compare("void") == 0) {
        Builder.CreateRetVoid();
    } else {
        llvm::Value* ret = Builder.CreateLoad(getLLvmType(*(type->name)), gen.returnVal, "");
        Builder.CreateRet(ret);
    }

	gen.popBlock();
    gen.currentFunc = nullptr;
	//std::cout << "Creating function: " << identifier.name << endl;
	return F;
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