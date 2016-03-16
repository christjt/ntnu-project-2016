//
// Created by eirikjak on 03.03.16.
//

#ifndef ROBOROBO2_SPARSEINPUTNETWORKTRANSLATOR_H
#define ROBOROBO2_SPARSEINPUTNETWORKTRANSLATOR_H
#include "NetworkTranslator.h"
class SparseInputNetworkTranslator: public NetworkTranslator
{
    private:
        int predatorSensorOffset;
        int robotSensorOffset;
        int environmentOffset;
        int energyOffset;
        int sensorOffset;
        int portOffset;
        int messageOffset;
        int energyLevelOffset;

    public:
        SparseInputNetworkTranslator(int nSensors, int nPorts);
        void setPredatorInput(int sensor, double value);
        void setRobotInput(int sensor, double value);
        void setEnvironmentInput(int sensor, double value);
        void setEnergyInput(int sensor, double value);
        void setMessageInput(const RobotMessage& message);
        void setConnectionInput(int connection, bool status);
        void setEnergyLevel(double energyLevel);



};
#endif //ROBOROBO2_SPARSEINPUTNETWORKTRANSLATOR_H
