#ifndef ROBOROBO2_CTRNGENOMETRANSLATOR_H
#define ROBOROBO2_CTRNGENOMETRANSLATOR_H
#include <neuralnetworks/NeuralNetwork.h>
#include "DoubleVectorGenomeTranslator.h"
#include <neuralnetworks/CTRNN.h>
#include "SelfAssemblyMechanismsUtilities.h"

class CTRNNGenomeTranslator : public DoubleVectorGenotypeTranslator
{
public:
    CTRNNGenomeTranslator(std::shared_ptr<Neural::NeuralNetwork> ann): DoubleVectorGenotypeTranslator(ann){}
    void translateToWeights(EA::DoubleVectorGenotype& genome)
    {
        Neural::CTRNN* network = (Neural::CTRNN*)ann.get();
        auto parameters = genome.getVector();
        auto weightsFirst = parameters.begin();
        auto timeConstantsFirst = weightsFirst + network->getRequiredNumberOfWeights();
        auto gainsFirst = timeConstantsFirst + network->getNumberOfTimeConstants();
        auto last = gainsFirst + network->getNumberOfGains();

        std::vector<double> newWeights(weightsFirst, timeConstantsFirst);
        network->setWeigths(newWeights);


        std::vector<double> newTimeConstraints(timeConstantsFirst, gainsFirst);
        for(auto i = 0u; i < newTimeConstraints.size(); i++)
        {
            newTimeConstraints[i] = SelfAssemblyMechanismsUtilities::normalizeDouble(newTimeConstraints[i], -1.0, 1.0, 1.0, 2.0);

        }

        network->setTimeConstants(newTimeConstraints);
        std::vector<double> newGains(gainsFirst, last);
        for(auto i = 0u; i < newGains.size(); i++)
        {
            newGains[i] = SelfAssemblyMechanismsUtilities::normalizeDouble(newGains[i], -1.0, 1.0, 1.0, 5.0);

        }
        network->setGains(newGains);
    };


    int getRequiredNumberOfWeights()
    {
        Neural::CTRNN* network = (Neural::CTRNN*)ann.get();
        return DoubleVectorGenotypeTranslator::getRequiredNumberOfWeights() + network->getNumberOfGains() + network->getNumberOfTimeConstants();
    }
};
#endif //ROBOROBO2_CTRNGENOMETRANSLATOR_H
