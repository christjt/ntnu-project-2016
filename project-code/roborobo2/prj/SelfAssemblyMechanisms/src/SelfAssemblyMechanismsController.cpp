/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */

#include "SelfAssemblyMechanisms/include/SelfAssemblyMechanismsController.h"
#include <Agents/Agent.h>
#include "SelfAssembly/WorldModels/GroupRobotWorldModel.h"
#include "SelfAssembly/Communication/CommunicationModule.h"

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
	std::vector<float> message = std::vector<float>(gInitialNumberOfRobots);
	message[_wm->getId()] = 1.0;

	((GroupRobotWorldModel*)_wm)->getCommunicationModule().broadcast(RobotMessage(message));
	auto received = ((GroupRobotWorldModel*)_wm)->getCommunicationModule().read(gInitialNumberOfRobots);


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

