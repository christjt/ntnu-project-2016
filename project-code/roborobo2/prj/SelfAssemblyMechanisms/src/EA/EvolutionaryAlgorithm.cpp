#include <iostream>
#include "SelfAssemblyMechanisms/include/EA/EvolutionaryAlgorithm.h"
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
    static int generation;
    generation++;
    CrossoverOperator cross(nCrossovers);
    MutationOperator mutation(mutationChance);
    ReproductionHandler reproductionHandler(random, cross, mutation);
    SigmaScalingSelectionMechanism selection;
    std::cout << "generation: " << generation << std::endl;

    insertElites(genomes);
    updateElites(genomes);

    auto matingParents = selection.selectParents(genomes, genomes.size(), random);
    std::cout << "parents selected " << std::endl;
    auto offspring = reproductionHandler.produceOffspring(matingParents, random);
    std::cout << "offspring created" << std::endl;
    return offspring;
}

void EvolutionaryAlgorithm::insertElites(std::vector<DoubleVectorGenotype>& genomes)
{
    std::sort(genomes.begin(), genomes.end(), [](DoubleVectorGenotype a, DoubleVectorGenotype b){
        return a.getFitness() < b.getFitness();
    });

    for(auto& genome: genomes){
        std::cout << genome.getFitness() << std::endl;
    }

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
    std::cout << "elites" << std::endl;
    for(auto& genome: elites){
        std::cout << genome.getFitness() << std::endl;
    }
}

void EvolutionaryAlgorithm::setElitism(int nElites)
{
    this->nElites = nElites;
}

std::vector<DoubleVectorGenotype>& EvolutionaryAlgorithm::getElites()
{
    return elites;
}