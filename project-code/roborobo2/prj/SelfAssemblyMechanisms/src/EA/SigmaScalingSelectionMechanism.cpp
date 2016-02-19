#include "SelfAssemblyMechanisms/include/EA/SigmaScalingSelectionMechanism.h"
#include "SelfAssemblyMechanisms/include/EA/RouletteWheel.h"
#include <algorithm>
#include <iostream>

using namespace EA;
std::vector<DoubleVectorGenotype> SigmaScalingSelectionMechanism::selectParents(std::vector<DoubleVectorGenotype> &adultPool, int selectCount, std::default_random_engine &random) {
    double average = std::accumulate(adultPool.begin(), adultPool.end(), 0.0, [](double sum, DoubleVectorGenotype &genotype)
    { return sum + genotype.getFitness();})/adultPool.size();
    double variance = std::accumulate(adultPool.begin(), adultPool.end(), 0.0 ,[average](double sum, DoubleVectorGenotype &genotype)
    { return sum + (genotype.getFitness() - average)*(genotype.getFitness() - average);})/adultPool.size();
    double  standardDeviation =  std::max(sqrt(variance), 0.0001);

    for(DoubleVectorGenotype &genotype: adultPool){
        genotype.setScaledFitness(1.0 + (genotype.getFitness() - average)/(2.0*standardDeviation));
    }
    RouletteWheel roulette(random, adultPool);
    return roulette.selectAdults(selectCount);
}
