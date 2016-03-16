#include "SelfAssemblyMechanisms/include/DenseInputNetworkTranslator.h"

DenseInputNetworkTranslator::DenseInputNetworkTranslator(int nSensors, int nPorts):
        NetworkTranslator(4*nSensors + nPorts*2 +1, nPorts),
        predatorSensorOffset(0), robotSensorOffset(nSensors), environmentOffset(nSensors*2),energyOffset(nSensors*3),
        portOffset(nSensors*4), messageOffset(nSensors*4 + nPorts), energyLevelOffset(nSensors*4 + nPorts*2 +1)
{
}

void DenseInputNetworkTranslator::setPredatorInput(int sensor, double value)
{
    inputs[predatorSensorOffset + sensor] = value;
}

void DenseInputNetworkTranslator::setRobotInput(int sensor, double value)
{
    inputs[robotSensorOffset + sensor] = value;
}

void DenseInputNetworkTranslator::setEnvironmentInput(int sensor, double value)
{
    inputs[environmentOffset + sensor] = value;
}

void DenseInputNetworkTranslator::setEnergyInput(int sensor, double value)
{
    inputs[energyOffset + sensor] = value;
}

void DenseInputNetworkTranslator::setMessageInput(const RobotMessage& message)
{
    auto messageContents = message.get();
    for(auto i = 0u; i < messageContents.size(); i++){
        inputs[messageOffset + i] = messageContents[i];
    }
}

void DenseInputNetworkTranslator::setConnectionInput(int connection, bool status)
{
    inputs[portOffset + connection] = status? 1.0 : 0.0;
}

void DenseInputNetworkTranslator::setEnergyLevel(double energyLevel)
{
    inputs[energyLevelOffset] = energyLevel;
}
