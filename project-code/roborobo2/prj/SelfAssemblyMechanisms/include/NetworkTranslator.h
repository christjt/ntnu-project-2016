#ifndef ROBOROBO2_NETWORKTRANSLATOR_H
#define ROBOROBO2_NETWORKTRANSLATOR_H

#include <neuralnetworks/NeuralNetwork.h>
#include "SelfAssembly/Communication/CommunicationModule.h"
#include <memory>
class NetworkTranslator
{
    private:
        std::shared_ptr<Neural::NeuralNetwork> ann;
        int messageOutOffset;
        int connectionOutOffset;
        int motorOutOffset;

    protected:
        std::vector<double> inputs;
        std::vector<double> outputs;


    public:
        NetworkTranslator(int nInputNodes, int nPorts);
        virtual void setPredatorInput(int sensor, double value) = 0;
        virtual void setRobotInput(int sensor, double value) = 0;
        virtual void setEnvironmentInput(int sensor, double value) = 0;
        virtual void setEnergyInput(int sensor, double value) = 0;
        virtual void setMessageInput(const RobotMessage& message) = 0;
        virtual void setConnectionInput(int connection, bool status) = 0;
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
