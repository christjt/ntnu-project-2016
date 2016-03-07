//
// Created by christopher on 07.03.16.
//

#include "SelfAssemblyMechanisms/include/EA/RerollMutationOperator.h"
#include "SelfAssemblyMechanisms/include/EA/DoubleVectorGenotype.h"

using namespace EA;
RerollMutationOperator::RerollMutationOperator(double mutationRate) : MutationOperator(mutationRate)
{
    //Do nothing
}

DoubleVectorGenotype RerollMutationOperator::apply(DoubleVectorGenotype parent, std::default_random_engine &random)
{
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
