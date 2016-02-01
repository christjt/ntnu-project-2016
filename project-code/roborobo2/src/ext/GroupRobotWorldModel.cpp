#include "SelfAssembly/WorldModels/GroupRobotWorldModel.h"


GroupRobotWorldModel::GroupRobotWorldModel()
{
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

}
std::shared_ptr<RobotGroup> GroupRobotWorldModel::getGroup()
{

}
