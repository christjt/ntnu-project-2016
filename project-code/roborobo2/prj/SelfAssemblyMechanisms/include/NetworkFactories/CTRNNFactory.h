#ifndef ROBOROBO2_CTRNNFACTORY_H
#define ROBOROBO2_CTRNNFACTORY_H

#include "NetworkFactory.h"
#include <neuralnetworks/CTRNN.h>
class CTRNNFactory : public NetworkFactory {
public:
    CTRNNFactory(int nInputNodes, int nOutputNodes)
    {
        _nInputNodes = nInputNodes;
        _nOutputNodes = nOutputNodes;
    }
    Neural::NeuralNetwork* create()
    {
        std::vector<double> weights;
        return new Neural::CTRNN(weights, _nInputNodes, _nOutputNodes, hiddenLayers, true, false, 1);

    }
};
#endif //ROBOROBO2_CTRNNFACTORY_H
