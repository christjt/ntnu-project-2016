#ifndef ROBOROBO2_PORTCONFIGURATION_H
#define ROBOROBO2_PORTCONFIGURATION_H

#include <vector>
#include "SelfAssembly/ConnectionPort.h"
#include "RoboroboMain/roborobo.h"
#include <iostream>
struct PortConfiguration{

    struct Port{
        Port(PortType _type, double _orientation):type(_type), orientation(_orientation){}
        const PortType  type;
        const double orientation;
    };

    const std::vector<Port> ports;
    PortConfiguration():ports(load()){}

    private:
        std::vector<Port> load()
        {
            std::vector<Port> conf;
            for(int i= 0; i < gNumberOfConnectionPoints; i++){
                std::ostringstream portProp;
                portProp << "port[" << i << "]";
                std::string port = portProp.str();

                PortType type =  parsePortType(port);
                double orientation =  parseOrientation(port);
                conf.push_back(Port(type, orientation));
            }
            return conf;
        }

        PortType parsePortType(std::string& port)
        {
            std::ostringstream typeProp;
            typeProp << port << ".type";

            auto typeString = gProperties.getProperty(typeProp.str(), "0");
            switch (atoi(typeString.c_str()))
            {
                case 0: return PortType::Male;
                case 1: return PortType::Female;
                case 2: return PortType::Unisex;
                default: return PortType::Male;
            }
        }

        double parseOrientation(std::string& port)
        {
            std::ostringstream orientationProp;
            orientationProp << port << ".orientation";
            auto orientationString = gProperties.getProperty(orientationProp.str(), "0");
            return atoi(orientationString.c_str());

        }
};
#endif //ROBOROBO2_PORTCONFIGURATION_H
