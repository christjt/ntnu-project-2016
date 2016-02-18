//
// Created by christopher on 11.11.15.
//

#include "Aggregate/include/EA/MutationOperator.h"
#include "Aggregate/include/EA/DoubleVectorGenotype.h"

using namespace EA;
MutationOperator::MutationOperator(double mutationRate) {
    _mutationRate = mutationRate;
}

DoubleVectorGenotype MutationOperator::apply(DoubleVectorGenotype parent, std::default_random_engine &random) {
    std::vector<double> vector = parent.getVector();

    std::uniform_real_distribution<double> rangeDistribution(parent.getRangeMin(), parent.getRangeMax());
    std::uniform_real_distribution<double> mutationDistribution(0, 1);

    for (unsigned int i = 0; i < vector.size(); ++i) {
        if(mutationDistribution(random) < _mutationRate){
            vector[i] = rangeDistribution(random);
        }
    }

    DoubleVectorGenotype offspring(vector, parent.getRangeMin(), parent.getRangeMax());

    return offspring;
}