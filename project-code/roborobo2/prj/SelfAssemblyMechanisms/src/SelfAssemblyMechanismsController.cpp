/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */


#include "SelfAssemblyMechanisms/include/SelfAssemblyMechanismsController.h"
#include <Agents/Agent.h>

SelfAssemblyMechanismsController::SelfAssemblyMechanismsController( RobotWorldModel *__wm ) : Controller ( __wm )
{
	// nothing to do
}

SelfAssemblyMechanismsController::~SelfAssemblyMechanismsController()
{
	// nothing to do.
}

void SelfAssemblyMechanismsController::reset()
{
	// nothing to do.
}

void SelfAssemblyMechanismsController::step()
{
	// a basic obstacle avoidance behavior

	_wm->_desiredTranslationalValue = 0.1;
	for(int i = 0; i < _wm->_cameraSensorsNb; i++){
		auto distance =  _wm->getDistanceValueFromCameraSensor(i);
		auto isOtherRobot =  Agent::isInstanceOf(_wm->getObjectIdFromCameraSensor(i));
		if(isOtherRobot){
			std::cout << "Distance from other robot: <<" << distance << std::endl;
		}
	}

}

