
#ifndef ROBOROBO2_GROUPROBOTWORLDMODEL_H
#define ROBOROBO2_GROUPROBOTWORLDMODEL_H

#include "WorldModels/RobotWorldModel.h"
#include <vector>
#include <unordered_map>
#include "Agents/Robot.h"
#include "Utilities/Vector2.h"

class GroupRobotWorldModel: public RobotWorldModel
{

    private:
        std::vector<int> desiredConnections;
        std::vector<GroupRobotWorldModel*> connections;
        Vector2<double> translation;
        //RobotGroup* group;
    public:
        GroupRobotWorldModel();
        void connectTo(int robotId);
        void addRobotToGroup(GroupRobotWorldModel* robot);
        void completeConnections();
        std::vector<GroupRobotWorldModel*> getConnections();
        std::vector<int> getDesiredConnections();
        void updateTranslationVector();
        Vector2<double> getTranslation();
};

/*class RobotGroup
{
private:
    std::unordered_map<int, GroupRobotWorldModel*> members;

public:
    int size();
    void addMember(GroupRobotWorldModel*);
    void mergeWith(RobotGroup);



};*/
#endif //ROBOROBO2_GROUPROBOTWORLDMODEL_H