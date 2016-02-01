#include "SelfAssembly/ConnectionMechanisms.h"
#include "SelfAssembly/WorldModels/GroupRobotWorldModel.h"

ConnectionMechanisms::ConnectionMechanisms()
{
}

bool ConnectionMechanisms::canConnect(GroupRobotWorldModel* otherWM)
{
    return true;
}

bool ConnectionMechanisms::connect(GroupRobotWorldModel* otherWM)
{
    for(unsigned int i = 0; i < connections.size(); i++)
    {
        if(connections[i]->getId() == otherWM->getId())
            return true;
    }
    connections.push_back(otherWM);

    return true;
}

std::vector<GroupRobotWorldModel*> ConnectionMechanisms::getConnections()
{
    return connections;
}