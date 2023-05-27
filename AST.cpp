#include "CodeGenerator.hpp"
llvm::Value* VarDecNode::genCode(CodeGenerator & gen) {  
    if(size == 0){ //������
        llvm::Type* llvmType = getLLvmType(type.name);
        // ȫ�ֱ���
        if(globalContext.currentFunc == nullptr) {
            //cout << "Creating global variable declaration " << type.name << " " << identifier.name<< endl;
            //
            //���ұ�����ֹ���¶���
            llvm::GlobalVariable *tmp = globalContext.myModule->getNamedGlobal(identifier.name);
            if(tmp != nullptr){
                throw logic_error("Redefined Global Variable: " + identifier.name);
            }
            //�½�ȫ�ֱ���
            llvm::GlobalVariable* New_globalVar = new llvm::GlobalVariable(*(globalContext.myModule), llvmType, false, llvm::GlobalValue::PrivateLinkage, 0, identifier.name);
            //���� �� �����鵥������ƫ��Ϊ0
            New_globalVar->setInitializer(llvm::ConstantInt::get(llvmType, 0));
            return nullptr;
        } else {//�����ڲ�����
            //cout << "Creating local variable declaration " << type.name << " " << identifier.name<< endl;
            //ָ��ǰ������
            auto *block = Builder.GetInsertBlock();
            //
            // ��ǰ�����Ѿ��иñ���, �ظ�����        
            if(globalContext.getTop().count(identifier.name) != 0) {
                throw logic_error("Redefined Local Variable: " + identifier.name);
            }
            //
            //�ռ�����
            llvm::AllocaInst *alloc = new llvm::AllocaInst(llvmType,block->getParent()->getParent()->getDataLayout().getAllocaAddrSpace(),(identifier.name.c_str()), block);
            // ���¶���ı������ͺ͵�ַ������ű���
            globalContext.getTopType()[identifier.name] = llvmType;
            globalContext.getTop()[identifier.name] = alloc;
            //�Ƿ�ֵ
            if (exp != NULL) {
                AssignNode assign(identifier, *exp);
                assign.genCode(globalContext);
            }
            return alloc;
        }
    }
    else{ //����
        llvm::Type* llvmType = getArrayLLvmType(type.name, size); 
        if(globalContext.currentFunc == nullptr) { //��ǰ����Ϊ�գ�Ϊȫ�����鶨��
            //cout << "Creating global array declaration " << type.name << " " << identifier.name<< endl;
            //���ұ�����ֹ���¶���
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
        else {//�ǿ� Ϊ�ڲ�����
            if(globalContext.getTop().count(identifier.name) != 0) {
                // ��ǰ�����иñ���, �ظ�����
                throw logic_error("Redefined Local Variable: " + identifier.name);
            }

            if(globalContext.isArgs) {
                // ����Ǻ��������ж����������Ҫ���� ָ������
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
        if(it->size == 0)//������������size��ֵΪ0
            args_types.push_back(getLLvmType(it->type.name));
        else//array 
        {
            args_types.push_back(getPtrLLvmType(it->type.name));
        }
    }
    //FunctionType::get��������Ϊ�����ĺ���ԭ�ʹ�����Ӧ��FunctionType����
    //���FunctionType::get������args_typesΪ�������͡��Ե���typeΪ����ֵ���ͣ�
    //������һ�������������ɱ䣨���һ������false���������˼���ĺ������͡�
    llvm::FunctionType *Ftype = llvm::FunctionType::get(getLLvmType(type.name), makeArrayRef(args_types), false);
    //
    // ��ExternalLinkage����ʾ�ú������ܶ����ڵ�ǰģ��֮�⣬��/����Ա���ǰģ��֮��ĺ�������;name������;���ű�ע��
    llvm::Function *F = Function::Create(Ftype, llvm::Function::ExternalLinkage, identifier->name.c_str(), gen.module);
    //
    //�½���һ����Ϊ��entry���Ļ���������Ժ�ö��󽫱�����F
    llvm::BasicBlock *basicblock = llvm::BasicBlock::Create(globalContext, "entry", F);
    //����Builder����������ָ��Ӧ�ò����ո��½��Ļ������ĩβ��
    Builder.SetInsertPoint(basicblock);

    gen.currentFunc = F;
    gen.returnBB = llvm::BasicBlock::Create(globalContext, "return", F);
    
    
    //�����з���ֵs
    if(type.name.compare("void") != 0) {
        //����ֵ�ռ����
        globalContext.returnVal = new llvm::AllocaInst(getLLvmType(type.name), baiscblock->getParent()->getParent()->getDataLayout().getAllocaAddrSpace(), "", basicblock);
    }
    //ѹ���·��ű�
	globalContext.pushBlock();
	llvm::Function::arg_iterator args_Values = F->arg_begin();
    llvm::Value* Tmp_Value;
    //��������
    globalContext.isArgs = true;// (*it).genCode(globalContext);��
    for(auto it : args){
        (*it).genCode(globalContext);
        //??     Tmp_Value = &*args_Values++;
        Tmp_Value = args_Values;
        args_Values++;
        Tmp_Value->setName((it)->identifier.name.c_str());
        //StoreInst (Value *Val, Value *Ptr, bool isVolatile, BasicBlock *InsertAtEnd)
        //          Ҫ���ֵ    ��Ŀ��洢ָ�룬�Ƿ��ױ�    �������Ŀ���档
        llvm::StoreInst *inst = new llvm::StoreInst(Tmp_Value, globalContext.getTop()[(it)->identifier.name], false, basicblock);
	}
    globalContext.isArgs = false;
	//���������鴦��
	block.genCode(globalContext);
    //����hasreturn
    globalContext.hasReturn = false;
    //return�����
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