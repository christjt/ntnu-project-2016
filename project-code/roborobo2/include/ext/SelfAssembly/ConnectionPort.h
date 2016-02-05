#ifndef ROBOROBO2_CONNECTIONPORT_H
#define ROBOROBO2_CONNECTIONPORT_H

#include <vector>
enum class PortType{Male, Female, Unisex};
class ConnectionPort{

    private:
        ConnectionPort* connectedTo = nullptr;
        PortType portType;
        bool portsCompatible(PortType other);
    public:
        ConnectionPort(PortType portType);
        bool connect(ConnectionPort* other);
        bool canConnectTo(ConnectionPort* other);
        bool isEngaged();
        void disconnect();
        bool canDisconnect();
        PortType getPortType();


};
#endif //ROBOROBO2_CONNECTIONPORT_H
