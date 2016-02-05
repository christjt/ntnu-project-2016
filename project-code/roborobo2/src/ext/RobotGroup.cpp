#include "SelfAssembly/RobotGroup.h"
#include "SelfAssembly/WorldModels/GroupRobotWorldModel.h"
#include <memory>
int RobotGroup::size(){
    return members.size();
}

void RobotGroup::addMember(GroupRobotWorldModel* robot){


    if(members.find(robot->getId()) != members.end()) return;
    if(members.size() > 0)
        mergeWith(robot->getGroup());
    else
        members[robot->getId()] = robot;


}

void RobotGroup::removeMember(GroupRobotWorldModel* robot){
    if(members.find(robot->getId()) == members.end()) return;
    members.erase(robot->getId());
    robot->setGroup(std::make_shared<RobotGroup>());
}
void RobotGroup::mergeWith(std::shared_ptr<RobotGroup> other){
    auto owner = (*members.begin()).second;
    for(auto it = other->begin(); it != other->end(); it++){
        GroupRobotWorldModel* member = (*it).second;
        member->setGroup(owner->getGroup());
    }
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

