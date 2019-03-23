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
    BitVector returnBV=bitVectors[0];
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
    // int iterationCount =1;
    while(valueChanged){
        valueChanged = false;
        // outs() << "Iteration : " << iterationCount++ << "\n";
        for(int i = 0; i < blockOrdering.size(); i++){//may need to code seperately for different directions
            std::vector<BitVector> prevVectors;
        	// outs() << "Prev Size = "  << BlockMap[blockOrdering[i]].prev.size() << "\n";
	      // printBitVector(BlockMap[blockOrdering[i]].in);
	       	if(!i){
		       prevVectors.push_back(BlockMap[blockOrdering[i]].in);
	       }	       
	    for(int j=0;j<BlockMap[blockOrdering[i]].prev.size();j++){
              BasicBlock* block = BlockMap[blockOrdering[i]].prev[j];
      		// outs() << block << "\n";	      
              prevVectors.push_back(BlockMap[block].out);
            }
            BitVector input = runMeetOp(prevVectors);
	    BlockMap[blockOrdering[i]].in=input;
            BitVector oldOutput = BlockMap[blockOrdering[i]].out;
            BitVector output = transferFunction(input,blockOrdering[i],domainIndex,BlockMap); //change this according to transfer function
            if (output != oldOutput){
              valueChanged = true;
              BlockMap[blockOrdering[i]].out=output;
            } 
        }
    }
    
   
  }
  void DataFlow::runPassSetup(Function &F){
    // outs()  << "Setting up prev list\n";
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
    }
    BasicBlock * start = &(F.front());
    BasicBlock * end;
    for(Function::iterator FI = F.begin();FI!=F.end();++FI){
      if(isa<ReturnInst>(FI->getTerminator())){
        end=&*FI;
      }
    }
    
  // outs () << "Setting in of initial block\n";
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
    // outs() << "Setting out of all blocks\n";
    BlockMap[initialBlock].in=initialCondition;
    for(Function::iterator FI = F.begin(); FI != F.end();++FI){
        BlockMap[&*FI].out=boundaryCondition;
    }
    
    
    //Setting Block Ordering (TODO)
    if(direction){
        blockOrdering.push_back(initialBlock);
        for (int i=0; i<blockOrdering.size(); ++i) {
          BasicBlock* block = blockOrdering[i];
            for(succ_iterator B = succ_begin(block); B != succ_end(block); ++B){
              if(std::find(blockOrdering.begin(),blockOrdering.end(),*B)==blockOrdering.end()){
                blockOrdering.push_back(*B);
              }
            }
        }
    }
    else{
      for(po_iterator<BasicBlock*> I = po_begin(&F.getEntryBlock()), E = po_end(&F.getEntryBlock()); I != E ; ++I){
          if(std::find(blockOrdering.begin(),blockOrdering.end(),*I)==blockOrdering.end()){
            blockOrdering.push_back(*I);
          }
      }
    }
    

   

    // //Remove this 
    // for(Function::iterator FI = F.begin(); FI!=F.end();++FI){
    // 	outs()<< &*FI << " ";
    // }
    // outs() << "\n";
    // for(int i=0;i<blockOrdering.size();i++){
    // 	outs() << blockOrdering[i] << " ";
    // }
    // outs() << "\n";
    // outs() << "Initial Block = " << initialBlock << "\n";
    // outs() << "Ending Block = " << endingBlock << "\n";

    // //Till here
    
  runPassFunction(F); 
 // outs() << "Done With Running Value Converged to\n";
  //printBitVector(BlockMap[endingBlock].out);
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
