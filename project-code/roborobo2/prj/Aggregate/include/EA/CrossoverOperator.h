//
// Created by christopher on 11.11.15.
//

#ifndef ROBOROBO2_CROSSOVEROPERATOR_H
#define ROBOROBO2_CROSSOVEROPERATOR_H

#include "DoubleVectorGenotype.h"
#include <random>
#include <vector>
#include <algorithm>

namespace EA {
    class CrossoverOperator{
    public:
        CrossoverOperator(int nCrossoverPoints);
        DoubleVectorGenotype apply(DoubleVectorGenotype parent1, DoubleVectorGenotype parent2, std::default_random_engine random);
    private:
        int _nCrossOverpoints;
        void Crossover(std::vector<double> &dest, std::vector<double> &source, int crossoverPoint);
    };
}


#endif //ROBOROBO2_CROSSOVEROPERATOR_H
