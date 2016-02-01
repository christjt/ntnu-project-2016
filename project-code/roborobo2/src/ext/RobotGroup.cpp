#include "SelfAssembly/RobotGroup.h"

int RobotGroup::size(){

}
void RobotGroup::addMember(GroupRobotWorldModel* robot){
    if(!members[robot->getId()]){
        members[robot->getId()] = robot;
    }
}
void RobotGroup::mergeWith(RobotGroup){

}