//
// Created by eirikjak on 11.11.15.
//

#ifndef ROBOROBO2_EVOLUTIONARYALGORITHM_H
#define ROBOROBO2_EVOLUTIONARYALGORITHM_H

#include <vector>
#include "DoubleVectorGenotype.h"
#include "CrossoverOperator.h"
#include "MutationOperator.h"
#include "ReproductionHandler.h"
#include "SigmaScalingSelectionMechanism.h"
#include <random>
namespace EA
{
    class EvolutionaryAlgorithm
    {
    private:
        std::vector<DoubleVectorGenotype> _genomes;
        std::vector<DoubleVectorGenotype> elites;
        int nElites;
        void insertElites();
        void updateElites();
    public:
        void setElitism(int nElites);
        std::vector<DoubleVectorGenotype>& getGenomes();
        void generateInitialPopulation(int populationSize, int nWeights, std::default_random_engine &random);
        void nextGeneration(int nCrossovers, double mutationChance, std::default_random_engine &random);
    };
}

#endif //ROBOROBO2_EVOLUTIONARYALGORITHM_H
