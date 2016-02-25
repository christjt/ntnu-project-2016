//
// Created by christopher on 18.02.16.
//

#include "SelfAssemblyMechanisms/include/NetworkFactories/MLPFactory.h"
#include <vector>

MLPFactory::MLPFactory(int nInputNodes, int nOutputNodes) {
    _nInputNodes = nInputNodes;
    _nOutputNodes = nOutputNodes;
}

Neural::NeuralNetwork* MLPFactory::create(){
    std::vector<double> weights(0, 0.0);
    if(hiddenLayers.size()){
        return new Neural::MLP(weights, _nInputNodes, _nOutputNodes, hiddenLayers, true, true);
    }else{
        return new Neural::MLP(weights, _nInputNodes, _nOutputNodes, true, true);
    }


}