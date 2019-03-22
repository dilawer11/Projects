// 15-745 S18 Assignment 2: liveness.cpp
// Group:
////////////////////////////////////////////////////////////////////////////////


#include "llvm/IR/Function.h"
#include "llvm/Pass.h"
#include "llvm/IR/Constants.h"
#include "llvm/Support/raw_ostream.h"

#include "dataflow.h"
#include "available-support.h"

using namespace llvm;
using namespace std;


namespace {

    BitVector transferFunc(BitVector output,BasicBlock *block,std::map<void*,int> domainIndex,std::map<BasicBlock*,BasicBlockSt> BlockMap){
      int sz=output.size();
      BitVector use(sz,false);
      BitVector def(sz,false);
      BitVector in(sz,false);
      for (BasicBlock::iterator i=block->begin(), e = block->end(); i!=e; ++i) {
        Instruction *I= &*i;
        if (PHINode* phi_in = dyn_cast<PHINode>(&*i)) {
          // int ind=domainIndex[phi_in];
          int vals=phi_in->getNumIncomingValues();
          // iterate over all values
          for(int x=0;x<vals;x++){
            int a=0;
            Value *val=phi_in->getIncomingValue(x);
            if( isa <Instruction >(val)  ||  isa <Argument>(val)){
              BasicBlock *phi_block=phi_in->getIncomingBlock(x);
              BasicBlockSt *currBlockst=&BlockMap[block];
              // Check if block exists exists in vector
              std::vector<BasicBlock*>::iterator it = std::find(currBlockst->prev.begin(), currBlockst->prev.end(), phi_block);
              if(it==currBlockst->prev.end()){
                // place holder for now, condition met if there is no such block
                (currBlockst->prev).push_back(phi_block);
                it = std::find(currBlockst->prev.begin(), currBlockst->prev.end(), phi_block);
              }
              
              int index = std::distance(currBlockst->prev.begin(), it);
              int Instind=domainIndex[(void*)(&*(val))];
              // set use value in that block as 1
              BasicBlock* prev=(currBlockst->prev)[index];
              BasicBlockSt* neighbourBlockst=&BlockMap[prev];//Might need to change how I get the mapped second element
              // BitVector nbrOut=BasicBlockSt
              (neighbourBlockst->out)[Instind]=1;
            }
          }
        }else{
          for(User::op_iterator OI= i->op_begin(); OI !=i->op_end(); ++OI){
            Value *val=*OI;
            if( isa <Instruction >(val)  ||  isa <Argument>(val)){
              //val used
              int ind=domainIndex[(void*)(&*(val))];//Getting the instruction via mapping, might be subject to change(the mapping is of Val instead)
              use[ind]=1; 
            }
          }
        }
        std::map<void*,int>::iterator it=domainIndex.find(I);
        if(it!=domainIndex.end()){
          def[it->second]=1;
        }
      }
      // use U (output-Def)
      for(int i=0;i<sz;i++){
        if(output[i]==1){
          in[i]=1;
        }
        if(def[i]==1){
          in[i]=0;
        }
        if(use[i]==1){
          in[i]=1;
        }
      }
      return in;
    }
  class Liveness : public FunctionPass {
  public:
    static char ID;

    Liveness() : FunctionPass(ID) { }
    
  

    virtual bool runOnFunction(Function& F) {
      std::vector<void*>domain;
      outs() << "Running\n";
      //Fill Domain
      for (Function::iterator FI = F.begin(), FE = F.end(); FI != FE; ++FI) {
	      BasicBlock* block = &*FI;
        for(BasicBlock::iterator i= block->begin(),e=block->end();i!=e;i++){
          Instruction *I=&*i;
          for(User::op_iterator OI= i->op_begin(); OI !=i->op_end(); ++OI){
            Value *val=*OI;
            if( isa <Instruction >(val)  ||  isa <Argument>(val)){
              if(std::find(domain.begin(),domain.end(),val)== domain.end()){
                  domain.push_back((void*)(&*(val)));
                  outs () << *val << " ";
              }
              
            }
          }
        } 
  
      }
      outs () << "\n";
      BitVector temp(domain.size(),0);  
      DataFlow obj(false,true,temp,temp,domain);
      obj.transferFunction=&transferFunc;
      obj.runPassSetup(F);
      outs()<<domain.size()<<"\n";
      // outs() << "\n\n\n";
      // for(int i=0 ;i<obj.blockOrdering.size();i++){
      //   outs() << obj.blockOrdering[i] << "\n";
      //   outs() << *obj.blockOrdering[i] << "\n\n";
      // }
      // outs() << "\n\n\n";
    for(int i=0;i<obj.blockOrdering.size();i++){
      printBitVector((obj.BlockMap[obj.blockOrdering[i]]).out);
    }	 
  
      return false;
    }

    virtual void getAnalysisUsage(AnalysisUsage& AU) const {
      AU.setPreservesAll();
    }

  private:
  };

  char Liveness::ID = 0;
  RegisterPass<Liveness> X("liveness", "15745 Liveness");
}
