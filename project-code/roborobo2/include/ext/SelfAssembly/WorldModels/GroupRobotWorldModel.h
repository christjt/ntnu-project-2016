
#ifndef ROBOROBO2_GROUPROBOTWORLDMODEL_H
#define ROBOROBO2_GROUPROBOTWORLDMODEL_H

#include "WorldModels/RobotWorldModel.h"
#include <vector>
#include "Agents/Robot.h"
#include "Utilities/Vector2.h"
#include <memory>

#include "SelfAssembly/ConnectionMechanisms.h"
#include "SelfAssembly/RobotGroup.h"
#include "SelfAssembly/Communication/CommunicationModule.h"
class GroupRobotWorldModel: public RobotWorldModel
{

    private:
        std::vector<int> desiredConnections;
        std::shared_ptr<RobotGroup> group;
        Vector2<double> translation;
        ConnectionMechanisms connectionMechanism;
        CommunicationModule communicationModule;
    public:
        GroupRobotWorldModel();
        void connectTo(int robotId);
        void addRobotToGroup(GroupRobotWorldModel* robot);
        void completeConnections();
        void updateTranslationVector();
        void setGroup(std::shared_ptr<RobotGroup> group);

        Vector2<double> getTranslation();

        std::vector<int> getDesiredConnections();
        std::shared_ptr<RobotGroup> getGroup();

        ConnectionMechanisms& getConnectionMechanism();
        CommunicationModule& getCommunicationModule();
        void setId(int id);

};

/*;*/
#endif //ROBOROBO2_GROUPROBOTWORLDMODEL_H