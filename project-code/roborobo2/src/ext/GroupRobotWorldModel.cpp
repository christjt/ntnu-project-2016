#include "SelfAssembly/WorldModels/GroupRobotWorldModel.h"
#include "SelfAssembly/PortPosition.h"
#include <unordered_set>
#include "SelfAssembly/Config/PortFactory.h"
static int nextGroupId = 1;
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

bool GroupRobotWorldModel::connectTo(GroupRobotWorldModel* other)
{

    if(!other->isAlive())
        return false;

    if(!connectionMechanism.canConnect(other)){
        return false;
    }
    if(!connectionMechanism.connect(other)){
        return false;
    }
    group->addMember(other);
    group->setId(nextGroupId++);
    return true;
}


bool GroupRobotWorldModel::disconnectFrom(GroupRobotWorldModel* other)
{

    //First traverse all neighbors except the connection to be removed to figure out if there is a cycle
    if(group->size() == 1)
        return false;

    getConnectionMechanism().disconnect(other);

    if(other->getConnectionMechanism().isWorldModelInConnections(this)){
        //There is a cycle. No need to form a new group
        return false;
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

    other->group->setId(nextGroupId++);

    return true;
}

void GroupRobotWorldModel::addRobotToGroup(GroupRobotWorldModel* otherWM)
{


}

void GroupRobotWorldModel::updateTranslationVector()
{
    backUpPosition.x = _xReal;
    backUpPosition.y = _yReal;

    translation.x = _actualTranslationalValue * cos((_agentAbsoluteOrientation +_actualRotationalVelocity)  * M_PI / 180);
    translation.y = _actualTranslationalValue * sin((_agentAbsoluteOrientation +_actualRotationalVelocity)  * M_PI / 180);
    moveCompleted = false;
}

void GroupRobotWorldModel::reset()
{
    this->group = std::make_shared<RobotGroup>();
    this->group->addMember(this);
    this->connectionMechanism = ConnectionMechanisms(this, PortFactory::createPorts(this));
    this->backUpPosition = Vector2<double>();
    this->translation = Vector2<double>();
    nextGroupId = 1;
    this->setEnergyLevel(gEnergyInit);
}
Vector2<double>& GroupRobotWorldModel::getBackupPosition()
{
    return backUpPosition;
}
bool GroupRobotWorldModel::hasPendingMove()
{
    return !moveCompleted;
}

void GroupRobotWorldModel::setMoveCompleted(bool moveCompleted){
    this->moveCompleted = moveCompleted;
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

