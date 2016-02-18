#ifndef ROBOROBO2_NETWORKFACTORY_H
#define ROBOROBO2_NETWORKFACTORY_H

#include <neuralnetworks/NeuralNetwork.h>

class NetworkFactory
{
    protected:
        int _nInputNodes;
        int _nOutputNodes;

    public:
        virtual Neural::NeuralNetwork* create() = 0;

};


#endif //ROBOROBO2_NETWORKFACTORY_H
