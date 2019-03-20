// 15-745 S18 Assignment 2: dataflow.h
// Group:
////////////////////////////////////////////////////////////////////////////////

#ifndef __CLASSICAL_DATAFLOW_H__
#define __CLASSICAL_DATAFLOW_H__
#include <stdio.h>
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include "llvm/IR/Instructions.h"
#include "llvm/ADT/BitVector.h"
#include "llvm/ADT/DenseMap.h"
#include "llvm/IR/ValueMap.h"
#include "llvm/IR/CFG.h"
#include "llvm/Support/raw_ostream.h"
namespace llvm {
    struct BasicBlockSt{
	    std::vector<BasicBlock*> prev; //All the blocks previous in running of this type (succ in backwards, pred in forwards)
        BitVector in;   //Input BitVector of the block (direction dependant)
        BitVector out; //Output BitVector of the block (direction dependant)
    };
    struct DFResult{
        //Fill in if necessary
    };

    class DataFlow{
    public:
        
    
    //variables
    bool direction; //true for forwards, false for backwards
    std::vector<void*> rawDomain; //pointers of domain
    std::map<void*,int> domainIndex; //Index to BitVectors of the domains
    bool meetOp;  //true for union, false for intersection
    BitVector initialCondition;
    BitVector boundaryCondition;
    std::map<BasicBlock*,BasicBlockSt> BlockMap;
    int bSize=0;
    std::vector<BasicBlock*> blockOrdering;
    DataFlow(bool,bool,BitVector,BitVector,std::vector<void*> domain);
    
    BitVector (*transferFunction)(BitVector,BasicBlock* ,std::map<void*,int> ,std::map<BasicBlock*,BasicBlockSt>);

    //methods
    // virtual BitVector transferFunction(BitVector input,BasicBlock* block){
    //     BitVector returnVal;
    //     return returnVal;
    // }
    BitVector runMeetOp(std::vector<BitVector> bitVectors);
    void runPassSetup(Function &F);
    void runPassFunction(Function &F);
    void printBitVector(BitVector toPrint);
    // virtual BitVector transferFunction(BitVector,BasicBlock* ,std::map<void*,int> ,std::map<BasicBlock*,BasicBlockSt>);

    
    };

// Add definitions (and code, depending on your strategy) for your dataflow
// abstraction here.
}

#endif
