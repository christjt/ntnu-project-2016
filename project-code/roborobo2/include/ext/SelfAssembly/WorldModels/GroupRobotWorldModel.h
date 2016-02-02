
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
        std::shared_ptr<RobotGroup> group;

        Vector2<double> translation;

        ConnectionMechanisms thisConnectionMechanism;

    public:
        GroupRobotWorldModel();

        void connectTo(int robotId);
        void addRobotToGroup(GroupRobotWorldModel* robot);
        void completeConnections();
        void updateTranslationVector();
        void setGroup(std::shared_ptr<RobotGroup> group);

        Vector2<double> getTranslation();

        std::vector<GroupRobotWorldModel*> getConnections();
        std::vector<int> getDesiredConnections();
        std::shared_ptr<RobotGroup> getGroup();

        ConnectionMechanisms getConnectionMechanism();
};

/*;*/
#endif //ROBOROBO2_GROUPROBOTWORLDMODEL_H