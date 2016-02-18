#ifndef ROBOROBO2_NETWORKTRANSLATOR_H
#define ROBOROBO2_NETWORKTRANSLATOR_H

#include <neuralnetworks/NeuralNetwork.h>
#include "SelfAssembly/Communication/CommunicationModule.h"
class NetworkTranslator
{
    public:
        NetworkTranslator(int nSensors, int nPorts);
        void setSensorInput(int sensor, double value);
        void setMessageInput(const RobotMessage& message);
        void setConnectionInput(int connection, bool status);
        double getTranslationOutput();
        double getRotationOutput();
        double getSensorRotationOutput();
        bool getDesiresConnection(int i);

};
#endif //ROBOROBO2_NETWORKTRANSLATOR_H
