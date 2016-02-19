#ifndef ROBOROBO2_DOUBLEVECTORGENOMETRANSLATOR_H
#define ROBOROBO2_DOUBLEVECTORGENOMETRANSLATOR_H

#include "GenomeTranslator.h"
#include <neuralnetworks/NeuralNetwork.h>
#include "EA/DoubleVectorGenotype.h"
class DoubleVectorGenotypeTranslator:public GenomeTranslator<EA::DoubleVectorGenotype>
{
    public:
        DoubleVectorGenotypeTranslator(Neural::NeuralNetwork* ann):GenomeTranslator(ann){}
        void translateToWeights(EA::DoubleVectorGenotype& genome)
        {
            ann->setWeigths(genome.getVector());
        };
};
#endif //ROBOROBO2_DOUBLEVECTORGENOMETRANSLATOR_H
