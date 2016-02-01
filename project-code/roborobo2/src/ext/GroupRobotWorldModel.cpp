#include "SelfAssembly/WorldModels/GroupRobotWorldModel.h"


GroupRobotWorldModel::GroupRobotWorldModel()
{
    this->group = std::make_shared<RobotGroup>();
    this->group->addMember(this, getId());
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
    group->addMembers(otherWM->group);
    otherWM->setGroup(group);
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
    if(this->group == group) return;
    this->group = group;
    for(auto it = this->group->begin(); it != this->group->end(); it++){
        GroupRobotWorldModel* member = (*it).second;
        if(member != this);
            member->setGroup(group);
    }

}
std::shared_ptr<RobotGroup> GroupRobotWorldModel::getGroup()
{
    return group;
}
