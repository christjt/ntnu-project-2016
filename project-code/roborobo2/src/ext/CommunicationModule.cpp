#include "SelfAssembly/Communication/CommunicationModule.h"
#include "SelfAssembly/WorldModels/GroupRobotWorldModel.h"
#include <algorithm>

CommunicationModule::CommunicationModule(GroupRobotWorldModel* owner){
    this->owner = owner;
}

RobotMessage CommunicationModule::read(int messageSize){
    auto neighbors = owner->getConnectionMechanism().getConnections();
    RobotMessage initial = RobotMessage(std::vector<double >(messageSize, 0.0));
    for(auto neighbor: neighbors){
        initial = initial + neighbor.first->getCommunicationModule().outgoingMessage;
    }
    return initial;
}

void CommunicationModule::broadcast(RobotMessage message){
    outgoingMessage = message;
}
