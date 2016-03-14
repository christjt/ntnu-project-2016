


#include "neuralnetworks/CTRNN.h"
#include <math.h>
#include <sstream>


using namespace Neural;
CTRNN::CTRNN(std::vector<double>& weights, unsigned int nbInputs, unsigned int nbOutputs, std::vector<unsigned int>& nbNeuronsPerLayer, bool activeBias, bool onlyUseBiasForFirstHiddenLayer, double biasValue) :
             MLP(weights, nbInputs, nbOutputs, nbNeuronsPerLayer, activeBias, onlyUseBiasForFirstHiddenLayer, biasValue)

{
    initLastOutputsAndCharge();
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

void CTRNN::initLastOutputsAndCharge()
{
    _lastOutputs = std::vector< std::vector<double> >(_nbNeuronsPerLayer.size() - 1);
    _internalCharge = std::vector< std::vector<double> >(_nbNeuronsPerLayer.size() - 1);
    for(size_t i = 0; i < _lastOutputs.size(); i++) {
        _lastOutputs[i] = std::vector<double>(_nbNeuronsPerLayer[i + 1], 0.0);
        _internalCharge[i] = std::vector<double>(_nbNeuronsPerLayer[i + 1], 0.0);
    }
}

void CTRNN::step()
{
    std::vector<double> lastLayerOut = _inputs;
    int weightIndex = 0;
    int timeConstantIndex = 0;
    int gainIndex = 0;
    std::vector<double> s_i;
    std::vector<double> dy_dt;

    // Verify that the number of layers is correct
    if(_nbNeuronsPerLayer.size() < 2)
        throw NeuralNetworkException("CTRNN must have at least 2 layers : input and output");
    if(_nbNeuronsPerLayer[0] != _inputs.size())
        throw NeuralNetworkException("nbNeuronsPerLayer has an incorrect number of inputs neurons (first layer)");
    if(_nbNeuronsPerLayer[_nbNeuronsPerLayer.size() - 1] == 0)
        throw NeuralNetworkException("nbNeuronsPerLayer has an incorrect number of output neurons (output layer)");

    unsigned int nbBiais = 0;
    if(_activeBiais)
        nbBiais = 1;


    for(unsigned int k = 0; k < _nbNeuronsPerLayer.size() - 1; k++) {


        // Verify that the number of weights is correct
        unsigned int const remainingWeights = _weights.size() - weightIndex;
        if(remainingWeights < lastLayerOut.size() + nbBiais) {
            std::stringstream ss;
            ss << "remainingWeights = " << remainingWeights <<
            " but at least " << lastLayerOut.size() + nbBiais << " weights are needed...";
            throw NeuralNetworkException(ss.str());
        }

        unsigned int nbOutputs = _nbNeuronsPerLayer[k + 1];

        // Do Stuffs ! (base neural computation)
        s_i = std::vector<double>(nbOutputs, 0.0);
        dy_dt = std::vector<double>(nbOutputs, 0.0);
        for(unsigned int i = 0; i < lastLayerOut.size(); i++) {
            for(unsigned int j = 0; j < nbOutputs; j++) {
                s_i[j] += lastLayerOut[i] * _weights[weightIndex++];
            }
        }

        // Do computation of the biais
        if(_activeBiais && (k==0 || !_onlyUseBiaisForFirstHiddenLayer))
            for(unsigned int j = 0; j < nbOutputs; j++)
                s_i[j] += _weights[weightIndex++] * _biaisValue;

        // Do computation using last outputs of this layer
        for(unsigned int i = 0; i < _lastOutputs[k].size(); i++) {
            for (unsigned int j = 0; j < nbOutputs; j++) {
                s_i[j] += _lastOutputs[k][i] * _weights[weightIndex++];
            }
        }


        //Compute change in internal state and apply
        for(unsigned int j = 0; j < nbOutputs; j++) {
            dy_dt[j] += (1/_timeConstants[timeConstantIndex++]) * (-_internalCharge[k][j] + s_i[j]);
            _internalCharge[k][j] = _internalCharge[k][j] + dy_dt[j];
        }

        // Activation Function
        for(unsigned int i = 0; i < nbOutputs; i++)
            s_i[i] = 1/(1 + exp(-_gains[gainIndex++] * _internalCharge[k][i]));

        lastLayerOut = s_i;

        _lastOutputs[k] = s_i;

    }

    _outputs = lastLayerOut;
}

