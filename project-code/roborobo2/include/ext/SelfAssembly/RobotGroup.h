#ifndef ROBOROBO2_ROBOTGROUP_H
#define ROBOROBO2_ROBOTGROUP_H
#include <unordered_map>
#include "Agents/Robot.h"
class GroupRobotWorldModel;
class RobotGroup
{
private:
    std::unordered_map<int, GroupRobotWorldModel*> members;
    int id = -1;

public:
    int size();
    void addMember(GroupRobotWorldModel* robot);
    void removeMember(GroupRobotWorldModel* robot);
    void mergeWith(std::shared_ptr<RobotGroup> other);
    std::unordered_map<int, GroupRobotWorldModel*>::iterator begin();
    std::unordered_map<int, GroupRobotWorldModel*>::iterator end();

    void setId(int id)
    {
        this->id = id;
    }

    int getId()
    {
        return this->id;
    }

};
#endif //ROBOROBO2_ROBOTGROUP_H
