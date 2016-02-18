//
// Created by christopher on 11.11.15.
//

#include "Aggregate/include/EA/ReproductionHandler.h"
#include <iostream>
using namespace EA;
ReproductionHandler::ReproductionHandler(std::default_random_engine &random, CrossoverOperator cross, MutationOperator mutate) : _cross(cross), _mutate(mutate)
{
}

std::vector<DoubleVectorGenotype> ReproductionHandler::produceOffspring(std::vector<DoubleVectorGenotype> matingParents, std::default_random_engine &random)
{
    std::vector<DoubleVectorGenotype> children;
    for (unsigned int i = 0; i < matingParents.size(); i = i + 2) {
        children.push_back(_mutate.apply(_cross.apply(matingParents[i], matingParents[i + 1], random), random));
        children.push_back(_mutate.apply(_cross.apply(matingParents[i + 1], matingParents[i], random), random));
    }

    return children;
}