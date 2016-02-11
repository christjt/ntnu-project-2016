#ifndef ROBOROBO2_PORTFACTORY_H
#define ROBOROBO2_PORTFACTORY_H

#include <memory>
#include <vector>
#include "SelfAssembly/ConnectionPort.h"
#include "SelfAssembly/Config/PortConfiguration.h"
#include "SelfAssembly/PortPosition.h"
class GroupRobotWorldModel;
class PortFactory{

    private:
        static std::unique_ptr<PortConfiguration> config;

    public:
        static std::vector<std::shared_ptr<ConnectionPort>> createPorts(GroupRobotWorldModel* wm)
        {
            if(!PortFactory::config)
                PortFactory::config.reset(new PortConfiguration());

            std::vector<std::shared_ptr<ConnectionPort>> ports;
            for(auto& portConf: config->ports){
                std::shared_ptr<ConnectionPort> port(new ConnectionPort(portConf.type, PortPosition(wm, portConf.orientation)));
                ports.push_back(port);
            }
            return ports;
        }
};

std::unique_ptr<PortConfiguration> PortFactory::config = std::unique_ptr<PortConfiguration>(nullptr);

#endif //ROBOROBO2_PORTFACTORY_H
