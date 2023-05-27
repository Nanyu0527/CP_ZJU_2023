#include "CodeGenerator.hpp"
llvm::Value* VarDecNode::genCode(CodeGenerator & gen) {  
    if(size == 0){ //非数组
        llvm::Type* llvmType = getLLvmType(type.name);
        // 全局变量
        if(globalContext.currentFunc == nullptr) {
            //cout << "Creating global variable declaration " << type.name << " " << identifier.name<< endl;
            //
            //查找变量防止重新定义
            llvm::GlobalVariable *tmp = globalContext.myModule->getNamedGlobal(identifier.name);
            if(tmp != nullptr){
                throw logic_error("Redefined Global Variable: " + identifier.name);
            }
            //新建全局变量
            llvm::GlobalVariable* New_globalVar = new llvm::GlobalVariable(*(globalContext.myModule), llvmType, false, llvm::GlobalValue::PrivateLinkage, 0, identifier.name);
            //类型 ， 非数组单个变量偏移为0
            New_globalVar->setInitializer(llvm::ConstantInt::get(llvmType, 0));
            return nullptr;
        } else {//函数内部变量
            //cout << "Creating local variable declaration " << type.name << " " << identifier.name<< endl;
            //指向当前函数块
            auto *block = Builder.GetInsertBlock();
            //
            // 当前域中已经有该变量, 重复定义        
            if(globalContext.getTop().count(identifier.name) != 0) {
                throw logic_error("Redefined Local Variable: " + identifier.name);
            }
            //
            //空间声明
            llvm::AllocaInst *alloc = new llvm::AllocaInst(llvmType,block->getParent()->getParent()->getDataLayout().getAllocaAddrSpace(),(identifier.name.c_str()), block);
            // 将新定义的变量类型和地址存入符号表中
            globalContext.getTopType()[identifier.name] = llvmType;
            globalContext.getTop()[identifier.name] = alloc;
            //是否赋值
            if (exp != NULL) {
                AssignNode assign(identifier, *exp);
                assign.genCode(globalContext);
            }
            return alloc;
        }
    }
    else{ //数组
        llvm::Type* llvmType = getArrayLLvmType(type.name, size); 
        if(globalContext.currentFunc == nullptr) { //当前函数为空，为全局数组定义
            //cout << "Creating global array declaration " << type.name << " " << identifier.name<< endl;
            //查找变量防止重新定义
            llvm::GlobalVariable *tmp = globalContext.myModule->getNamedGlobal(identifier.name);
            if(tmp != nullptr){
                throw logic_error("Redefined Global Variable(ARRAY): " + identifier.name);
            }
            llvm::GlobalVariable* New_globalVar = new llvm::GlobalVariable(*(globalContext.myModule), llvmType, false, llvm::GlobalValue::PrivateLinkage, 0, identifier.name);
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
            if(globalContext.getTop().count(identifier.name) != 0) {
                // 当前域中有该变量, 重复定义
                throw logic_error("Redefined Local Variable: " + identifier.name);
            }

            if(globalContext.isArgs) {
                // 如果是函数参数中定义的数组需要返回 指针类型
                //cout << "Creating args array declaration " << type.name << " " << identifier.name<< endl;
                llvmType = getPtrLLvmType(type.name);
            } else {
                //cout << "Creating local array declaration " << type.name << " " << identifier.name<< endl;
            }
            globalContext.getTopType()[identifier.name] = llvmType;
            auto *block = Builder.GetInsertBlock();
            llvm::AllocaInst *alloc = new llvm::AllocaInst(llvmType,block->getParent()->getParent()->getDataLayout().getAllocaAddrSpace(),(identifier.name.c_str()), block);
            globalContext.getTop()[identifier.name] = alloc;
            return alloc;
        }
    }

}
llvm::Value* FunDecNode::genCode(CodeGenerator & gen){
	vector<llvm::type> args_types;
    for(auto it : args){
        if(it->size == 0)//除数组外其它size赋值为0
            args_types.push_back(getLLvmType(it->type.name));
        else//array 
        {
            args_types.push_back(getPtrLLvmType(it->type.name));
        }
    }
    //FunctionType::get调用用于为给定的函数原型创建对应的FunctionType对象。
    //随后，FunctionType::get方法以args_types为参数类型、以单个type为返回值类型，
    //创建出一个参数个数不可变（最后一个参数false就是这个意思）的函数类型。
    llvm::FunctionType *Ftype = llvm::FunctionType::get(getLLvmType(type.name), makeArrayRef(args_types), false);
    //
    // “ExternalLinkage”表示该函数可能定义于当前模块之外，且/或可以被当前模块之外的函数调用;name函数名;符号表注册
    llvm::Function *F = Function::Create(Ftype, llvm::Function::ExternalLinkage, identifier->name.c_str(), gen.module);
    //
    //新建了一个名为“entry”的基本块对象，稍后该对象将被插入F
    llvm::BasicBlock *basicblock = llvm::BasicBlock::Create(globalContext, "entry", F);
    //告诉Builder，后续的新指令应该插至刚刚新建的基本块的末尾处
    Builder.SetInsertPoint(basicblock);

    gen.currentFunc = F;
    gen.returnBB = llvm::BasicBlock::Create(globalContext, "return", F);
    
    
    //函数有返回值s
    if(type.name.compare("void") != 0) {
        //返回值空间分配
        globalContext.returnVal = new llvm::AllocaInst(getLLvmType(type.name), baiscblock->getParent()->getParent()->getDataLayout().getAllocaAddrSpace(), "", basicblock);
    }
    //压入新符号表
	globalContext.pushBlock();
	llvm::Function::arg_iterator args_Values = F->arg_begin();
    llvm::Value* Tmp_Value;
    //遍历参数
    globalContext.isArgs = true;// (*it).genCode(globalContext);用
    for(auto it : args){
        (*it).genCode(globalContext);
        //??     Tmp_Value = &*args_Values++;
        Tmp_Value = args_Values;
        args_Values++;
        Tmp_Value->setName((it)->identifier.name.c_str());
        //StoreInst (Value *Val, Value *Ptr, bool isVolatile, BasicBlock *InsertAtEnd)
        //          要插的值    ，目标存储指针，是否易变    ，插在哪块后面。
        llvm::StoreInst *inst = new llvm::StoreInst(Tmp_Value, globalContext.getTop()[(it)->identifier.name], false, basicblock);
	}
    globalContext.isArgs = false;
	//函数后函数块处理
	block.genCode(globalContext);
    //重置hasreturn
    globalContext.hasReturn = false;
    //return后操作
    Builder.SetInsertPoint(globalContext.returnBB);
    if(type.name.compare("void") == 0) {
        Builder.CreateRetVoid();
    } else {
        llvm::Value* ret = Builder.CreateLoad(getLLvmType(type.name), globalContext.returnVal, "");
        Builder.CreateRet(ret);
    }

	globalContext.popBlock();
    globalContext.currentFunc = nullptr;
	//std::cout << "Creating function: " << identifier.name << endl;
	return F;
}