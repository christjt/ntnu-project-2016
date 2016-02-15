//
// Created by christopher on 03.02.16.
//

#include "SelfAssemblyMechanisms/include/SelfAssemblyMechanismsPredatorController.h"

#include <Agents/Agent.h>

#include "SelfAssembly/WorldModels/GroupRobotWorldModel.h"


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

    _wm->_desiredTranslationalValue =  + 1 - ( (double)gSensorRange - ((_wm->getCameraSensorValue(2,5)+_wm->getCameraSensorValue(3,5))/2) )  / (double)gSensorRange;

    if ( _wm->getCameraSensorValue(0,5) + _wm->getCameraSensorValue(1,5) + _wm->getCameraSensorValue(2,5) < _wm->getCameraSensorValue(3,5) + _wm->getCameraSensorValue(4,5) + _wm->getCameraSensorValue(5,5) )
    {
        _wm->_desiredRotationalVelocity = +5;
    }
    else if ( _wm->getCameraSensorValue(0,5) + _wm->getCameraSensorValue(1,5) + _wm->getCameraSensorValue(2,5) > _wm->getCameraSensorValue(3,5) + _wm->getCameraSensorValue(4,5) + _wm->getCameraSensorValue(5,5) )
    {
        _wm->_desiredRotationalVelocity = -5;
    }
    else{ //TODO: I velocity != orientation

        if(fabs(_wm->_desiredRotationalVelocity) < _orientationThreshold)
        {
            _orientationDirection = 1 - (rand() % 2) * 2;
            _wm->_desiredRotationalVelocity = _orientationThreshold * _orientationDirection;

        }
        else if(abs(_wm->_desiredRotationalVelocity) <= _boundaryPoint)
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