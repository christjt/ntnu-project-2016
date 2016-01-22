/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */


#include "Sandbox/include/SandboxController.h"

SandboxController::SandboxController( RobotWorldModel *__wm ) : Controller ( __wm )
{
	// nothing to do
}

SandboxController::~SandboxController()
{
	// nothing to do.
}

void SandboxController::reset()
{
	// nothing to do.
}

void SandboxController::step()
{
	// a basic obstacle avoidance behavior

	_wm->_desiredTranslationalValue =  + 1 - ( (double)gSensorRange - ((_wm->getCameraSensorValue(2,5)+_wm->getCameraSensorValue(3,5))/2) )  / (double)gSensorRange;
	if ( _wm->getCameraSensorValue(0,5) + _wm->getCameraSensorValue(1,5) + _wm->getCameraSensorValue(2,5) < _wm->getCameraSensorValue(3,5) + _wm->getCameraSensorValue(4,5) + _wm->getCameraSensorValue(5,5) )
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
					_wm->_desiredRotationalVelocity = 0.01 - (double)(rand()%10)/10.*0.02;
}

