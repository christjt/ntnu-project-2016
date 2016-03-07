//
// Created by eirikjak on 11.11.15.
//

#ifndef ROBOROBO2_EVOLUTIONARYALGORITHM_H
#define ROBOROBO2_EVOLUTIONARYALGORITHM_H

#include <vector>
#include "DoubleVectorGenotype.h"
#include "CrossoverOperator.h"
#include "ReproductionHandler.h"
#include "SigmaScalingSelectionMechanism.h"
#include <random>
#include <memory>
namespace EA
{
    class Logger;
    class EvolutionaryAlgorithm
    {
    private:
        std::vector<DoubleVectorGenotype> elites;
        int nElites;
        void insertElites(std::vector<DoubleVectorGenotype>& genomes);
        void updateElites(std::vector<DoubleVectorGenotype>& genomes);
        Logger* logger;
    public:
        void setElitism(int nElites);
        void setLogger(Logger* logger);
        std::vector<DoubleVectorGenotype> generateInitialPopulation(int populationSize, int nWeights, std::default_random_engine &random);
        std::vector<DoubleVectorGenotype> nextGeneration(std::vector<DoubleVectorGenotype>& genomes, int nCrossovers, double mutationChance, std::default_random_engine &random);
        const std::vector<DoubleVectorGenotype>& getElites() const;
    };
}

#endif //ROBOROBO2_EVOLUTIONARYALGORITHM_H
