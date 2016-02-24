#include <iostream>
#include "SelfAssemblyMechanisms/include/EA/EvolutionaryAlgorithm.h"
using namespace EA;

void EvolutionaryAlgorithm::generateInitialPopulation(int populationSize, int nWeights, int nElites, std::default_random_engine &random)
{
    this->nElites = nElites;
    _genomes.clear();
    for(int i = 0; i < populationSize; i++){
        DoubleVectorGenotype genotype(nWeights, -1.0, 1.0);
        genotype.randomize(random);
        _genomes.push_back(genotype);
    }
}
void EvolutionaryAlgorithm::nextGeneration(int nCrossovers, double mutationChance, std::default_random_engine &random)
{
    static int generation;
    static DoubleVectorGenotype elite = _genomes[0];
    generation++;
    CrossoverOperator cross(nCrossovers);
    MutationOperator mutation(mutationChance);
    ReproductionHandler reproductionHandler(random, cross, mutation);
    SigmaScalingSelectionMechanism selection;
    std::cout << "generation: " << generation << std::endl;
    insertElites();
    updateElites();

    auto matingParents = selection.selectParents(_genomes, _genomes.size(), random);
    std::cout << "parents selected " << std::endl;
    auto offspring = reproductionHandler.produceOffspring(matingParents, random);
    std::cout << "offspring created" << std::endl;
    _genomes = offspring;
}
void EvolutionaryAlgorithm::insertElites()
{
    std::sort(_genomes.begin(), _genomes.end(), [](DoubleVectorGenotype a, DoubleVectorGenotype b){
        return a.getFitness() < b.getFitness();
    });

    for(auto i = 0u; i < elites.size(); i++){
        _genomes[i] = elites[i];
    }
}
void EvolutionaryAlgorithm::updateElites()
{
    std::sort(_genomes.begin(), _genomes.end(), [](DoubleVectorGenotype a, DoubleVectorGenotype b){
        return a.getFitness() < b.getFitness();
    });

    for(auto& genome: _genomes){
        std::cout << genome.getFitness() << std::endl;
    }

    elites.assign(_genomes.begin() + (_genomes.size() -nElites), _genomes.end());
    std::cout << "elites" << std::endl;
    for(auto& genome: elites){
        std::cout << genome.getFitness() << std::endl;
    }
}
std::vector<DoubleVectorGenotype>& EvolutionaryAlgorithm::getGenomes()
{
    return _genomes;
}