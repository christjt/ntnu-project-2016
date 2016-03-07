//
// Created by christopher on 07.03.16.
//

#include "SelfAssemblyMechanisms/include/EA/IncrementalMutationOperator.h"
#include <algorithm>

using namespace EA;

IncrementalMutationOperator::IncrementalMutationOperator(double mutationRate, double step) : MutationOperator(mutationRate)
{
    _step = step;
}

DoubleVectorGenotype IncrementalMutationOperator::apply(DoubleVectorGenotype parent, std::default_random_engine &random)
{
    std::vector<double> vector = parent.getVector();

    std::uniform_real_distribution<double> mutationDistribution(0, 1);

    std::uniform_real_distribution<double> stepDistribution(-_step, _step);

    for (unsigned int i = 0; i < vector.size(); ++i) {
        if(mutationDistribution(random) < _mutationRate){
            vector[i] = std::max(std::min(vector[i] + stepDistribution(random), 1.0), -1.0);
        }
    }

    DoubleVectorGenotype offspring(vector, parent.getRangeMin(), parent.getRangeMax());

    return offspring;
}
