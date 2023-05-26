#ifndef AST_NODE
#define AST_NODE

#include <iostream>
#include <string>
#include <vector>
#include <llvm/IR/Value.h>
#include "llvm/ADT/STLExtras.h"

extern llvm::LLVMContext globalContext;
extern llvm::IRBuilder<> Builder;

using namespace std;

enum C_TYPE
{
    C_INTEGER,
    // C_FLOAT,
    C_DOUBLE,
    C_CHAR
    // C_BOOLEAN
};
class CodeGenerator{};

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
// using StmList =  std::vector <StmNode>;
// std::vector<ExpNode> ExpList;
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

class IdentifierNode : public ExpNode{
public:
    IdentifierNode (string *name) : name(name){}
    string getname(){return *name;}
    virtual string genJson();
    virtual llvm::Value *genCode(CodeGenerator & gen);

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

    char value;
};
// class BoolNode : public Const{
// public:
//     BoolNode(bool value) : value(value){}
//     virtual C_TYPE getType(){ return C_BOOLEAN;}
//     virtual Const::Value getValue(){
//         Const::Value v;
//         v.b = value;
//         return v; 
//     }
//     virtual string genJson();
//     virtual llvm::Value *genCode(CodeGenerator & gen);

//     bool value;
// };
// class FloatNode : public Const{
// public:
//     FloatNode(float value) : value(value){}
//     virtual C_TYPE getType(){ return C_FLOAT;}
//     virtual Const::Value getValue(){
//         Const::Value v;
//         v.f = value;
//         return v; 
//     }
//     virtual string genJson();
//     virtual llvm::Value *genCode(CodeGenerator & gen);

// private:
//     float value;
// };

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

    double value;
};

class StringNode : public ExpNode{
public:
    StringNode(string *value):value(value){}
    virtual string genJson();
    virtual llvm::Value *genCode(CodeGenerator & gen);

    string *value;
};
class ArrayEleNode : public ExpNode{
public:
    ArrayEleNode(IdentifierNode* _identifier,ExpNode* _index):identifier(_identifier),index(_index){}
    virtual string genJson();
    virtual llvm::Value *genCode(CodeGenerator & gen);
    
    IdentifierNode * identifier;
    ExpNode* index;
};

class ArrayAssNode : public ExpNode{
public:
    ArrayAssNode(IdentifierNode* _identifier,ExpNode* _index,ExpNode* _rhs):identifier(_identifier),index(_index),rhs(_rhs){}
    virtual string genJson();
    virtual llvm::Value *genCode(CodeGenerator & gen);

    IdentifierNode * identifier;
    ExpNode* index;
    ExpNode* rhs; 
    
};
class FunCallNode : public ExpNode{
public:
    FunCallNode(IdentifierNode *_identifier, vector<ExpNode*> _args) : identifier(_identifier), args(_args) {}
    FunCallNode(IdentifierNode *_identifier) :  identifier(identifier) {}
    virtual string genJson();
    virtual llvm::Value *genCode(CodeGenerator & gen);

    IdentifierNode * identifier;
    vector<ExpNode*> args;

};
class BinOpNode : public ExpNode{
public:
    BinOpNode(int _op,ExpNode* _l,ExpNode* _r):op(_op),l(_l),r(_r){}
    virtual string genJson();
    virtual llvm::Value *genCode(CodeGenerator & gen);
    int op;
    ExpNode* l;
    ExpNode* r;
};
class getAddrNode : public ExpNode{
public:
    getAddrNode(IdentifierNode *_identifier):identifier(_identifier){}
    virtual string genJson();
    virtual llvm::Value *genCode(CodeGenerator & gen);

    IdentifierNode *identifier;
};
class getArrayAddrNode : public ExpNode{
public:
    getArrayAddrNode(IdentifierNode *_identifier, ExpNode *_index) :index(_index), identifier(_identifier) {}
    virtual string genJson();
    virtual llvm::Value *genCode(CodeGenerator & gen);

    ExpNode* index;
    IdentifierNode *identifier;
};
class AssignNode : public ExpNode{
public:
    AssignNode(IdentifierNode *_identifier, ExpNode *_index) :lhs(_index), identifier(_identifier) {}
    virtual string genJson();
    virtual llvm::Value *genCode(CodeGenerator & gen);

    IdentifierNode *identifier;
    ExpNode *lhs;
};
class BlockNode : public ExpNode{
public:
    BlockNode(){}
    BlockNode(vector<StmNode*> _stmlist):stmlist(_stmlist){}
    virtual string genJson();
    virtual llvm::Value *genCode(CodeGenerator & gen);

    vector<StmNode*> stmlist;
};

class ExpStmNode : public StmNode{
public:
    ExpStmNode(ExpNode* _exp):exp(_exp){}
    virtual string genJson();
    virtual llvm::Value *genCode(CodeGenerator & gen);

    ExpNode* exp;
};
class BreakStmNode : public StmNode{
public:
    BreakStmNode(){}
    virtual string genJson();
    virtual llvm::Value *genCode(CodeGenerator & gen);
};
class IfStmNode : public StmNode{
public:
    IfStmNode(ExpNode* _exp,BlockNode*_block):exp(_exp),block(_block){}
    virtual string genJson();
    llvm::Value *genCode(CodeGenerator & gen);

    ExpNode *exp;
    BlockNode *block;
};
class IfElseStmNode : public StmNode{
public:
    IfElseStmNode(ExpNode* _exp,BlockNode*_block,BlockNode*block_):exp(_exp),ifblock(_block),elseblock(block_){}
    virtual string genJson();
    virtual llvm::Value *genCode(CodeGenerator & gen);

    ExpNode *exp;
    BlockNode *ifblock,*elseblock;
};
class WhileStmNode : public StmNode{
public:
    WhileStmNode(ExpNode* _exp,BlockNode*_block):exp(_exp),block(_block){}
    virtual string genJson();
    virtual llvm::Value *genCode(CodeGenerator & gen);
    ExpNode *exp;
    BlockNode *block;
};
class ForStmNode : public StmNode{
public:
    ForStmNode(ExpNode* _exp,BlockNode*_block):exp(_exp),block(_block){}
    virtual string genJson();
    virtual llvm::Value *genCode(CodeGenerator & gen);
    ExpNode *exp;
    BlockNode *block;
};
class ReturnNullStmNode : public StmNode{
public:
    ReturnNullStmNode(){}
    virtual string genJson();
    virtual llvm::Value *genCode(CodeGenerator & gen);

};
class ReturnStmNode : public StmNode{
public:
    ReturnStmNode(ExpNode* _exp):exp(_exp){}
    virtual string genJson();
    virtual llvm::Value *genCode(CodeGenerator & gen);

    ExpNode *exp;
};
class VarDecNode : public StmNode{
public:
    VarDecNode(IdentifierNode* _type ,IdentifierNode* _identifier ):type(_type),identifier(_identifier){}
    VarDecNode(IdentifierNode* _type ,IdentifierNode* _identifier, int _size ):type(_type),identifier(_identifier),size(_size){}
    VarDecNode(IdentifierNode* _type ,IdentifierNode* _identifier, ExpNode* assign ):type(_type),identifier(_identifier),exp(assign){}
    virtual string genJson();
    virtual llvm::Value *genCode(CodeGenerator & gen);

    IdentifierNode *type;
    IdentifierNode *identifier;
    ExpNode* exp;
    int size;

};
// using VarDecList = std::vector<VarDecNode>;
class FunDecNode : public StmNode{
public:
    FunDecNode(IdentifierNode *_type, IdentifierNode *_identifier, 
    vector<VarDecNode*> _args, BlockNode *_block) :  type(_type), identifier(_identifier), args(_args), block(_block) {}
    virtual string genJson();
    virtual llvm::Value *genCode(CodeGenerator & gen);

    IdentifierNode *type;
    IdentifierNode *identifier;
    BlockNode *block;
    vector<VarDecNode*> args;
};
#endif