#include "SelfAssembly/ConnectionMechanisms.h"
#include "SelfAssembly/WorldModels/GroupRobotWorldModel.h"

ConnectionMechanisms::ConnectionMechanisms(GroupRobotWorldModel* owner, std::vector<std::shared_ptr<ConnectionPort>> ports)
{
    this->ports = ports;
    this->owner = owner;
}

bool ConnectionMechanisms::canConnect(GroupRobotWorldModel* otherWM)
{
    return true;
}

void ConnectionMechanisms::disconnect(GroupRobotWorldModel* neighbor)
{
    auto found = portMap.find(neighbor);
    if(found == portMap.end())
        return;
    auto port = found->second;
    port->disconnect();
    portMap.erase(neighbor);
    connections.erase(std::find(connections.begin(), connections.end(), neighbor));
    auto neighborMechanism = neighbor->getConnectionMechanism();
    neighborMechanism.portMap.erase(this->owner);
    neighbor->getConnectionMechanism().connections.erase(std::find(neighborMechanism.connections.begin(), neighborMechanism.connections.end(), this->owner));
}

bool ConnectionMechanisms::connect(GroupRobotWorldModel* otherWM)
{

    for(unsigned int i = 0; i < connections.size(); i++)
    {
        if(connections[i]->getId() == otherWM->getId())
            return true;
    }

    auto otherPorts = otherWM->getConnectionMechanism().getPorts();
    for(auto port: ports){
        auto eligiblePort = std::find_if(otherPorts.begin(), otherPorts.end(), [&port](std::shared_ptr<ConnectionPort> &otherPort){
            return otherPort->canConnectTo(port.get());
        });

        if(eligiblePort != otherPorts.end()){
            port->connect(eligiblePort->get());
            portMap[otherWM] = port;
            connections.push_back(otherWM);
            otherWM->getConnectionMechanism().connections.push_back(owner);
            otherWM->getConnectionMechanism().portMap[owner] = *eligiblePort;
            return true;
        }
    }
    return false;
}

std::unordered_set<GroupRobotWorldModel*> ConnectionMechanisms::findConnectedRobots()
{
    std::unordered_set<GroupRobotWorldModel*> robots;
    visitNeighbors(robots);
    return robots;
}
void ConnectionMechanisms::visitNeighbors(std::unordered_set<GroupRobotWorldModel*>& visited){
    if(visited.find(this->owner) != visited.end())
        return;
    visited.insert(this->owner);
    for(auto connection: connections){
        connection->getConnectionMechanism().visitNeighbors(visited);
    }
}
bool ConnectionMechanisms::isWorldModelInConnections(GroupRobotWorldModel* target)
{
    std::unordered_set<GroupRobotWorldModel*> visited;
    visited.insert(this->owner);
    for(auto connection: connections){
        if(connection == target)
            continue;
        if(connection->getConnectionMechanism().isConnectedTo(target, connection, visited)){
            return true;
        }
    }
    return false;
}

bool ConnectionMechanisms::isConnectedTo(GroupRobotWorldModel* target, GroupRobotWorldModel* origin, std::unordered_set<GroupRobotWorldModel*> visited)
{
    if(visited.find(this->owner) != visited.end())
        return false;
    visited.insert(this->owner);
    for(auto connection: connections){
        if(connection == origin)
            continue;
        if(connection == target)
            return true;
        if(connection->getConnectionMechanism().isConnectedTo(target, this->owner, visited)){
            return true;
        }
    }
    return false;
}

std::vector<GroupRobotWorldModel*> ConnectionMechanisms::getConnections()
{
    return connections;
}
std::vector<std::shared_ptr<ConnectionPort>> ConnectionMechanisms::getPorts()
{
    return ports;
}
void ConnectionMechanisms::dissolveConnections()
{
    connections.clear();
}