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

bool ConnectionMechanisms::disconnect(int id)
{
    auto it = std::find_if(connections.begin(), connections.end(), [&id](GroupRobotWorldModel*wm){ return wm->getId() == id;});
    if(it != connections.end()){

    }
    return false;
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
            connections.push_back(otherWM);
            otherWM->getConnectionMechanism().connections.push_back(owner);
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