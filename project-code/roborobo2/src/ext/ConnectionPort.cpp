#include "SelfAssembly/ConnectionPort.h"

#include <iostream>

const double _collisionPositionOffset = 2;
const double _collisionOrientationOffset = 2.0;
const double PERFECT_ORIENTATIONAL_FIT = 180.0;

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

bool ConnectionPort::isBroken(){
    if(!connectedTo)
        return false;

    return !isGeometricValidConnection(connectedTo->position);

}
bool ConnectionPort::isGeometricValidConnection(const PortPosition& other) const
{

    return isOrientationalSound(other) && isSpatiallySound(other);
}

bool ConnectionPort::isOrientationalSound(const PortPosition& other) const
{
    double otherOrientation = other.getOrientation();
    double thisOrientation = position.getOrientation();
    return (fabs(thisOrientation- otherOrientation) < (PERFECT_ORIENTATIONAL_FIT + _collisionOrientationOffset)) && (fabs(thisOrientation - otherOrientation) > (PERFECT_ORIENTATIONAL_FIT - _collisionOrientationOffset));
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
    connectedTo->connectedTo = nullptr;
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

