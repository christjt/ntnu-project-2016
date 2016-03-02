#ifndef ROBOROBO2_NETWORKTRANSLATOR_H
#define ROBOROBO2_NETWORKTRANSLATOR_H

#include <neuralnetworks/NeuralNetwork.h>
#include "SelfAssembly/Communication/CommunicationModule.h"
#include <memory>
class NetworkTranslator
{
    private:
        std::shared_ptr<Neural::NeuralNetwork> ann;
        std::vector<double> inputs;
        std::vector<double> outputs;
        int predatorSensorOffset;
        int robotSensorOffset;
        int environmentOffset;
        int energyOffset;
        int portOffset;
        int messageOffset;
        int messageOutOffset;
        int connectionOutOffset;
        int motorOutOffset;

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

        std::shared_ptr<Neural::NeuralNetwork> getAnn()
        {
            return ann;
        }

};
#endif //ROBOROBO2_NETWORKTRANSLATOR_H
