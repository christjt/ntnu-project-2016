#include "SelfAssembly/ConnectionPort.h"

#include <iostream>

const int _collisionPositionOffset = 5;
const int _collisionOrientationOffset = 1;
const int PERFECT_ORIENTATIONAL_FIT = 180;

ConnectionPort::ConnectionPort(const PortType& _portType, const PortPosition& _position):position(_position), portType(_portType)
{
}

bool ConnectionPort::connect(ConnectionPort* other)
{
    if(!canConnectTo(*other))
        return false;
    other->connectedTo = this;
    connectedTo = other;
    return true;
}

bool ConnectionPort::canConnectTo(const ConnectionPort& other) const
{
    if(isEngaged() || other.isEngaged()){
        return false;
    }
    return portsCompatible(other.getPortType()) && isGeometricValidConnection(other.position);
}

bool ConnectionPort::isEngaged() const
{

    return connectedTo != nullptr;
}

bool ConnectionPort::portsCompatible(const PortType& other) const
{
    if(this->portType == PortType::Unisex || other == PortType::Unisex)
        return true;

    switch (this->portType){
        case PortType::Female: return other == PortType::Male;
        case PortType::Male: return other == PortType::Female;
        default: throw std::runtime_error("Unknown port type");

    }

}

bool ConnectionPort::isGeometricValidConnection(const PortPosition& other) const
{

    return isOrientationalSound(other) && isSpatiallySound(other);
}

bool ConnectionPort::isOrientationalSound(const PortPosition& other) const
{
    double otherOrientation = other.getOrientation();
    double thisOrientation = position.getOrientation();
    return (abs(thisOrientation- otherOrientation) < PERFECT_ORIENTATIONAL_FIT + _collisionOrientationOffset) && (abs(thisOrientation - otherOrientation) > PERFECT_ORIENTATIONAL_FIT - _collisionOrientationOffset);
}

bool ConnectionPort::isSpatiallySound(const PortPosition& other) const
{
    Vector2<double> otherPos = other.getPosition();
    Vector2<double> thisPos = position.getPosition();
    return (otherPos - thisPos).length() < _collisionPositionOffset;
}

void ConnectionPort::disconnect(){
    if(connectedTo == nullptr)
        return;
    connectedTo->disconnect();
    connectedTo = nullptr;
}
bool ConnectionPort::canDisconnect()
{
    return true;
}

PortType ConnectionPort::getPortType() const
{
    return portType;
}
PortPosition ConnectionPort::getPosition() const
{
    return position;
}

