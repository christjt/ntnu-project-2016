//
// Created by christopher on 11.11.15.
//

#ifndef ROBOROBO2_MUTATIONOPERATOR_H
#define ROBOROBO2_MUTATIONOPERATOR_H

#include "DoubleVectorGenotype.h"
#include <random>
#include <vector>

namespace EA{
    class MutationOperator{
    public:
        MutationOperator(double mutationRate);
        virtual DoubleVectorGenotype apply(DoubleVectorGenotype parent, std::default_random_engine &random) = 0;
    protected:
        double _mutationRate;
    };

}

#endif //ROBOROBO2_MUTATIONOPERATOR_H
