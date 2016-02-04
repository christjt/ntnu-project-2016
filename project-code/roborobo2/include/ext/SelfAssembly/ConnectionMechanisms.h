#ifndef ROBOROBO2_CONNECTIONMECHANISMS_H
#define ROBOROBO2_CONNECTIONMECHANISMS_H

#include <vector>
#include "SelfAssembly/ConnectionPort.h"
#include <memory>
class GroupRobotWorldModel;

class ConnectionMechanisms
{
    public:
        ConnectionMechanisms(GroupRobotWorldModel* owner, std::vector<std::shared_ptr<ConnectionPort>> ports);
        virtual bool canConnect(GroupRobotWorldModel* otherWM);
        virtual bool connect(GroupRobotWorldModel* otherWM);
        virtual bool disconnect(int id);
        virtual void dissolveConnections();
        std::vector<GroupRobotWorldModel*> getConnections();
        std::vector<std::shared_ptr<ConnectionPort>> getPorts();
    private:
        std::vector<GroupRobotWorldModel*> connections;
        std::vector<std::shared_ptr<ConnectionPort>> ports;
        GroupRobotWorldModel* owner;

};


#endif //ROBOROBO2_CONNECTIONMECHANISMS_H
