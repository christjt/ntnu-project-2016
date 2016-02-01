#ifndef ROBOROBO2_ROBOTGROUP_H
#define ROBOROBO2_ROBOTGROUP_H
#include <unordered_map>
#include "SelfAssembly/WorldModels/GroupRobotWorldModel.h"

class RobotGroup
{
private:
    std::unordered_map<int, GroupRobotWorldModel*> members;

public:
    int size();
    void addMember(GroupRobotWorldModel*);
    void mergeWith(RobotGroup);



};
#endif //ROBOROBO2_ROBOTGROUP_H
