//
// Created by christopher on 18.02.16.
//

#include "SelfAssemblyMechanisms/include/NetworkFactories/MLPFactory.h"
#include <vector>

MLPFactory::MLPFactory(int nInputNodes, int nOutputNodes) {
    _nInputNodes = nInputNodes;
    _nOutputNodes = nOutputNodes;
    hiddenLayers[0] = nInputNodes;
    hiddenLayers[hiddenLayers.size()-1] = nOutputNodes;
}

Neural::NeuralNetwork* MLPFactory::create(){

    int nWeights = 0;
    if(hiddenLayers.size() > 2)
    {
        for(auto i = 0u; i < hiddenLayers.size()-1; i++){
            nWeights += hiddenLayers[i]*hiddenLayers[i+1];
        }
    }else{
        nWeights = _nInputNodes * _nOutputNodes;
    }
    std::vector<double> weights(nWeights, 0.0);
    std::cout << nWeights << std::endl;
    if(hiddenLayers.size() > 2){
        return new Neural::MLP(weights, _nInputNodes, _nOutputNodes, hiddenLayers);
    }else{
        return new Neural::MLP(weights, _nInputNodes, _nOutputNodes, true, true, 0.5);
    }


}