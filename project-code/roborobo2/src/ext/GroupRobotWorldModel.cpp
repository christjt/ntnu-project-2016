#include "SelfAssembly/WorldModels/GroupRobotWorldModel.h"
#include <unordered_set>
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
    //First traverse all neighbors except the connection to be removed to figure out if there is a cycle
    if(other->getConnectionMechanism().isWorldModelInConnections(this)){
        //There is a cycle. No need to form a new group
        getConnectionMechanism().disconnect(other);
        return;
    }
    //The robots can ble split into separate groups
    getConnectionMechanism().disconnect(other);
    //Find the robots that should be removed from the group and create a new one.
    auto robots = other->getConnectionMechanism().findConnectedRobots();
    for(auto robot: robots){
        group->removeMember(robot);
        //Make the other robot the owner of the new group
        other->group->addMember(robot);
    }

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

