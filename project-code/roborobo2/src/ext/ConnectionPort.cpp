#include "SelfAssembly/ConnectionPort.h"

#include <iostream>
ConnectionPort::ConnectionPort(PortType portType)
{
    this->portType = portType;
}

bool ConnectionPort::connect(ConnectionPort* other)
{
    if(!canConnectTo(other))
        return false;
    other->connectedTo = this;
    connectedTo = other;
    return true;
}

bool ConnectionPort::canConnectTo(ConnectionPort* other)
{
    if(isEngaged() || other->isEngaged()){
        return false;
    }

    return portsCompatible(other->getPortType());
}

bool ConnectionPort::isEngaged()
{
    return connectedTo != nullptr;
}

bool ConnectionPort::portsCompatible(PortType other)
{
    if(this->portType == PortType::Unisex || other == PortType::Unisex)
        return true;

    switch (this->portType){
        case PortType::Female: return other == PortType::Male;
        case PortType::Male: return other == PortType::Female;
        default: throw std::runtime_error("Unknown port type");

    }

}

bool ConnectionPort::canDisconnect()
{
    return true;
}

PortType ConnectionPort::getPortType(){
    return portType;
}


