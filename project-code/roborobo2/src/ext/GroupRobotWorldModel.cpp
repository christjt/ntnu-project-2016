#include "SelfAssembly/WorldModels/GroupRobotWorldModel.h"
std::vector<std::shared_ptr<ConnectionPort>> make_ports(){
    std::vector<std::shared_ptr<ConnectionPort>> ports;
    auto port = std::shared_ptr<ConnectionPort>(new ConnectionPort(PortType::Unisex));
    auto port2 = std::shared_ptr<ConnectionPort>(new ConnectionPort(PortType::Unisex));
    ports.push_back(port);
    ports.push_back(port2);
    return ports;

}
GroupRobotWorldModel::GroupRobotWorldModel():connectionMechanism(this, make_ports()), communicationModule(this) {

}


void GroupRobotWorldModel::setId(int id){
    RobotWorldModel::setId(id);
    if(!this->group){
        this->group = std::make_shared<RobotGroup>();
        this->group->addMember(this);
    }
}

void GroupRobotWorldModel::connectTo(GroupRobotWorldModel* other)
{
    if(!connectionMechanism.canConnect(other)){
        return;
    }
    if(!connectionMechanism.connect(other)){
        return;
    }
    group->addMember(other);

}

void GroupRobotWorldModel::disconnectFrom(GroupRobotWorldModel* other)
{
    //Traverse the robot connections to form two new groups
    auto otherConnections = other->getConnectionMechanism().getConnections();
    other->group = std::make_shared<RobotGroup>();
}

void GroupRobotWorldModel::addRobotToGroup(GroupRobotWorldModel* otherWM)
{


}

void GroupRobotWorldModel::updateTranslationVector()
{
    translation.x = _actualTranslationalValue * cos((_agentAbsoluteOrientation +_actualRotationalVelocity)  * M_PI / 180);
    translation.y = _actualTranslationalValue * sin((_agentAbsoluteOrientation +_actualRotationalVelocity)  * M_PI / 180);
}

Vector2<double>GroupRobotWorldModel::getTranslation()
{
    return translation;
}

void GroupRobotWorldModel::setGroup(std::shared_ptr<RobotGroup> group)
{
    this->group = group;
}

std::shared_ptr<RobotGroup> GroupRobotWorldModel::getGroup()
{
    return group;
}

ConnectionMechanisms& GroupRobotWorldModel::getConnectionMechanism()
{
    return connectionMechanism;
}

CommunicationModule& GroupRobotWorldModel::getCommunicationModule(){
    return communicationModule;
};

