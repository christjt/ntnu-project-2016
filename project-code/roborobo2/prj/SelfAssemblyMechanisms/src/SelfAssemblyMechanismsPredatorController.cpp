//
// Created by christopher on 03.02.16.
//

#include "SelfAssemblyMechanisms/include/SelfAssemblyMechanismsPredatorController.h"

#include <Agents/Agent.h>

#include "SelfAssembly/WorldModels/GroupRobotWorldModel.h"
#include "Agents/Robot.h"

SelfAssemblyMechanismsPredatorController::SelfAssemblyMechanismsPredatorController( RobotWorldModel *__wm ) : Controller ( __wm )
{

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
        if(pair.second <= 5 )
        {
            auto wm = (GroupRobotWorldModel*)pair.first->getWorldModel();
            if(wm->getConnectionMechanism().numConnections() > 0)
                continue;
            eat(pair.first);
        }
    }

    for(int i = 0; i < _wm->_cameraSensorsNb; i++)
    {

        if(_wm->getDistanceValueFromCameraSensor(i) >= gSensorRange){
            continue;
        }

        int objectId = _wm->getObjectIdFromCameraSensor(i);
        bool isOtherRobot =  Agent::isInstanceOf(objectId);
        if(!isOtherRobot){
            continue;
        }

        int id = objectId - gRobotIndexStartOffset;
        auto robot = _wm->getWorld()->getRobot(id);
        if(robot->getIsPredator())
            continue;

        _wm->_desiredRotationalVelocity = i/2 * 3 - 3;

        return;
    }

    exploreMovement();


}

void SelfAssemblyMechanismsPredatorController::eat(Robot* prey)
{
    for(auto connection: ((GroupRobotWorldModel*)prey->getWorldModel())->getConnectionMechanism().getConnections()){
        ((GroupRobotWorldModel*)prey->getWorldModel())->disconnectFrom(connection.first);
    }
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
        {
            continue;
        }

        int objectId = _wm->getObjectIdFromCameraSensor(i);
        bool isOtherRobot =  Agent::isInstanceOf(objectId);
        if(!isOtherRobot){
            continue;
        }
        int id = objectId - gRobotIndexStartOffset;
        auto robot = _wm->getWorld()->getRobot(id);
        if(robot->getIsPredator())
            continue;
        prey.push_back(std::make_pair(robot, _wm->getDistanceValueFromCameraSensor(i)));

    }

    return prey;
}

void SelfAssemblyMechanismsPredatorController::exploreMovement(){
    _wm->_desiredTranslationalValue =  1.05 - ( (double)gSensorRange - ((_wm->getCameraSensorValue(2,5)+_wm->getCameraSensorValue(3,5))/2) )  / (double)gSensorRange;

    if ( _wm->getCameraSensorValue(0,5) + _wm->getCameraSensorValue(1,5) + _wm->getCameraSensorValue(2,5) < _wm->getCameraSensorValue(3,5) + _wm->getCameraSensorValue(4,5) + _wm->getCameraSensorValue(5,5) )
    {
        _wm->_desiredRotationalVelocity = +5;
    }
    else if ( _wm->getCameraSensorValue(0,5) + _wm->getCameraSensorValue(1,5) + _wm->getCameraSensorValue(2,5) > _wm->getCameraSensorValue(3,5) + _wm->getCameraSensorValue(4,5) + _wm->getCameraSensorValue(5,5) )
    {
        _wm->_desiredRotationalVelocity = -5;
    }
    else{

        if(fabs(_wm->_desiredRotationalVelocity) < _orientationThreshold)
        {
            _orientationDirection = 1 - (rand() % 2) * 2;
            _wm->_desiredRotationalVelocity = _orientationThreshold * _orientationDirection;

        }
        else if(fabs(_wm->_desiredRotationalVelocity) <= _boundaryPoint)
        {
            _wm->_desiredRotationalVelocity += _orientationChange * _orientationDirection;
        }
        else
        {
            _orientationDirection = (int) (_wm->_desiredRotationalVelocity/fabs(_wm->_desiredRotationalVelocity));
            _wm->_desiredRotationalVelocity = _boundaryPoint * _orientationDirection;
            _orientationDirection = -_orientationDirection;
        }

    }
}


