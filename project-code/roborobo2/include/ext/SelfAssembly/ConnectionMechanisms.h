#ifndef ROBOROBO2_CONNECTIONMECHANISMS_H
#define ROBOROBO2_CONNECTIONMECHANISMS_H

#include <vector>
#include "SelfAssembly/ConnectionPort.h"
#include <memory>
#include <unordered_set>
#include <unordered_map>
class GroupRobotWorldModel;

class ConnectionMechanisms
{
    public:
        ConnectionMechanisms(GroupRobotWorldModel* owner, std::vector<std::shared_ptr<ConnectionPort>> ports);
        virtual bool canConnect(GroupRobotWorldModel* otherWM);
        virtual bool connect(GroupRobotWorldModel* otherWM);
        virtual void disconnect(GroupRobotWorldModel* neighbor);
        virtual void dissolveConnections();
        bool isWorldModelInConnections(GroupRobotWorldModel* target);
        std::unordered_set<GroupRobotWorldModel*> findConnectedRobots();
        std::vector<GroupRobotWorldModel*> getConnections();
        std::vector<std::shared_ptr<ConnectionPort>> getPorts();
    private:
        std::unordered_map<GroupRobotWorldModel*, std::shared_ptr<ConnectionPort>> portMap;
        std::vector<GroupRobotWorldModel*> connections;
        std::vector<std::shared_ptr<ConnectionPort>> ports;
        GroupRobotWorldModel* owner;
        bool isConnectedTo(GroupRobotWorldModel* target, GroupRobotWorldModel* origin, std::unordered_set<GroupRobotWorldModel*> visited);
        void visitNeighbors(std::unordered_set<GroupRobotWorldModel*>& visited);

};


#endif //ROBOROBO2_CONNECTIONMECHANISMS_H
