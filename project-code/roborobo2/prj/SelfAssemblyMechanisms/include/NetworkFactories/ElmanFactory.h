#ifndef ROBOROBO2_ELMANFACTORY_H
#define ROBOROBO2_ELMANFACTORY_H

#include <neuralnetworks/Elman.h>
#include "NetworkFactory.h"

class ElmanFactory : public NetworkFactory {
public:
    ElmanFactory(int nInputNodes, int nOutputNodes)
    {
        _nInputNodes = nInputNodes;
        _nOutputNodes = nOutputNodes;
    }
    Neural::NeuralNetwork* create()
    {
        std::vector<double> weights;
        if(hiddenLayers.size()){
            return new Neural::Elman(weights, _nInputNodes, _nOutputNodes, hiddenLayers, true, false);
        }else{
            return new Neural::Elman(weights, _nInputNodes, _nOutputNodes, true, false);
        }
    }
};
#endif //ROBOROBO2_ELMANFACTORY_H
