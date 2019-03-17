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
        vector<BasicBlockSt*> prev;
        BitVector in;
        BitVector out=boundaryCondition;
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
    BitVector runMeetOp(vector<BitVector> bitVectors);
    void runPass(Function &F){
        //setup Prev List
        for (Function::iterator FI = F.begin(), FE = F.end(); FI != FE; ++FI) {
	        BasicBlock* block = &*FI;
            if(direction){
                for(pred_iterator PI = pred_begin(BB); PI != pred_end(BB); ++PI){
                    BlockMap[block].prev.push_back(*PI);
                }
            }
            else{
                for(succ_iterator SI = succ_begin(BB); SI != succ_end(BB); ++SI){
                    BlockMap[block].prev.push_back(*SI);
                }
            }
        }
        // for(std::map<BasicBlock*,BasicBlockSt::iterator it =BlockMap.begin();it!=BlockMap.end();++it){
        //     it->second.out=boundaryCondition;
        // }
        for(std::map<BasicBlock*,BasicBlockSt>::iterator it = BlockMap.begin();it!=BlockMap.end();++it){
            if(it->second.prev.size()==0){
                it->second.prev.in=initialCondition;
                outs() << "Found Initial Basic Block\n"; //Remove this later
            }
        }
    }


    
    };

// Add definitions (and code, depending on your strategy) for your dataflow
// abstraction here.
}

#endif
