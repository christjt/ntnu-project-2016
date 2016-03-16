#include "SelfAssemblyMechanisms/include/SparseInputNetworkTranslator.h"

SparseInputNetworkTranslator::SparseInputNetworkTranslator(int nSensors, int nPorts):
        NetworkTranslator(4 + nSensors + nPorts*2 + 1, nPorts),
        predatorSensorOffset(0), robotSensorOffset(1), environmentOffset(2),energyOffset(3),
        sensorOffset(energyOffset +1), portOffset(sensorOffset + nSensors), messageOffset(portOffset + nPorts),energyLevelOffset(messageOffset + nPorts)
{
}

void SparseInputNetworkTranslator::setPredatorInput(int sensor, double value)
{
    inputs[sensorOffset + sensor] = value;
    inputs[predatorSensorOffset] = value;
}

void SparseInputNetworkTranslator::setRobotInput(int sensor, double value)
{
    inputs[sensorOffset + sensor] = value;
    inputs[robotSensorOffset] = value;
}

void SparseInputNetworkTranslator::setEnvironmentInput(int sensor, double value)
{
    inputs[sensorOffset + sensor] = value;
    inputs[environmentOffset] = value;
}

void SparseInputNetworkTranslator::setEnergyInput(int sensor, double value)
{
    inputs[sensorOffset + sensor] = value;
    inputs[energyOffset] = value;
}

void SparseInputNetworkTranslator::setMessageInput(const RobotMessage& message)
{
    auto messageContents = message.get();
    for(auto i = 0u; i < messageContents.size(); i++){
        inputs[messageOffset + i] = messageContents[i];
    }
}

void SparseInputNetworkTranslator::setConnectionInput(int connection, bool status)
{
    inputs[portOffset + connection] = status? 1.0 : 0.0;
}

void SparseInputNetworkTranslator::setEnergyLevel(double energyLevel)
{
    inputs[energyLevelOffset] = energyLevel;
}
