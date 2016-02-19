#ifndef ROBOROBO2_NETWORKTRANSLATOR_H
#define ROBOROBO2_NETWORKTRANSLATOR_H

#include <neuralnetworks/NeuralNetwork.h>
#include "SelfAssembly/Communication/CommunicationModule.h"
class NetworkTranslator
{
    private:
        std::vector<double> inputs;
        std::vector<double> outputs;
        const int sensorOffset;
        const int portOffset;
        const int messageOffset;
        const int messageOutOffset;
        const int connectionOutOffset;
        const int motorOutOffset;
        Neural::NeuralNetwork* ann;

    public:
        NetworkTranslator(int nSensors, int nPorts);
        void setSensorInput(int sensor, double value);
        void setMessageInput(const RobotMessage& message);
        void setConnectionInput(int connection, bool status);
        double getTranslationOutput();
        double getRotationOutput();
        double getSensorRotationOutput();
        bool getDesiresConnection(int i);
        RobotMessage getMessageOut();
        void step();

        Neural::NeuralNetwork* getAnn()
        {
            return ann;
        }

};
#endif //ROBOROBO2_NETWORKTRANSLATOR_H
