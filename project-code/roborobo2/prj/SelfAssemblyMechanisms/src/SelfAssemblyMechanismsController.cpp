/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */

#include "SelfAssemblyMechanisms/include/SelfAssemblyMechanismsController.h"
#include <Agents/Agent.h>
#include "SelfAssembly/WorldModels/GroupRobotWorldModel.h"

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

	_wm->_desiredTranslationalValue = 0.5;
	for(int i = 0; i < _wm->_cameraSensorsNb; i++)
	{
		auto distance =  _wm->getDistanceValueFromCameraSensor(i);
		auto isOtherRobot =  Agent::isInstanceOf(_wm->getObjectIdFromCameraSensor(i));
		if(isOtherRobot){
			if(distance < 10)
			{
				((GroupRobotWorldModel*)_wm)->connectTo((int)_wm->getObjectIdFromCameraSensor(i) - gRobotIndexStartOffset);

			}
		}
	}

}

