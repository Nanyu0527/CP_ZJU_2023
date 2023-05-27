#include"CodeGenerator.hpp"

CodeGenerator::CodeGenerator(){
    this->myModule = new llvm::Module("main",globalContext);
    this->printf = getPrintf();
    this->scanf = getScanf();
    this->hasReturn = false;
    this->isArgs = false;
}

map<string , llvm::Value*> &CodeGenerator::getTop(){
    return symbolTable_stack.back()->local_Var;
}
map<string , llvm::Type*> &CodeGenerator::getTopType(){
    return symbolTable_stack.back()->local_Var_Type;
}

void CodeGenerator::pushBlock(){
    symbolTable_stack.push_back(new symbolTable());
}

void CodeGenerator::popBlock(){
    symbolTable *tmp = symbolTable_stack.back();
    symbolTable_stack.pop_back();
    delete tmp;
}

llvm::Value* CodeGenerator::findVariable(string var){
    for(auto iter = symbolTable_stack.rbegin();iter != symbolTable_stack.rend();iter++){
        symbolTable* table = *iter;
        if(table->local_Var.find(var)!=table->local_Var.end()){
            return table->local_Var[var];
        }
    }
    return myModule->getGlobalVariable(var,true);
}
llvm::Function* CodeGenerator::getScanf(){
    llvm::FunctionType* scanf_type = 
    llvm::FunctionType::get(Builder.getInt32Ty(),true);
    llvm::Function* scanf_func = 
    llvm::Function::Create(scanf_type,llvm::Function::ExternalLinkage,llvm::Twine("scanf"),myModule);

    scanf_func->setCallingConv(llvm::CallingConv::C);
    return scanf_func;
}
llvm::Function* CodeGenerator::getPrintf(){
    vector<llvm::Type*> printf_arg_types; //printf内参数的类型
    printf_arg_types.push_back(Builder.getInt8PtrTy()); //8位代表void*
    llvm::FunctionType* printf_type = 
    llvm::FunctionType::get(Builder.getInt32Ty(),printf_arg_types,true);
    llvm::Function* printf_func = 
    llvm::Function::Create(printf_type,llvm::Function::ExternalLinkage,llvm::Twine("printf"),myModule);
    printf_func->setCallingConv(llvm::CallingConv::C);
    return printf_func;
}
llvm::Function* CodeGenerator::getGets(){
    llvm::FunctionType* gets_type = 
    llvm::FunctionType::get(Builder.getInt32Ty(),true);
    llvm::Function* gets_func = 
    llvm::Function::Create(gets_type,llvm::Function::ExternalLinkage,llvm::Twine("gets"),this->myModule);
    gets_func->setCallingConv(llvm::CallingConv::C);
    return gets_func;
}
vector<llvm::Value *> *getPrintfArgs(CodeGenerator &Context,vector<ExpNode*>args){
    vector<llvm::Value *> *printf_args = new vector<llvm::Value *>;
    for(auto it: args){
        llvm::Value* tmp = it->genCode(Context);
        if (tmp->getType() == llvm::Type::getFloatTy(globalContext))
            tmp = Builder.CreateFPExt(tmp, llvm::Type::getDoubleTy(globalContext), "tmpdouble");
        printf_args->push_back(tmp);
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
llvm:: Value* CodeGenerator::emitPrintf(CodeGenerator &Context,vector<ExpNode*> args){
    vector<llvm::Value *> *printf_args = getPrintfArgs(Context, args);    
    return Builder.CreateCall(Context.printf, *printf_args, "printf");
}

llvm:: Value* CodeGenerator::emitScanf(CodeGenerator &emitContext,vector<ExpNode*> args){
    vector<llvm::Value *> *scanf_args = getScanfArgs(emitContext, args);    
    return Builder.CreateCall(emitContext.scanf, *scanf_args, "scanf");
}

void CodeGenerator::Run(BlockNode* Root){
    Root->genCode(*this);
    llvm::verifyModule(*this->myModule, &llvm::outs());
    this->myModule->print(llvm::outs(), nullptr);
}
