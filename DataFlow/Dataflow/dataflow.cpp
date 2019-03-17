// 15-745 S18 Assignment 2: aataflow.cpp
// Group:
////////////////////////////////////////////////////////////////////////////////

#include "dataflow.h"

namespace llvm {
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

  // Add code for your dataflow abstraction here.
}
