#include <iostream>
#include "SelfAssemblyMechanisms/include/EA/EvolutionaryAlgorithm.h"
#include "SelfAssemblyMechanisms/include/EA/Logger.h"
#include "SelfAssemblyMechanisms/include/EA/IncrementalMutationOperator.h"
#include "SelfAssemblyMechanisms/include/EA/RerollMutationOperator.h"
#include "SelfAssemblyMechanisms/include/SelfAssemblyMechanismsSharedData.h"

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


    std::sort(genomes.begin(), genomes.end(), [](DoubleVectorGenotype a, DoubleVectorGenotype b){
        return a.getFitness() < b.getFitness();
    });
    MutationOperator* mutation;
    if(computeGenomeVariation(genomes) < explorationThreshold){
        mutation = new RerollMutationOperator(SelfAssemblyMechanismsSharedData::gExplorationMutationRate); //Change this line to change mutation operator
    }else{
        mutation = new IncrementalMutationOperator(mutationChance, SelfAssemblyMechanismsSharedData::gMutationStep); //Change this line to change mutation operator
    }
    CrossoverOperator cross(nCrossovers);
    ReproductionHandler reproductionHandler(random, cross, mutation);

    logger->logGeneration(elites, genomes);
    insertElites(genomes);
    updateElites(genomes);
    auto matingParents = selectionMechanism->selectParents(genomes, genomes.size(), random);
    auto offspring = reproductionHandler.produceOffspring(matingParents, random);
    return offspring;
}

void EvolutionaryAlgorithm::insertElites(std::vector<DoubleVectorGenotype>& genomes)
{

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


double EvolutionaryAlgorithm::computeGenomeVariation(std::vector<DoubleVectorGenotype>& genomes)
{
    auto& best = genomes[genomes.size()-1];
    double difference = 0.0;
    for(auto& genome: genomes)
    {
        for(auto i = 0u; i < genome.getVector().size(); i++)
        {
            difference += fabs(best.getVector()[i] - genome.getVector()[i]);
        }
    }
    return (difference/genomes.size())/best.getVector().size();
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