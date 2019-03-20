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
        Function::iterator start;
        Function::iterator end;
        if(direction){
            start=F.begin();
            end=F.end();
        }
        else{
            start=F.end();
            end=F.begin();
        }
        for(Function::iterator FI = start; FI!=end; FI){//may need to code seperately for different directions
            std::vector<BitVector> prevVectors;
            for(int i=0;i<BlockMap[&*FI].prev.size();i++){
              BasicBlock* block = BlockMap[&*FI].prev[i];	
              prevVectors.push_back(BlockMap[block].out);
            }
            BitVector input = runMeetOp(prevVectors);
            if (input != BlockMap[&*FI].in){
              BitVector output = transferFunction(BlockMap[&*FI].in,&*FI); //change this according to transfer function
              valueChanged = true;
              BlockMap[&*FI].out=output;
            } 
            if(direction){
              ++FI;
            } 
            else{
              --FI;
            } 
        }
    }
    outs() << "Done With Running Value Converged to\n";
   
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
    runPassFunction(F);
    printBitVector(BlockMap[endingBlock].out);
    //Setting Block Ordering (TODO)
    for (int i=0; i<blockOrdering.size(); ++i) {
      outs() << "Turn Order : " << i << "\n";
      BasicBlock* block = blockOrdering[i];
      if(direction){
        for(succ_iterator B = succ_begin(block); B != succ_end(block); ++B){
          if(std::find(blockOrdering.begin(),blockOrdering.end(),*B)!=blockOrdering.end()){
            blockOrdering.push_back(*B);
          }
        }
      }
      else{
        for(pred_iterator B = pred_begin(block); B != pred_end(block); ++B){
          if(std::find(blockOrdering.begin(),blockOrdering.end(),*B)!=blockOrdering.end()){
            blockOrdering.push_back(*B);
          }
        }
      }
    }
    
  }
  void DataFlow::printBitVector(BitVector toPrint){
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
