#ifndef AST_NODE
#define AST_NODE

#include <iostream>
#include <string>
#include <vector>
#include <llvm/IR/Value.h>
#include "llvm/ADT/STLExtras.h"

using namespace std;

enum C_TYPE
{
    C_INTEGER,
    C_FLOAT,
    C_DOUBLE,
    C_CHAR,
    C_BOOLEAN
};


class Node {
public:
    Node() {}
    virtual ~Node() {}
    virtual string genJson(){};
    virtual llvm::Value *genCode(CodeGenerator & gen);
};

class StmNode : public Node{
public:
    // void forward(CodeGenerator & gen);
    // void backward(CodeGenerator & gen);
    llvm::BasicBlock *block;
};
class ExpNode : public Node{
    
};
class Const : public ExpNode{
public:
    struct Value
    {
        int i;
        double d;
        float f;
        bool b;
        char c;
        // float f;
    };
};

class Identifier : public ExpNode{
public:
    Identifier(string *name) : name(name){}
    string getname(){return *name;}
    virtual string genJson();
    virtual llvm::Value *genCode(CodeGenerator & gen);
private:
    string *name;
};
class IntNode : public Const{
public:
    IntNode(int value) : value(value){}
    virtual C_TYPE getType(){ return C_INTEGER;}
    virtual Const::Value getValue(){
        Const::Value v;
        v.i = value;
        return v; 
    }
    virtual string genJson();
    virtual llvm::Value *genCode(CodeGenerator & gen);

private:
    int value;
};
class CharNode : public Const{
public:
    CharNode(char value) : value(value){}
    virtual C_TYPE getType(){ return C_CHAR;}
    virtual Const::Value getValue(){
        Const::Value v;
        v.c = value;
        return v; 
    }
    virtual string genJson();
    virtual llvm::Value *genCode(CodeGenerator & gen);

private:
    char value;
};
class BoolNode : public Const{
public:
    BoolNode(bool value) : value(value){}
    virtual C_TYPE getType(){ return C_BOOLEAN;}
    virtual Const::Value getValue(){
        Const::Value v;
        v.b = value;
        return v; 
    }
    virtual string genJson();
    virtual llvm::Value *genCode(CodeGenerator & gen);

private:
    bool value;
};
class FloatNode : public Const{
public:
    FloatNode(float value) : value(value){}
    virtual C_TYPE getType(){ return C_FLOAT;}
    virtual Const::Value getValue(){
        Const::Value v;
        v.f = value;
        return v; 
    }
    virtual string genJson();
    virtual llvm::Value *genCode(CodeGenerator & gen);

private:
    float value;
};

class DoubleNode : public Const{
public:
    DoubleNode(double value) : value(value){}
    virtual C_TYPE getType(){ return C_DOUBLE;}
    virtual Const::Value getValue(){
        Const::Value v;
        v.d = value;
        return v; 
    }
    virtual string genJson();
    virtual llvm::Value *genCode(CodeGenerator & gen);

private:
    double value;
};

class StringNode : public ExpNode{
public:
    StringNode(string &value):value(value){}
    virtual string genJson();
    virtual llvm::Value *genCode(CodeGenerator & gen);

private:
    string &value;
};
class ArrayEleNode : public ExpNode{
public:
    ArrayEleNode(){}
    virtual string genJson();
    virtual llvm::Value *genCode(CodeGenerator & gen);
};

class ArrayAssNode : public ExpNode{
public:
    ArrayAssNode(){}
    virtual string genJson();
    virtual llvm::Value *genCode(CodeGenerator & gen);
    
};
class FunCallNode : public ExpNode{
public:
    FunCallNode(){}
    virtual string genJson();
    virtual llvm::Value *genCode(CodeGenerator & gen);
};
class BinOpNode : public ExpNode{
public:
    BinOpNode(){}
    virtual string genJson();
    virtual llvm::Value *genCode(CodeGenerator & gen);
};
class getAddrNode : public ExpNode{
public:
    getAddrNode(){}
    virtual string genJson();
    virtual llvm::Value *genCode(CodeGenerator & gen);
};
class getArrayAddrNode : public ExpNode{
public:
    getArrayAddrNode(){}
    virtual string genJson();
    virtual llvm::Value *genCode(CodeGenerator & gen);
};
class AssignNode : public ExpNode{
public:
    AssignNode(){}
    virtual string genJson();
    virtual llvm::Value *genCode(CodeGenerator & gen);
};
class BlockNode : public ExpNode{
public:
    BlockNode(){}
    virtual string genJson();
    virtual llvm::Value *genCode(CodeGenerator & gen);
};

class ExpStmNode : public StmNode{
public:
    ExpStmNode(){}
    virtual string genJson();
    virtual llvm::Value *genCode(CodeGenerator & gen);
};
class BreakStmNode : public StmNode{
public:
    BreakStmNode(){}
    virtual string genJson();
    virtual llvm::Value *genCode(CodeGenerator & gen);
};
class IfStmNode : public StmNode{
public:
    IfStmNode(){}
    virtual string genJson();
    virtual llvm::Value *genCode(CodeGenerator & gen);
};
class IfElseStmNode : public StmNode{
public:
    IfElseStmNode(){}
    virtual string genJson();
    virtual llvm::Value *genCode(CodeGenerator & gen);
};
class WhileStmNode : public StmNode{
public:
    WhileStmNode(){}
    virtual string genJson();
    virtual llvm::Value *genCode(CodeGenerator & gen);
};
class ForStmNode : public StmNode{
public:
    ForStmNode(){}
    virtual string genJson();
    virtual llvm::Value *genCode(CodeGenerator & gen);
}
class ReturnNullStmNode : public StmNode{
public:
    ReturnNullStmNode(){}
    virtual string genJson();
    virtual llvm::Value *genCode(CodeGenerator & gen);
};
class ReturnStmNode : public StmNode{
public:
    ReturnStmNode(){}
    virtual string genJson();
    virtual llvm::Value *genCode(CodeGenerator & gen);
};
class VarDecNode : public StmNode{
public:
    VarDecNode(){}
    virtual string genJson();
    virtual llvm::Value *genCode(CodeGenerator & gen);
};
class FunDecNode : public StmNode{
public:
    FunDecNode(){}
    virtual string genJson();
    virtual llvm::Value *genCode(CodeGenerator & gen);
};
#endif