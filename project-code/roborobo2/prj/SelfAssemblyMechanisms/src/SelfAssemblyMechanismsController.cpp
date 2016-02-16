/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */

#include "SelfAssemblyMechanisms/include/SelfAssemblyMechanismsController.h"
#include <Agents/Agent.h>
#include "SelfAssembly/WorldModels/GroupRobotWorldModel.h"
#include "WorldModels/RobotWorldModel.h"
#include "SelfAssembly/Communication/CommunicationModule.h"
#include "World/World.h"
#include "Agents/Robot.h"
SelfAssemblyMechanismsController::SelfAssemblyMechanismsController( RobotWorldModel *__wm ) : Controller ( __wm )
{
	// nothing to do
	groupWM = (GroupRobotWorldModel*)_wm;
}

SelfAssemblyMechanismsController::~SelfAssemblyMechanismsController()
{
	// nothing to do.
}

void SelfAssemblyMechanismsController::reset()
{
	// nothing to do.
}

int ticks = 0;
void SelfAssemblyMechanismsController::step()
{
	if(!_wm->isAlive()){
		_wm->_desiredTranslationalValue = 0.0;
		_wm->_desiredRotationalVelocity = 0.0;
		groupWM->getConnectionMechanism().setDesiredRotationalVelocity(0.0);
		return;
	}

	if(groupWM->getConnectionMechanism().numConnections() > 0){
		_wm->_desiredRotationalVelocity = 0.5;
	}

	if(groupWM->getConnectionMechanism().numConnections() > 1){
		ticks++;
		done = true;


	}

	if(groupWM->getId() == 3 && ticks > 600 && groupWM->getConnectionMechanism().numConnections() > 0){
		auto other = (*(groupWM->getConnectionMechanism().getConnections().begin())).first;
		groupWM->disconnectFrom(other);
		if(groupWM->getConnectionMechanism().numConnections() == 0){
			_wm->_desiredRotationalVelocity = 1;

		}

	}
	_wm->_desiredTranslationalValue = 1.0;

	std::vector<float> message = std::vector<float>(gInitialNumberOfRobots);
	message[_wm->getId()] = 1.0;

	((GroupRobotWorldModel*)_wm)->getCommunicationModule().broadcast(RobotMessage(message));
	auto received = ((GroupRobotWorldModel*)_wm)->getCommunicationModule().read(gInitialNumberOfRobots);

	((GroupRobotWorldModel*)_wm)->getConnectionMechanism().setDesiredRotationalVelocity(1.0);
	for(int i = 0; i < _wm->_cameraSensorsNb; i++)
	{
		auto distance =  _wm->getDistanceValueFromCameraSensor(i);
		auto isOtherRobot =  Agent::isInstanceOf(_wm->getObjectIdFromCameraSensor(i));
		if(isOtherRobot){
			if(distance < 10)
			{
				auto world = _wm->_world;
				auto other = world->getRobot((int)_wm->getObjectIdFromCameraSensor(i) - gRobotIndexStartOffset);

				if(!other->getIsPredator())
				{
					if(!done){
						((GroupRobotWorldModel*)_wm)->connectTo((GroupRobotWorldModel*)other->getWorldModel());


					}

				}

			}

		}
	}

}

