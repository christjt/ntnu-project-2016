#ifndef ROBOROBO2_NETWORKFACTORY_H
#define ROBOROBO2_NETWORKFACTORY_H

#include <neuralnetworks/NeuralNetwork.h>
#include <memory>
enum class ANNType{MLP, Elman, CTRNN};
class NetworkFactory
{
    private:
    protected:
        int _nInputNodes;
        int _nOutputNodes;

    public:
        static ANNType factoryType;
        virtual Neural::NeuralNetwork* create() = 0;
        static std::shared_ptr<NetworkFactory> createFactory(int nInputNodes, int nOutputNodes);
        static std::vector<unsigned > hiddenLayers;
};


#endif //ROBOROBO2_NETWORKFACTORY_H
