#ifndef ROBOROBO2_DENSEINPUTNETWORKTRANSLATOR_H
#define ROBOROBO2_DENSEINPUTNETWORKTRANSLATOR_H

#include <neuralnetworks/NeuralNetwork.h>
#include "SelfAssembly/Communication/CommunicationModule.h"
#include <memory>
#include "NetworkTranslator.h"
class DenseInputNetworkTranslator: public NetworkTranslator
{
    private:
        int predatorSensorOffset;
        int robotSensorOffset;
        int environmentOffset;
        int energyOffset;
        int portOffset;
        int messageOffset;
        int energyLevelOffset;

    public:
        DenseInputNetworkTranslator(int nSensors, int nPorts);
        void setPredatorInput(int sensor, double value);
        void setRobotInput(int sensor, double value);
        void setEnvironmentInput(int sensor, double value);
        void setEnergyInput(int sensor, double value);
        void setMessageInput(const RobotMessage& message);
        void setConnectionInput(int connection, bool status);
        void setEnergyLevel(double energyLevel);


};
#endif //ROBOROBO2_DENSEINPUTNETWORKTRANSLATOR_H
