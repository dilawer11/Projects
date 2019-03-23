// 15-745 S18 Assignment 2: available.cpp
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
BitVector transferFunc(BitVector input,BasicBlock* block,std::map<void*,int>domainIndex,std::map<BasicBlock*,BasicBlockSt>BlockMap){
        // printBitVector(input);
	      // outs() << "Transfer Function Called\n";
        int sz=input.size();
        BitVector gen(sz,false);
        BitVector kill(sz,false);
        BitVector out(sz,false);
        if(!block){
          outs() << "ERR: NULL PTR TO BLOCK\n";
          return out;
        }
        for (BasicBlock::iterator i = block->begin(), e = block->end(); i!=e; ++i) {
          Instruction* I = &*i;
          // First calculating Generated defs
          
          if (BinaryOperator *BI = dyn_cast<BinaryOperator>(I)) {
		          int ind=domainIndex[(void*)(&*(BI))];
              if(input[ind]==0){
                  gen[ind]=1;
              }else if(input[ind]==1){
                  kill[ind]=1;
              }
              // UNION
              for(int x=0;x<out.size();x++){
                  if(gen[x]==1 || input[x]==1){
                      out[x]=1;
                  }
                  if(kill[x]==1){
                      out[x]=0;
                  }
              }
          }
          // (Input_instructions /U/ (Generated)) //XOR (Killed)
      }
	// outs() << "Transfer Function Returned with output : \n";
	// printBitVector(out);
    return out;
    }


  class AvailableExpressions : public FunctionPass {
    
  public:
    static char ID;
    
    AvailableExpressions() : FunctionPass(ID) { }
    
    
    virtual bool runOnFunction(Function& F) {
      
      // Here's some code to familarize you with the Expression
      // class and pretty printing code we've provided:
	  vector<Expression> expressions;
    std::vector<void*> domain;
    for (Function::iterator FI = F.begin(), FE = F.end(); FI != FE; ++FI) {
	    BasicBlock* block = &*FI;
	    for (BasicBlock::iterator i = block->begin(), e = block->end(); i!=e; ++i) {
	      Instruction* I = &*i;
	      // We only care about available expressions for BinaryOperators
	      if (BinaryOperator *BI = dyn_cast<BinaryOperator>(I)) {
	    // Create a new Expression to capture the RHS of the BinaryOperator
	        expressions.push_back(Expression(BI));
		domain.push_back((void*)(&*(BI)));
	      }
	    }
    }
    BitVector temp(domain.size(),0);
     
    DataFlow obj(true,false,temp,temp,domain);
    obj.transferFunction = &transferFunc;  
    obj.runPassSetup(F);

    for(int i=0;i<obj.blockOrdering.size();i++){
      outs() << *obj.blockOrdering[i]<<"\n";
      outs() << "Available Expressions After Block:\n";
      printAvailable(&expressions,obj.BlockMap[obj.blockOrdering[i]].out);
    }
      
      // Did not modify the incoming Function.
      return false;
    }
    
    virtual void getAnalysisUsage(AnalysisUsage& AU) const {
      AU.setPreservesAll();
    }
    
  private:
  };
  
  char AvailableExpressions::ID = 0;
  RegisterPass<AvailableExpressions> X("available",
				       "15745 Available Expressions");
}
