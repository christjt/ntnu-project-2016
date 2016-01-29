#include "WorldModels/GroupRobotWorldModel.h"


GroupRobotWorldModel::GroupRobotWorldModel()
{
    std::cout<< "hello from parent!" << std::endl;
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