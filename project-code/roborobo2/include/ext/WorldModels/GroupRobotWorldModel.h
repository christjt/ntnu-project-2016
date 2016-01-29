
#ifndef ROBOROBO2_GROUPROBOTWORLDMODEL_H
#define ROBOROBO2_GROUPROBOTWORLDMODEL_H

#include "WorldModels/RobotWorldModel.h"
#include <vector>
#include "Agents/Robot.h"
class GroupRobotWorldModel: public RobotWorldModel
{

    private:
        std::vector<int> desiredConnections;
        std::vector<GroupRobotWorldModel*> connections;
    public:
        GroupRobotWorldModel();
        void connectTo(int robotId);
        void addRobotToGroup(GroupRobotWorldModel* robot);
        void completeConnections();
        std::vector<GroupRobotWorldModel*> getConnections();
        std::vector<int> getDesiredConnections();


};
#endif //ROBOROBO2_GROUPROBOTWORLDMODEL_H