//
// Created by christopher on 11.11.15.
//

#include "SelfAssemblyMechanisms/include/EA/CrossoverOperator.h"

using namespace EA;
CrossoverOperator::CrossoverOperator(int nCrossoverPoints) {
    _nCrossOverpoints = nCrossoverPoints;
}


DoubleVectorGenotype CrossoverOperator::apply(DoubleVectorGenotype parent1, DoubleVectorGenotype parent2, std::default_random_engine random){
    std::vector<double> vector =  parent1.getVector();

    std::uniform_int_distribution<int> distribution(0, vector.size());

    std::vector<int> crossoverPoints(_nCrossOverpoints);

    for (int i = 0; i < _nCrossOverpoints; ++i) {
        crossoverPoints[i] = distribution(random);
    }

    sort(crossoverPoints.begin(), crossoverPoints.end());

    std::vector<double> currVector;

    for (int j = 0; j < _nCrossOverpoints; ++j) {
        currVector = (j % 2 == 0 ? parent2 : parent1).getVector();
        Crossover(vector, currVector, crossoverPoints[j]);
    }

    DoubleVectorGenotype newChild(vector, parent1.getRangeMin(), parent1.getRangeMax());

    return newChild;
}

void CrossoverOperator::Crossover(std::vector<double> &dest, std::vector<double> &source, int crossoverPoint){
    for (unsigned int i = crossoverPoint; i < dest.size(); ++i) {
        dest[i] = source[i];
    }
}