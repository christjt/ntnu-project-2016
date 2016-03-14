


#include "neuralnetworks/CTRNN.h"


using namespace Neural;
CTRNN::CTRNN(std::vector<double>& weights, unsigned int nbInputs, unsigned int nbOutputs, std::vector<unsigned int>& nbNeuronsPerLayer, bool activeBias, bool onlyUseBiasForFirstHiddenLayer, double biasValue) :
             MLP(weights, nbInputs, nbOutputs, nbNeuronsPerLayer, activeBias, onlyUseBiasForFirstHiddenLayer, biasValue)

{
    _timeConstants = std::vector<double>(computeNumberOfParameterNodes(), 0.0);
    _gains = std::vector<double>(computeNumberOfParameterNodes(), 0.0);
}

unsigned int CTRNN::computeRequiredNumberOfWeights()
{
    size_t res = MLP::computeRequiredNumberOfWeights();
    for(size_t i = 1; i < _nbNeuronsPerLayer.size(); i++)
        res += _nbNeuronsPerLayer[i] * _nbNeuronsPerLayer[i];
    return res;
}

unsigned int CTRNN::computeNumberOfParameterNodes()
{
    int sum = 0;
    for(unsigned int i = 1; i < _nbNeuronsPerLayer.size(); i++)
    {
        sum += _nbNeuronsPerLayer[i];
    }
    return sum;
}

void CTRNN::initLastOutputs()
{
    _lastOutputs = std::vector< std::vector<double> >(_nbNeuronsPerLayer.size() - 1);
    for(size_t i = 0; i < _lastOutputs.size(); i++) {
        _lastOutputs[i] = std::vector<double>(_nbNeuronsPerLayer[i + 1], 0.0);
    }
}

void CTRNN::step()
{

}

void CTRNN::setNNparameters(std::vector<double> parameters)
{
    auto weightsFirst = parameters.begin();
    auto timeConstantsFirst = weightsFirst + computeRequiredNumberOfWeights();
    auto gainsFirst = timeConstantsFirst + computeNumberOfParameterNodes();
    auto last = gainsFirst + computeNumberOfParameterNodes();

    std::vector<double> newWeights(weightsFirst, timeConstantsFirst);
    setWeigths(newWeights);

    std::vector<double> newTimeConstraints(timeConstantsFirst, gainsFirst);
    setTimeConstants(newTimeConstraints);

    std::vector<double> newGains(gainsFirst, last);
    setGains(newGains);

}

