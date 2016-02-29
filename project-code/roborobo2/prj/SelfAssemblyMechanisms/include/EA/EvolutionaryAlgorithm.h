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
        std::vector<DoubleVectorGenotype> elites;
        int nElites;
        void insertElites(std::vector<DoubleVectorGenotype>& genomes);
        void updateElites(std::vector<DoubleVectorGenotype>& genomes);
    public:
        void setElitism(int nElites);
        std::vector<DoubleVectorGenotype> generateInitialPopulation(int populationSize, int nWeights, std::default_random_engine &random);
        std::vector<DoubleVectorGenotype> nextGeneration(std::vector<DoubleVectorGenotype>& genomes, int nCrossovers, double mutationChance, std::default_random_engine &random);
        std::vector<DoubleVectorGenotype>& getElites();
    };
}

#endif //ROBOROBO2_EVOLUTIONARYALGORITHM_H
