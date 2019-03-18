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
    
    //methods
    virtual BitVector transferFunction(BitVector input,BasicBlock* block){
        BitVector returnVal;
        return returnVal;
    }
    BitVector runMeetOp(std::vector<BitVector> bitVectors);
    void runPassSetup(Function &F){
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
        
	    outs () << "Setting in of initial block\n";
        BasicBlock * initialBlock;
        if(direction){
            initialBlock=&(F.front());
        }
        else{
            for(Function::iterator FI = F.begin();FI!=F.end();++FI){
                if(isa<ReturnInst>(FI->getTerminator())){
                    initialBlock=&*FI;
                }
            }
            //Remove
            if(initialBlock==&*F.end()){
                outs()<< "SAME BLOCK AS END\n";
            }
            //Till here
        }
        outs() << "Setting out of all blocks";
        BlockMap[initialBlock].in=initialCondition;
        for(Function::iterator FI = F.begin(); FI != F.end();++FI){
            BlockMap[&*FI].out=boundaryCondition;
        }
        runPassFunction(F);
        

    }
    void runPassFunction(Function &F){
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
    }


    
    };

// Add definitions (and code, depending on your strategy) for your dataflow
// abstraction here.
}

#endif
