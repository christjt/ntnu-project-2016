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
        bool isWorldModelInConnections(GroupRobotWorldModel* target);
        std::unordered_set<GroupRobotWorldModel*> findConnectedRobots();
        std::vector<std::shared_ptr<ConnectionPort>> getPorts();
        std::unordered_map<GroupRobotWorldModel*, std::shared_ptr<ConnectionPort>> getConnections();

private:
        std::unordered_map<GroupRobotWorldModel*, std::shared_ptr<ConnectionPort>> portMap;
        std::vector<std::shared_ptr<ConnectionPort>> ports;
        GroupRobotWorldModel* owner;
        void visitNeighbors(std::unordered_set<GroupRobotWorldModel*>& visited);

};


#endif //ROBOROBO2_CONNECTIONMECHANISMS_H
