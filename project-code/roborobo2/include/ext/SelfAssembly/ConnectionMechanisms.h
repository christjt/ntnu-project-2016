#ifndef ROBOROBO2_CONNECTIONMECHANISMS_H
#define ROBOROBO2_CONNECTIONMECHANISMS_H

#include <vector>

class GroupRobotWorldModel;

class ConnectionMechanisms
{
    public:
        ConnectionMechanisms();
        virtual bool canConnect(GroupRobotWorldModel* otherWM);
        virtual bool connect(GroupRobotWorldModel* otherWM);
        std::vector<GroupRobotWorldModel*> getConnections();

    private:
        std::vector<GroupRobotWorldModel*> connections;

};


#endif //ROBOROBO2_CONNECTIONMECHANISMS_H
