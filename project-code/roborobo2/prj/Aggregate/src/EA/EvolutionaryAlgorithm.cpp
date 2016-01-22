#include <iostream>
#include "Aggregate/include/EA/EvolutionaryAlgorithm.h"
using namespace EA;

void EvolutionaryAlgorithm::generateInitialPopulation(int populationSize, int nWeights, std::default_random_engine &random)
{
    _genomes.clear();
    for(int i = 0; i < populationSize; i++){
        DoubleVectorGenotype genotype(nWeights, -1.0, 1.0);
        genotype.randomize(random);
        _genomes.push_back(genotype);
        std::cout << genotype.toString() << std::endl;
        std::cout << std::endl;
    }
}
void EvolutionaryAlgorithm::nextGeneration(int nCrossovers, double mutationChance, std::default_random_engine &random)
{
    static int generation;
    generation++;
    CrossoverOperator cross(nCrossovers);
    MutationOperator mutation(mutationChance);
    ReproductionHandler reproductionHandler(random, cross, mutation);
    SigmaScalingSelectionMechanism selection;
    std::cout << "generation: " << generation << std::endl;
    double max = 0.0;
    for(auto &genome:_genomes){
        if(genome.getFitness() > max){
            max = genome.getFitness();
        }
        std::cout << "Fitness: " << genome.getFitness() << std::endl;
    }

    std::cout <<" Best fitness:" << max << std::endl;

    auto matingParents = selection.selectParents(_genomes, _genomes.size(), random);
    std::cout << "parents selected" << std::endl;
    auto offspring = reproductionHandler.produceOffspring(matingParents, random);
    std::cout << "offspring created" << std::endl;
    _genomes = offspring;
}

std::vector<DoubleVectorGenotype>& EvolutionaryAlgorithm::getGenomes()
{
    return _genomes;
}