// 15-745 S18 Assignment 2: aataflow.cpp
// Group:
////////////////////////////////////////////////////////////////////////////////

#include "dataflow.h"

namespace llvm {
  DataFlow::DataFlow(bool pDirection,bool pMeetOp,BitVector pInitCond,BitVector pBoundaryCondition,std::vector<void*> domain){
    direction=pDirection;
    meetOp=pMeetOp;
    initialCondition=pInitCond;
    boundaryCondition=pBoundaryCondition;
    rawDomain=domain;
    bSize=rawDomain.size();
    //setup domain;
    for(int i=0;i<bSize;i++){
      domainIndex[rawDomain[i]]=i;
    }
    
  }
    BitVector DataFlow::transferFunction(BitVector input,BasicBlock* block,std::map<void*,int> domainIndex,std::map<BasicBlock*,BasicBlockSt> BlockMap){
        // printBitVector(input);
	outs() << "Transfer Function Called\n";
        int sz=input.size();
        BitVector gen(sz,false);
        BitVector kill(sz,false);
        BitVector out(sz,false);
        for (BasicBlock::iterator i = block->begin(), e = block->end(); i!=e; ++i) {
          Instruction* I = &*i;
          // First calculating Generated defs
          
          if (BinaryOperator *BI = dyn_cast<BinaryOperator>(I)) {
              int ind=domainIndex[I];
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
    return out;
    }
  BitVector DataFlow::runMeetOp(std::vector<BitVector> bitVectors)
  {
    BitVector returnBV;
    for(int i=0;i<bitVectors.size();i++){
        if(meetOp){
            returnBV |=bitVectors[i];
        }
        else{
            returnBV &=bitVectors[i];
        }
    }
    return returnBV;
  }
  void DataFlow::runPassFunction(Function &F){
    bool valueChanged = true;
    while(valueChanged){
        valueChanged = false;
        for(int i = 0; i < blockOrdering.size(); i++){//may need to code seperately for different directions
            std::vector<BitVector> prevVectors;
            for(int i=0;i<BlockMap[blockOrdering[i]].prev.size();i++){
              BasicBlock* block = BlockMap[blockOrdering[i]].prev[i];	
              prevVectors.push_back(BlockMap[block].out);
            }
            BitVector input = runMeetOp(prevVectors);
            if (input != BlockMap[blockOrdering[i]].in){
              BitVector output = transferFunction(BlockMap[blockOrdering[i]].in,blockOrdering[i],domainIndex,BlockMap); //change this according to transfer function
              valueChanged = true;
              BlockMap[blockOrdering[i]].out=output;
            } 
        }
    }
    
   
  }
  void DataFlow::runPassSetup(Function &F){
    outs()  << "Setting up prev list\n";
    for (Function::iterator FI = F.begin(), FE = F.end(); FI != FE; ++FI) {
      BasicBlock* block = &*FI;
        if(direction){
            for(pred_iterator PI = pred_begin(block); PI != pred_end(block); ++PI){
                (BlockMap[block].prev).push_back(*PI);
            }
        }
        else{
            for(succ_iterator SI = succ_begin(block); SI != succ_end(block); ++SI){
                BlockMap[block].prev.push_back(*SI);
            }
        }
        // BlockMap[]
    }
    BasicBlock * start = &(F.front());
    BasicBlock * end;
    for(Function::iterator FI = F.begin();FI!=F.end();++FI){
      if(isa<ReturnInst>(FI->getTerminator())){
        end=&*FI;
      }
    }
    
  outs () << "Setting in of initial block\n";
    BasicBlock * initialBlock;
    BasicBlock * endingBlock;
    if(direction){
      initialBlock=start;
      endingBlock=end;
    }
    else{
      initialBlock=end;
      endingBlock=start;
    }
    outs() << "Setting out of all blocks\n";
    BlockMap[initialBlock].in=initialCondition;
    for(Function::iterator FI = F.begin(); FI != F.end();++FI){
        BlockMap[&*FI].out=boundaryCondition;
    }
    
    //Setting Block Ordering (TODO)
    blockOrdering.push_back(initialBlock);
    for (int i=0; i<blockOrdering.size(); ++i) {
      outs() << "Turn Order : " << i << "\n";
      BasicBlock* block = blockOrdering[i];
      if(direction){
        for(succ_iterator B = succ_begin(block); B != succ_end(block); ++B){
          if(std::find(blockOrdering.begin(),blockOrdering.end(),*B)==blockOrdering.end()){
            blockOrdering.push_back(*B);
          }
        }
      }
      else{
        for(pred_iterator B = pred_begin(block); B != pred_end(block); ++B){
          if(std::find(blockOrdering.begin(),blockOrdering.end(),*B)==blockOrdering.end()){
            blockOrdering.push_back(*B);
          }
        }
      }
    }
  runPassFunction(F); 
  outs() << "Done With Running Value Converged to\n";
  printBitVector(BlockMap[endingBlock].out);
  }
  void printBitVector(BitVector toPrint){
    if(toPrint.size() == 0){
      outs() << "-";
    }
    else{
      for(int i = 0; i < toPrint.size() ; i++)
      {
        if(toPrint[i] == true)
          outs() << "1";
        else
          outs() << "0";
      }
    }
    outs() << "\n";

  }

  // Add code for your dataflow abstraction here.
}
