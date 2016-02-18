#ifndef ROBOROBO2_GENOMETRANSLATOR_H
#define ROBOROBO2_GENOMETRANSLATOR_H

#include <neuralnetworks/NeuralNetwork.h>

template <class TGenome>
class GenomeTranslator
{
    private:
        double numberOfWeights;
    protected:
        Neural::NeuralNetwork* ann;

    public:
        GenomeTranslator(Neural::NeuralNetwork* _ann):ann(_ann), numberOfWeights(_ann->getRequiredNumberOfWeights()){}
        virtual void translateToWeights(TGenome& genome) = 0;
        double getRequiredNumberOfWeights()
        {
            return numberOfWeights;
        }
};
#endif //ROBOROBO2_GENOMETRANSLATOR_H
