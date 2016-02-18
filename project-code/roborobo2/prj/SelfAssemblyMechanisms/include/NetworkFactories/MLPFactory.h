//
// Created by christopher on 18.02.16.
//

#ifndef ROBOROBO2_MPLFACTORY_H
#define ROBOROBO2_MPLFACTORY_H

#include "NetworkFactory.h"
#include <neuralnetworks/MLP.h>

class MLPFactory : NetworkFactory {
    public:
        MLPFactory(int nInputNodes, int nOutputNodes);
        Neural::NeuralNetwork* create();
};


#endif //ROBOROBO2_MPLFACTORY_H
