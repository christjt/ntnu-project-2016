#include "SelfAssembly/WorldModels/GroupRobotWorldModel.h"


GroupRobotWorldModel::GroupRobotWorldModel()
{
}
void GroupRobotWorldModel::setId(int id){
    RobotWorldModel::setId(id);
    if(!this->group){
        this->group = std::make_shared<RobotGroup>();
        this->group->addMember(this);
    }
}
void GroupRobotWorldModel::connectTo(int robotId)
{

    desiredConnections.push_back(robotId);
}

void GroupRobotWorldModel::addRobotToGroup(GroupRobotWorldModel* otherWM)
{
    for(int i = 0; i < connections.size(); i++)
    {
        if(connections[i]->getId() == otherWM->getId())
            return;
    }
    connections.push_back(otherWM);
    group->addMember(otherWM);
}
void GroupRobotWorldModel::completeConnections()
{
    desiredConnections.clear();
}
std::vector<GroupRobotWorldModel*> GroupRobotWorldModel::getConnections()
{
    return connections;
}
std::vector<int> GroupRobotWorldModel::getDesiredConnections()
{
    return desiredConnections;
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
