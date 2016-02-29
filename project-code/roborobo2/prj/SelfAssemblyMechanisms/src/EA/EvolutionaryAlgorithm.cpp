#include <iostream>
#include "SelfAssemblyMechanisms/include/EA/EvolutionaryAlgorithm.h"
#include "SelfAssemblyMechanisms/include/EA/Logger.h"

using namespace EA;

std::vector<DoubleVectorGenotype> EvolutionaryAlgorithm::generateInitialPopulation(int populationSize, int nWeights,  std::default_random_engine &random)
{
    std::vector<DoubleVectorGenotype> genomes;
    for(int i = 0; i < populationSize; i++){
        DoubleVectorGenotype genotype(nWeights, -1.0, 1.0);
        genotype.randomize(random);
        genomes.push_back(genotype);
    }
    return genomes;
}
std::vector<DoubleVectorGenotype> EvolutionaryAlgorithm::nextGeneration(std::vector<DoubleVectorGenotype>& genomes,int nCrossovers, double mutationChance, std::default_random_engine &random)
{
    CrossoverOperator cross(nCrossovers);
    MutationOperator mutation(mutationChance);
    ReproductionHandler reproductionHandler(random, cross, mutation);
    SigmaScalingSelectionMechanism selection;
    logger->logGeneration(elites, genomes);
    insertElites(genomes);
    updateElites(genomes);
    auto matingParents = selection.selectParents(genomes, genomes.size(), random);
    auto offspring = reproductionHandler.produceOffspring(matingParents, random);
    return offspring;
}

void EvolutionaryAlgorithm::insertElites(std::vector<DoubleVectorGenotype>& genomes)
{
    std::sort(genomes.begin(), genomes.end(), [](DoubleVectorGenotype a, DoubleVectorGenotype b){
        return a.getFitness() < b.getFitness();
    });

    for(auto i = 0u; i < elites.size(); i++){
        genomes[i] = elites[i];
    }
}

void EvolutionaryAlgorithm::updateElites(std::vector<DoubleVectorGenotype>& genomes)
{
    std::sort(genomes.begin(), genomes.end(), [](DoubleVectorGenotype a, DoubleVectorGenotype b){
        return a.getFitness() < b.getFitness();
    });
    elites.assign(genomes.begin() + (genomes.size() -nElites), genomes.end());
}

void EvolutionaryAlgorithm::setElitism(int nElites)
{
    this->nElites = nElites;
}

void EvolutionaryAlgorithm::setLogger(Logger* logger)
{
    this->logger = logger;
}
const std::vector<DoubleVectorGenotype>& EvolutionaryAlgorithm::getElites() const
{
    return elites;
}