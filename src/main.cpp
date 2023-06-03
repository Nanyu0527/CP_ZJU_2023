#include "fstream"
#include "CodeGenerator.hpp"
#include "AST.h"
#include <stdio.h>
#include <llvm/Support/TargetSelect.h>

extern int yyparse(void);
extern BlockNode* root;

int main(){
    string inputfile_name = "./test/test.c";
    string outputfile_name = "./test/test.ll";
    freopen(inputfile_name.c_str(), "r", stdin);
    yyparse();
    CodeGenerator* generator = new CodeGenerator();
    
    llvm::InitializeNativeTarget();
    llvm::InitializeNativeTargetAsmParser();
    llvm::InitializeNativeTargetAsmPrinter();

    cout<<"program begin"<<endl;

    freopen(outputfile_name.c_str(), "w", stdout);

    generator->Run(root);
    generator->PrintIRCode(outputfile_name);

    return 0;

}