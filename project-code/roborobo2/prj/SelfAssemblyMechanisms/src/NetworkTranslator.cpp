#include "SelfAssemblyMechanisms/include/NetworkTranslator.h"
#include "SelfAssemblyMechanisms/include/NetworkFactories/NetworkFactory.h"
NetworkTranslator::NetworkTranslator(int nInputNodes, int nPorts):
        ann(NetworkFactory::createFactory(nInputNodes, nPorts*3 +3)->create()),
        messageOutOffset(0), connectionOutOffset(nPorts),disconnectOutOffset(nPorts*2), motorOutOffset(nPorts*3),
        inputs(nInputNodes, 0.0), outputs(nPorts*3 + 3)

{
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

bool NetworkTranslator::getDesiresDisconnect(int i)
{
    return outputs[disconnectOutOffset +i ] > 0.5;
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
    for(auto i= 0u; i < inputs.size(); i++)
    {
        inputs[i] = 0;
    }

    outputs = ann->readOut();
}