#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Value.h>
#include <map>
#include <stack>
#include <string>
#include <vector>
#include <typeinfo>
#include <llvm/IR/Verifier.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/IR/GlobalVariable.h>
#include <llvm/IR/IRPrintingPasses.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/Bitcode/BitcodeReader.h>
#include <llvm/Bitcode/BitcodeWriter.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/ADT/Twine.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Support/raw_ostream.h>


#include "AST.h"
using namespace std;

llvm::LLVMContext globalContext;
llvm::IRBuilder<> Builder(globalContext);

class symbolTable {
    public:
        map<string, llvm::Value*> local_Var; //局部变量map
        map<string, llvm::Type*> local_Var_Type;//局部变量string-llvm::type的map
};

class CodeGenerator{
    

public:
    vector<symbolTable *> symbolTable_stack; 
    llvm::Module *myModule; 
    llvm::Function *printf,*scanf, *gets;
    llvm::Function* currentFunc;
    llvm::BasicBlock* returnBB;
    llvm::Value* returnVal;
    bool isArgs;
    bool hasReturn;

    CodeGenerator();
    ~CodeGenerator();
    map<string, llvm::Value*>& getTop();
    map<string, llvm::Type*>& getTopType();

    void pushBlock();
    void popBlock();

    llvm::Value* findVariable(string variableName);
    llvm::Type* findVariableType(string variableName);

    llvm::Function* getCurFunction();
    void pushFunction(llvm::Function* func);
    void popFunction();

    llvm::Function* getPrintf(); 
    llvm::Function* getScanf(); 
    llvm:: Value* emitScanf(CodeGenerator &emitContext,vector<ExpNode*> args);
    llvm:: Value* emitPrintf(CodeGenerator &emitContext,vector<ExpNode*> args);
    vector<llvm::Value *> *getPrintfArgs(CodeGenerator &emitContext,vector<ExpNode*>args);
    vector<llvm::Value *> *getScanfArgs(CodeGenerator &emitContext,vector<ExpNode*>args);
    void Run(BlockNode* Root); 
};