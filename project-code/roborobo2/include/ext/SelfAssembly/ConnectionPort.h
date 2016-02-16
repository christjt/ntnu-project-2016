#ifndef ROBOROBO2_CONNECTIONPORT_H
#define ROBOROBO2_CONNECTIONPORT_H

#include <vector>
#include "SelfAssembly/PortPosition.h"
enum class PortType{Male, Female, Unisex};
class ConnectionPort{

    private:
        PortPosition position;
        ConnectionPort* connectedTo = nullptr;
        PortType portType;
        bool portsCompatible(const PortType& other) const;
        bool isOrientationalSound(const PortPosition& other) const;
        bool isSpatiallySound(const PortPosition& other) const;
        bool isGeometricValidConnection(const PortPosition& other) const;

    public:
        ConnectionPort(const PortType &portType, const PortPosition& position);
        bool connect(ConnectionPort* other);
        bool canConnectTo(const ConnectionPort& other) const;
        bool isEngaged() const;
        bool isBroken();
        void disconnect();
        bool canDisconnect();
        PortType getPortType() const;
        PortPosition getPosition() const;


};
#endif //ROBOROBO2_CONNECTIONPORT_H
