// 15-745 S18 Assignment 2: dataflow.h
// Group:
////////////////////////////////////////////////////////////////////////////////

#ifndef __CLASSICAL_DATAFLOW_H__
#define __CLASSICAL_DATAFLOW_H__
#include <stdio.h>
#include <iostream>
#include <queue>
#include <vector>
#include "llvm/IR/Instructions.h"
#include "llvm/ADT/BitVector.h"
#include "llvm/ADT/DenseMap.h"
#include "llvm/IR/ValueMap.h"
#include "llvm/IR/CFG.h"

namespace llvm {
    struct BasicBlockSt{
	std::vector<BasicBlock*> prev;
        BitVector in;
        BitVector out;
    };
    struct DFResult{

    };

    class DataFlow{
    public:
        
    
    //variables
    bool direction; //true for forwards, false for backwards
    std::vector<void*> rawDomain;
    bool meetOp;  //true for union, false for intersection
    BitVector initialCondition;
    BitVector boundaryCondition;
    std::map<BasicBlock*,BasicBlockSt> BlockMap;

    //methods
    BitVector runMeetOp(std::vector<BitVector> bitVectors);
    void runPass(Function &F){
        //setup Prev List
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
        // for(std::map<BasicBlock*,BasicBlockSt::iterator it =BlockMap.begin();it!=BlockMap.end();++it){
        //     it->second.out=boundaryCondition;
        // }
	outs () << "HERE I AM\n";
        for(std::map<BasicBlock*,BasicBlockSt>::iterator it = BlockMap.begin();it!=BlockMap.end();++it){
        outs() <<  it->second.prev.size() << " ";
    	outs() << "\n";
	for(int i=0;i<it->second.prev.size();i++){
	    outs() << it->second.prev[i] << " ";
	}
	outs() << "\n";	
	if(it->second.prev.size()==0){
                (it->second).in=initialCondition;
                outs() << "Found Initial Basic Block\n"; //Remove this later
            }
        }
    }


    
    };

// Add definitions (and code, depending on your strategy) for your dataflow
// abstraction here.
}

#endif
