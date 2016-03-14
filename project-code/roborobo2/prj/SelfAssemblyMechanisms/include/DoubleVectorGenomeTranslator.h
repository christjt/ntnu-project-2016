#ifndef ROBOROBO2_DOUBLEVECTORGENOMETRANSLATOR_H
#define ROBOROBO2_DOUBLEVECTORGENOMETRANSLATOR_H

#include "GenomeTranslator.h"
#include <neuralnetworks/NeuralNetwork.h>
#include "EA/DoubleVectorGenotype.h"
class DoubleVectorGenotypeTranslator:public GenomeTranslator<EA::DoubleVectorGenotype>
{
    public:
        DoubleVectorGenotypeTranslator(std::shared_ptr<Neural::NeuralNetwork> ann):GenomeTranslator(ann){}
        virtual void translateToWeights(EA::DoubleVectorGenotype& genome)
        {
            auto genomeCopy = genome.getVector();
            ann->setWeigths(genomeCopy);
        };
};
#endif //ROBOROBO2_DOUBLEVECTORGENOMETRANSLATOR_H
