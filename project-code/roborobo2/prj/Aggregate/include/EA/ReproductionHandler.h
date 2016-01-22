//
// Created by christopher on 11.11.15.
//

#ifndef ROBOROBO2_REPRODUCTIONHANDLER_H
#define ROBOROBO2_REPRODUCTIONHANDLER_H

#include <random>
#include <vector>
#include "MutationOperator.h"
#include "CrossoverOperator.h"

namespace EA
{
    class ReproductionHandler
    {
    private:
        CrossoverOperator _cross;
        MutationOperator _mutate;
    public:
        ReproductionHandler(std::default_random_engine &random, CrossoverOperator cross, MutationOperator mutate);
        std::vector<DoubleVectorGenotype> produceOffspring(std::vector<DoubleVectorGenotype> matingParents, std::default_random_engine &random);
    };
}

#endif //ROBOROBO2_REPRODUCTIONHANDLER_H
