#include "SelfAssembly/WorldModels/GroupRobotWorldModel.h"


GroupRobotWorldModel::GroupRobotWorldModel()
{
    thisConnectionMechanism = ConnectionMechanisms();
}
void GroupRobotWorldModel::connectTo(int robotId)
{
    desiredConnections.push_back(robotId);
}

void GroupRobotWorldModel::addRobotToGroup(GroupRobotWorldModel* otherWM)
{
    if(thisConnectionMechanism.canConnect(otherWM)){
        if (!thisConnectionMechanism.connect(otherWM)){
            std::cout << "Connection to" << otherWM << "is unsuccsessful" << "\n";
        }
        else{
            return;
        }
    }
    else{
        std::cout << "Connection is not allowed" << "\n";
    }
}
void GroupRobotWorldModel::completeConnections()
{
    desiredConnections.clear();
}

std::vector<int> GroupRobotWorldModel::getDesiredConnections()
{
    return desiredConnections;
}


void GroupRobotWorldModel::updateTranslationVector()
{
    translation.x = _actualTranslationalValue * cos((_agentAbsoluteOrientation +_actualRotationalVelocity)  * M_PI / 180);
    translation.y = _actualTranslationalValue * sin((_agentAbsoluteOrientation +_actualRotationalVelocity)  * M_PI / 180);
}

Vector2<double>GroupRobotWorldModel::getTranslation()
{
    return translation;
}

void GroupRobotWorldModel::setGroup(std::shared_ptr<RobotGroup> group)
{

}
std::shared_ptr<RobotGroup> GroupRobotWorldModel::getGroup()
{

}

ConnectionMechanisms GroupRobotWorldModel::getConnectionMechanism()
{
    return thisConnectionMechanism;
}
