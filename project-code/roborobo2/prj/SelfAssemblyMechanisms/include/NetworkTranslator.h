#ifndef ROBOROBO2_NETWORKTRANSLATOR_H
#define ROBOROBO2_NETWORKTRANSLATOR_H

#include <neuralnetworks/NeuralNetwork.h>
#include "SelfAssembly/Communication/CommunicationModule.h"
class NetworkTranslator
{
    private:
        std::vector<double> inputs;
        std::vector<double> outputs;
        const int predatorSensorOffset;
        const int robotSensorOffset;
        const int environmentOffset;
        const int energyOffset;
        const int portOffset;
        const int messageOffset;
        const int messageOutOffset;
        const int connectionOutOffset;
        const int motorOutOffset;
        Neural::NeuralNetwork* ann;

    public:
        NetworkTranslator(int nSensors, int nPorts);
        void setPredatorInput(int sensor, double value);
        void setRobotInput(int sensor, double value);
        void setEnvironmentInput(int sensor, double value);
        void setEnergyInput(int sensor, double value);
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
