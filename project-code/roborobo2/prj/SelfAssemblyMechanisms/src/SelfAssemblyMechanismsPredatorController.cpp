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