#include "SelfAssemblyMechanisms/include/NetworkFactories/NetworkFactory.h"
#include "SelfAssemblyMechanisms/include/NetworkFactories/MLPFactory.h"
ANNType NetworkFactory::factoryType = ANNType::MLP;
std::shared_ptr<NetworkFactory> NetworkFactory::createFactory(int nInputNodes, int nOutputNodes)
{
    switch(NetworkFactory::factoryType){
        case ANNType::MLP: return std::shared_ptr<NetworkFactory>(new MLPFactory(nInputNodes, nOutputNodes));
    }
    throw "Invalid factory type";

}