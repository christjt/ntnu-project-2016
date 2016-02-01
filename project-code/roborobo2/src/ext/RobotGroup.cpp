#include "SelfAssembly/RobotGroup.h"
#include <memory>
int RobotGroup::size(){
    return members.size();
}

void RobotGroup::addMember(GroupRobotWorldModel* robot, int id){
    members[id] = robot;
}
void RobotGroup::addMembers(std::shared_ptr<RobotGroup> otherGroup){

    members.insert(otherGroup->begin(), otherGroup->end());
}

void RobotGroup::mergeWith(std::shared_ptr<RobotGroup> other){
    members.insert(other->begin(), other->end());
}

std::unordered_map<int, GroupRobotWorldModel*>::iterator RobotGroup::begin()
{
    return members.begin();
};
std::unordered_map<int, GroupRobotWorldModel*>::iterator RobotGroup::end()
{
    return members.end();
};

