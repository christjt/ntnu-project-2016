#ifndef ROBOROBO2_GENOMETRANSLATOR_H
#define ROBOROBO2_GENOMETRANSLATOR_H

#include <neuralnetworks/NeuralNetwork.h>
#include <memory>

template <class TGenome>
class GenomeTranslator
{
    private:
        double numberOfWeights;
    protected:
        std::shared_ptr<Neural::NeuralNetwork> ann;

    public:
        GenomeTranslator(std::shared_ptr<Neural::NeuralNetwork> _ann):numberOfWeights(_ann->getRequiredNumberOfWeights()),ann(_ann){}
        virtual void translateToWeights(TGenome& genome) = 0;
        int getRequiredNumberOfWeights()
        {
            return numberOfWeights;
        }
};
#endif //ROBOROBO2_GENOMETRANSLATOR_H
