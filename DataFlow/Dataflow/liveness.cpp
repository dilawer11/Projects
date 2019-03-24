// 15-745 S18 Assignment 2: liveness.cpp
// Group:
////////////////////////////////////////////////////////////////////////////////

#include "llvm/IR/Function.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include "available-support.h"
#include "dataflow.h"

using namespace llvm;

namespace {

    BitVector transferFunc(BitVector output,BasicBlock *block,std::map<void*,int> domainIndex,std::map<BasicBlock*,BasicBlockSt> BlockMap){
      int sz=output.size();
      BitVector use(sz,false);
      BitVector def(sz,false);
      BitVector inp(sz,false);
      BasicBlockSt chkblock=BlockMap[block];
      for (BasicBlock::iterator i=block->begin(), e = block->end(); i!=e; ++i) {
        Instruction *I= &*i;
        
        if (PHINode* phi_in = dyn_cast<PHINode>(&*I)){
          int ind=domainIndex[phi_in];
          
          // outs()<<*I<<"\n";
          int vals=phi_in->getNumIncomingValues();
          // iterate over all values
          for(int x=0;x<vals;x++){
            int a=0;
            Value *val=phi_in->getIncomingValue(x);
            if( isa <Instruction >(val)  ||  isa <Argument>(val)){
              // outs()<<*val<<"\n";
              BasicBlock *phi_block=phi_in->getIncomingBlock(x);
              BasicBlockSt *currBlockst=&BlockMap[block];
              // Check if block exists exists in vector
              std::vector<BasicBlock*>::iterator it = std::find(currBlockst->prev.begin(), currBlockst->prev.end(), phi_block);
              if(it==currBlockst->prev.end()){
                // place holder for now, condition met if there is no such block
                ((BlockMap[block]).prev).push_back(phi_block);
                it = std::find(currBlockst->prev.begin(), currBlockst->prev.end(), phi_block);
                // continue;
              }
              int index = std::distance(BlockMap[block].prev.begin(), it);
              // outs()<<*val<<"\n";
              int Instind=domainIndex[val];
              // set use value in that block as 1
              BasicBlock* prev=(currBlockst->prev)[index];
              // BasicBlockSt* neighbourBlockst=&BlockMap[prev];//Might need to change how I get the mapped second element
              // if(BlockMap[prev].out[Instind])
              BlockMap[prev].out[Instind]=1;
              // Making the variable to be defined since it exists previously
             // if(def[Instind]!=1){
               // use[ind]=1;
             // }
               use[ind]=1;
            }
          }
        }else{
          for(User::op_iterator OI= I->op_begin(); OI !=I->op_end(); ++OI){
            Value *val=*OI;
            if( isa <Instruction >(val)  ||  isa <Argument>(val)){
              // outs()<<*val<<"\n";
              int ind=domainIndex[val];//Getting the instruction via mapping, might be subject to change(the mapping is of Val instead)
              // Locally exposed use check
              //if(def[ind]!=1){
                use[ind]=1;
              //}
            }
          }
        }
        std::map<void*,int>::iterator it=domainIndex.find(I);
        if(it!=domainIndex.end()){
          def[it->second]=1;
        }
        // for(std::map<void*,int>::iterator is= domainIndex.begin(), ie=domainIndex.end();is!=ie;++is){
        //   if(inp[is->second]==1){
        //     outs()<<getShortValueName(static_cast<Value*>(is->first))<<", ";
        //   }
        // }
        // outs()<<"\n";
      }
      for(int i=0;i<sz;i++){
           if(output[i]==1){
             inp[i]=1;
           }
          if(def[i]==1){
            inp[i]=0;
          }
          if(use[i]==1 && def[i]==0){
            inp[i]=1;
          } 
      } 
      return inp;
    }
  class Liveness : public FunctionPass {
  public:
    static char ID;

    Liveness() : FunctionPass(ID) { }
    
  

    virtual bool runOnFunction(Function& F) {
      std::vector<void*>domain;
      std::vector<void*>::iterator it;
      //Fill Domain
      for (Function::iterator FI = F.begin(), FE = F.end(); FI != FE; ++FI) {
	      BasicBlock* block = &*FI;
        for(BasicBlock::iterator i= block->begin(),e=block->end();i!=e;i++){
          Instruction *I=&*i;
          if(PHINode* phi_in = dyn_cast<PHINode>(&*i)) {
            int rang=phi_in->getNumIncomingValues();
            for(int x=0;x<rang;x++){
              Value *val=phi_in->getIncomingValue(x);
              if( isa <Instruction >(val)  ||  isa <Argument>(val)){
                it = std::find(domain.begin(), domain.end(), val);
                if(it==domain.end()){
                  domain.push_back((void*)(&*(val)));
                }
                
              }
            }
          }else{
            for(User::op_iterator OI= i->op_begin(); OI !=i->op_end(); ++OI){
              Value *val=*OI;
              if( isa <Instruction >(val)  ||  isa <Argument>(val)){
                it = std::find(domain.begin(), domain.end(), val);
                if(it==domain.end()){
                  domain.push_back((void*)(&*(val)));
                }
              }
            }
          } 
        }
      }
      
      BitVector temp(domain.size(),0);
      // for(int i=0;i<domain.size();i++){
      //   Value *val=static_cast<Value*>(domain[i]);
      //   outs()<<*val<<"\n";
      // }
      DataFlow obj(false,true,temp,temp,domain);
      obj.transferFunction = &transferFunc;
      obj.runPassSetup(F);
      
      
      
      for(int i=obj.blockOrdering.size()-1;i>=0;i--){
	      outs() << *obj.blockOrdering[i] << "\n";
        BitVector inp=(obj.BlockMap[obj.blockOrdering[i]]).out;
        outs()<<"{";
        for(std::map<void*,int>::iterator is= obj.domainIndex.begin(), ie=obj.domainIndex.end();is!=ie;++is){
          if(inp[is->second]==1){
            outs()<<getShortValueName(static_cast<Value*>(is->first))<<",";
          }
        }
        outs()<<"}\n\n";
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
