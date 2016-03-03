#include "SelfAssemblyMechanisms/include/SparseInputNetworkTranslator.h"

SparseInputNetworkTranslator::SparseInputNetworkTranslator(int nSensors, int nPorts):
        NetworkTranslator(nSensors +4 + nPorts*2, nPorts),
        predatorSensorOffset(0), robotSensorOffset(1), environmentOffset(2),energyOffset(3),sensorOffset(nSensors), portOffset(nSensors+4), messageOffset(nSensors +4 + nPorts)
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
