#ifndef ROBOROBO2_CONNECTIONMECHANISMS_H
#define ROBOROBO2_CONNECTIONMECHANISMS_H


class ConnectionMechanisms
{
    public:
        virtual bool canConnect() = 0;
        virtual bool connect() = 0;

};


#endif //ROBOROBO2_CONNECTIONMECHANISMS_H
