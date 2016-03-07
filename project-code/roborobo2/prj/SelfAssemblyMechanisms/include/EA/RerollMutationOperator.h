//
// Created by christopher on 07.03.16.
//

#ifndef ROBOROBO2_REROLLMUTATIONOPERATOR_H
#define ROBOROBO2_REROLLMUTATIONOPERATOR_H

#include "SelfAssemblyMechanisms/include/EA/MutationOperator.h"

namespace EA {
    class RerollMutationOperator : public MutationOperator{
    public:
        RerollMutationOperator(double mutationRate);
        DoubleVectorGenotype apply(DoubleVectorGenotype parent, std::default_random_engine &random);
    };
}




#endif //ROBOROBO2_REROLLMUTATIONOPERATOR_H
