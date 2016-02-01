
#ifndef ROBOROBO2_GROUPROBOTWORLDMODEL_H
#define ROBOROBO2_GROUPROBOTWORLDMODEL_H

#include "WorldModels/RobotWorldModel.h"
#include <vector>
#include "Agents/Robot.h"
#include "Utilities/Vector2.h"
#include <memory>
#include "SelfAssembly/ConnectionMechanisms.h"
class RobotGroup;
class GroupRobotWorldModel: public RobotWorldModel
{

    private:
        std::vector<int> desiredConnections;
        std::vector<GroupRobotWorldModel*> connections;
        Vector2<double> translation;
        std::shared_ptr<RobotGroup> group;
        ConnectionMechanisms thisConnectionMechanism;
    public:
        GroupRobotWorldModel();
        void connectTo(int robotId);
        void addRobotToGroup(GroupRobotWorldModel* robot);
        void completeConnections();
        std::vector<GroupRobotWorldModel*> getConnections();
        std::vector<int> getDesiredConnections();
        void updateTranslationVector();
        Vector2<double> getTranslation();
        void setGroup(std::shared_ptr<RobotGroup> group);
        std::shared_ptr<RobotGroup> getGroup();
};

/*;*/
#endif //ROBOROBO2_GROUPROBOTWORLDMODEL_H