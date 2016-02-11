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
    neighbor->getConnectionMechanism().portMap.erase(this->owner);
}

bool ConnectionMechanisms::connect(GroupRobotWorldModel* otherWM)
{
    if(portMap.find(otherWM) != portMap.end())
        return true;

    auto otherPorts = otherWM->getConnectionMechanism().getPorts();
    for(auto port: ports){
        auto eligiblePort = std::find_if(otherPorts.begin(), otherPorts.end(), [&port](std::shared_ptr<ConnectionPort> &otherPort){
            return otherPort->canConnectTo(*(port.get()));
        });

        if(eligiblePort != otherPorts.end()){
            port->connect(eligiblePort->get());
            portMap[otherWM] = port;
            otherWM->getConnectionMechanism().portMap[owner] = *eligiblePort;
            return true;
        }
    }
    return false;
}

bool ConnectionMechanisms::isWorldModelInConnections(GroupRobotWorldModel* target)
{
    std::unordered_set<GroupRobotWorldModel*> robots = findConnectedRobots();
    return robots.find(target) != robots.end();
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
    for(auto connection: portMap){
        connection.first->getConnectionMechanism().visitNeighbors(visited);
    }
}

double ConnectionMechanisms::getOrientation()
{
    return orientation;
}

void ConnectionMechanisms::setOrientation(double orientation)
{
    this->orientation = orientation;
}
double ConnectionMechanisms::getDesiredRotationalVelocity()
{
    return desiredRotationalVelocity;
}

void ConnectionMechanisms::setDesiredRotationalVelocity(double velocity)
{
    this->desiredRotationalVelocity = velocity;
}

double ConnectionMechanisms::getRotationalVelocity()
{
    return rotationalVelocity;
}

void ConnectionMechanisms::setRotationalVelocity(double velocity)
{
    this->rotationalVelocity = velocity;
}

double ConnectionMechanisms::getMaxRotationalVelocity(){
    return maxRotationalVelocity;
}

int ConnectionMechanisms::numConnections(){
    return portMap.size();
}
std::unordered_map<GroupRobotWorldModel*, std::shared_ptr<ConnectionPort>> ConnectionMechanisms::getConnections()
{
    return portMap;
}
const std::vector<std::shared_ptr<ConnectionPort>> &ConnectionMechanisms::getPorts()
{
    return ports;
}