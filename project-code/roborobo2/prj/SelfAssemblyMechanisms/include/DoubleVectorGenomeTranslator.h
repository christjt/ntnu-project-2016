#ifndef ROBOROBO2_DOUBLEVECTORGENOMETRANSLATOR_H
#define ROBOROBO2_DOUBLEVECTORGENOMETRANSLATOR_H

#include "GenomeTranslator.h"
#include <neuralnetworks/NeuralNetwork.h>
class DoubleVectorGenotypeTranslator:public GenomeTranslator<std::vector<double>>
{
    public:
        DoubleVectorGenotypeTranslator(Neural::NeuralNetwork* ann):GenomeTranslator(ann){}
        void translateToWeights(std::vector<double>& genome)
        {
            ann->setWeigths(genome);
        };
};
#endif //ROBOROBO2_DOUBLEVECTORGENOMETRANSLATOR_H
