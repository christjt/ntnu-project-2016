//
// Created by christopher on 07.03.16.
//

#ifndef ROBOROBO2_INCREMENTALMUTATIONOPERATOR_H
#define ROBOROBO2_INCREMENTALMUTATIONOPERATOR_H

#include "SelfAssemblyMechanisms/include/EA/MutationOperator.h"

namespace EA
{
    class IncrementalMutationOperator : public MutationOperator
    {
        public:
            IncrementalMutationOperator(double mutationRate, double step);
            DoubleVectorGenotype apply(DoubleVectorGenotype parent, std::default_random_engine &random);
        private:
            double _step;
    };
}



#endif //ROBOROBO2_INCREMENTALMUTATIONOPERATOR_H
