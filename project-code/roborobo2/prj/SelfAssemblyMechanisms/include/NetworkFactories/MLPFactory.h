//
// Created by christopher on 18.02.16.
//

#ifndef ROBOROBO2_MPLFACTORY_H
#define ROBOROBO2_MPLFACTORY_H

#include <neuralnetworks/MLP.h>
#include "NetworkFactory.h"
class MLPFactory : public NetworkFactory {
    public:
        MLPFactory(int nInputNodes, int nOutputNodes);
        Neural::NeuralNetwork* create();
};


#endif //ROBOROBO2_MPLFACTORY_H
