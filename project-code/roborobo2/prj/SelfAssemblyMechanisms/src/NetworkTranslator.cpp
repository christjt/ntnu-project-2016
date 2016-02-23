#include "SelfAssemblyMechanisms/include/NetworkTranslator.h"
#include "SelfAssemblyMechanisms/include/NetworkFactories/NetworkFactory.h"
NetworkTranslator::NetworkTranslator(int nSensors, int nPorts):
        inputs(nSensors + nPorts*2, 0.0), outputs(nPorts*2 +3), sensorOffset(0), portOffset(nSensors), messageOffset(nSensors + nPorts),
        messageOutOffset(0), connectionOutOffset(nPorts), motorOutOffset(nPorts*2)
{
    this->ann = NetworkFactory::createFactory(nSensors + nPorts*2, nPorts*2 +3)->create();
}

void NetworkTranslator::setSensorInput(int sensor, double value)
{
    inputs[sensorOffset + sensor] = value;
}

void NetworkTranslator::setMessageInput(const RobotMessage& message)
{
    auto messageContents = message.get();
    for(auto i = 0u; i < messageContents.size(); i++){
        inputs[messageOffset + i] = messageContents[i];
    }
}

void NetworkTranslator::setConnectionInput(int connection, bool status)
{
    inputs[portOffset + connection] = status? 1.0 : 0.0;
}

double NetworkTranslator::getTranslationOutput()
{
    return outputs[motorOutOffset];
}

double NetworkTranslator::getRotationOutput()
{
    return outputs[motorOutOffset + 1];
}

double NetworkTranslator::getSensorRotationOutput()
{
    return outputs[motorOutOffset + 2];
}

bool NetworkTranslator::getDesiresConnection(int i)
{
    return outputs[connectionOutOffset + i] > 0.5;
}

RobotMessage NetworkTranslator::getMessageOut()
{
    std::vector<double> message(outputs.begin() + messageOutOffset, outputs.begin()+connectionOutOffset);
    return RobotMessage(message);
}

void NetworkTranslator::step()
{
    ann->setInputs(inputs);
    ann->step();
    inputs.clear();
    outputs = ann->readOut();

}