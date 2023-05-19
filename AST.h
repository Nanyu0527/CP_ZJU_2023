#ifndef AST_NODE
#define AST_NODE

#include <iostream>
#include <string>
#include <vector>
#include <llvm/IR/Value.h>
#include "llvm/ADT/STLExtras.h"

using namespace std;

class Node {
public:
    Node() {}
    virtual ~Node() {}
    virtual void GenJson(){}
};

class StmNode : public Node{

};
class ExpNode : public Node{

};


#endif