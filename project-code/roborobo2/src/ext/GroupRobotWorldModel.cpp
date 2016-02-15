#include "SelfAssembly/WorldModels/GroupRobotWorldModel.h"
#include "SelfAssembly/PortPosition.h"
#include <unordered_set>
#include "SelfAssembly/Config/PortFactory.h"

GroupRobotWorldModel::GroupRobotWorldModel():connectionMechanism(this, PortFactory::createPorts(this)), communicationModule(this)
{

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
    if(!other->isAlive())
        return;
    
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
    getConnectionMechanism().disconnect(other);

    if(other->getConnectionMechanism().isWorldModelInConnections(this)){
        //There is a cycle. No need to form a new group
        return;
    }
    //The robots should ble split into separate groups
    //Find the robots that should be removed from the group and create a new one.
    auto robots = other->getConnectionMechanism().findConnectedRobots();
    group->removeMember(other);
    for(auto robot: robots){
        if(robot == other)
            continue;
        group->removeMember(robot);
        //Make the other robot the owner of the new group
        other->group->addMember(robot);
    }

    std::cout << "Other " << other->group->size() << std::endl;

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

