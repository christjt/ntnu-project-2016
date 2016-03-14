//
// Created by christopher on 10.03.16.
//

#ifndef ROBOROBO2_CTRNN_H
#define ROBOROBO2_CTRNN_H

#include <neuralnetworks/MLP.h>
#include <string>
#include <vector>

namespace Neural
{
    class CTRNN : public MLP{


        private:
            std::vector<double> _gains;
            std::vector<double> _timeConstants;

            std::vector< std::vector<double> > _lastOutputs;
            std::vector< std::vector<double> > _internalCharge;

            void initLastOutputsAndCharge();
            unsigned int computeRequiredNumberOfWeights();
            unsigned int computeNumberOfParameterNodes();
            double activationFunction(double internalState, double gain);


        public:
            CTRNN(std::vector<double>& weights, unsigned int nbInputs, unsigned int nbOutputs, std::vector<unsigned int>& nbNeuronsPerLayer, bool activeBias = false, bool onlyUseBiasForFirstHiddenLayer = false, double biasValue = 1.0);
            std::vector< std::vector<double> > const& getLastOutputs() const;
            void step();
            static std::string getNNTypeName() { return "CTRNN"; };

            int getNumberOfGains()
            {
                return _gains.size();
            };

            int getNumberOfTimeConstants()
            {
                return _timeConstants.size();
            };

            void setTimeConstants(std::vector<double>& timeConstraints)
            {
                _timeConstants = timeConstraints;
            };

            void setGains(std::vector<double>& gains)
            {
                _gains = gains;
            };

    };
}



#endif //ROBOROBO2_CTRNN_H
