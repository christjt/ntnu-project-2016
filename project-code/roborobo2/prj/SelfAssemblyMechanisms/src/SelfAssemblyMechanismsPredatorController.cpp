//
// Created by christopher on 03.02.16.
//

#include "SelfAssemblyMechanisms/include/SelfAssemblyMechanismsPredatorController.h"

#include <Agents/Agent.h>

#include "SelfAssembly/WorldModels/GroupRobotWorldModel.h"
#include "Agents/Robot.h"

SelfAssemblyMechanismsPredatorController::SelfAssemblyMechanismsPredatorController( RobotWorldModel *__wm ) : Controller ( __wm )
{
    std::cout << "Added predator controller" << "\n";
}

void SelfAssemblyMechanismsPredatorController::reset()
{
    // nothing to do.
}

void SelfAssemblyMechanismsPredatorController::step()
{
    std::vector<std::pair<Robot*, double>> prey = findPrey();

    for(auto pair: prey)
    {
        if(pair.second <= 1){
            eat(pair.first);
        }
    }


    _wm->_desiredTranslationalValue =  1;
 /*   if ( _wm->getCameraSensorValue(0,5) + _wm->getCameraSensorValue(1,5) + _wm->getCameraSensorValue(2,5) < _wm->getCameraSensorValue(3,5) + _wm->getCameraSensorValue(4,5) + _wm->getCameraSensorValue(5,5) )
        _wm->_desiredRotationalVelocity = +5;
    else
        if ( _wm->getCameraSensorValue(3,5) + _wm->getCameraSensorValue(4,5) + _wm->getCameraSensorValue(5,5) < 3*gSensorRange )
            _wm->_desiredRotationalVelocity = -5;
        else
            if ( _wm->_desiredRotationalVelocity > 0 )
                _wm->_desiredRotationalVelocity--;
            else
                if ( _wm->_desiredRotationalVelocity < 0)
                    _wm->_desiredRotationalVelocity++;
                else
                    _wm->_desiredRotationalVelocity = 0.01 - (double)(rand()%10)/10.*0.02;*/


}

void SelfAssemblyMechanismsPredatorController::eat(Robot* prey)
{
    prey->getWorldModel()->setAlive(false);
    prey->unregisterRobot();
    _wm->_world->unregisterRobot(prey->getWorldModel()->getId());
}

std::vector<std::pair<Robot*, double>> SelfAssemblyMechanismsPredatorController::findPrey()
{
    std::vector<std::pair<Robot*, double>> prey;
    for(int i = 0; i < _wm->_cameraSensorsNb; i++)
    {

        if(_wm->getDistanceValueFromCameraSensor(i) >= gSensorRange)
            continue;
        int objectId = _wm->getObjectIdFromCameraSensor(i);
        bool isOtherRobot =  Agent::isInstanceOf(objectId);
        if(!isOtherRobot)
            continue;
        int id = objectId - gRobotIndexStartOffset;
        auto robot = _wm->getWorld()->getRobot(id);
        if(robot->getIsPredator())
            continue;
        prey.push_back(std::make_pair(robot,1.0));
    }

    return prey;
}


