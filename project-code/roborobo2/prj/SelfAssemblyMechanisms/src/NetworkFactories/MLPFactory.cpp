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

    std::vector<double> weights(_nInputNodes * _nOutputNodes, 0.0);
    return new Neural::MLP(weights, _nInputNodes, _nOutputNodes, false, false, 0);

}