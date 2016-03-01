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

#include "SelfAssemblyMechanisms/include/NetworkFactories/MLPFactory.h"
#include "SelfAssemblyMechanisms/include/NetworkFactories/NetworkFactory.h"
#include "SelfAssemblyMechanisms/include/SelfAssemblyMechanismsUtilities.h"

SelfAssemblyMechanismsController::SelfAssemblyMechanismsController( RobotWorldModel *__wm ) : Controller ( __wm )
{
	// nothing to do
	wm = (GroupRobotWorldModel*)_wm;
}

SelfAssemblyMechanismsController::~SelfAssemblyMechanismsController()
{
	// nothing to do.
}

void SelfAssemblyMechanismsController::reset()
{
	messageWidth =  wm->getConnectionMechanism().getPorts().size();
	translator = new NetworkTranslator(wm->_cameraSensorsNb, messageWidth);
	genomeTranslator = new DoubleVectorGenotypeTranslator(translator->getAnn());

}

int ticks = 0;
void SelfAssemblyMechanismsController::step()
{

	if(!wm->isAlive())
	{
		return;
	}

	std::vector<GroupRobotWorldModel*> nearbyRobots;
	updateSensorValues();
	findNearbyRobots(nearbyRobots);
	updateMessageInput();
	updateConnectionInput();

	translator->step();

	applyTranslationOutput();
	applyRotationalOutput();
	applyMessageOutput();
	applyConnectionOutput(nearbyRobots);

}

void SelfAssemblyMechanismsController::updateSensorValues()
{
	for(int i = 0; i < wm->_cameraSensorsNb; i++)
	{
		auto objectId = wm->getObjectIdFromCameraSensor(i);
		if(Agent::isInstanceOf(objectId))
		{
			int id = objectId - gRobotIndexStartOffset;
			Robot* robot = wm->getWorld()->getRobot(id);
			if(!robot->getIsPredator()){
				translator->setRobotInput(i, (gSensorRange - wm->getDistanceValueFromCameraSensor(i)/gSensorRange));
			}else{
				translator->setPredatorInput(i, (gSensorRange - wm->getDistanceValueFromCameraSensor(i)/gSensorRange));
			}
		}else
		{
			translator->setEnvironmentInput(i, (gSensorRange - wm->getDistanceValueFromCameraSensor(i))/gSensorRange);
		}
	}
}

void SelfAssemblyMechanismsController::findNearbyRobots(std::vector<GroupRobotWorldModel*>& dest)
{
	for(int i = 0; i < wm->_cameraSensorsNb; i++)
	{
		auto objectId = wm->getObjectIdFromCameraSensor(i);
		if (Agent::isInstanceOf(objectId)) {
			int id = objectId - gRobotIndexStartOffset;
			Robot *robot = wm->getWorld()->getRobot(id);
			if (!robot->getIsPredator()) {
				dest.push_back((GroupRobotWorldModel *) robot->getWorldModel());
			}
		}
	}
}
void SelfAssemblyMechanismsController::updateMessageInput()
{
	translator->setMessageInput(wm->getCommunicationModule().read(messageWidth));
}

void SelfAssemblyMechanismsController::updateConnectionInput()
{
	auto connectionMechanism = wm->getConnectionMechanism();
	auto ports = connectionMechanism.getPorts();
	for(auto i = 0u; i < ports.size(); i++)
	{
		translator->setConnectionInput(i, ports[i]->isEngaged());
	}
}

void SelfAssemblyMechanismsController::applyTranslationOutput()
{
	wm->_desiredTranslationalValue = translator->getTranslationOutput()*2;
	if(wm->_desiredTranslationalValue < 0)
		wm->_desiredTranslationalValue = 0;
}

void SelfAssemblyMechanismsController::applyRotationalOutput()
{
	wm->_desiredRotationalVelocity = translator->getRotationOutput();
	wm->getConnectionMechanism().setDesiredRotationalVelocity(translator->getSensorRotationOutput());

}

void SelfAssemblyMechanismsController::applyMessageOutput()
{
	wm->getCommunicationModule().broadcast(translator->getMessageOut());
}

void SelfAssemblyMechanismsController::applyConnectionOutput(const std::vector<GroupRobotWorldModel*>& nearbyRobots)
{
	auto ports = wm->getConnectionMechanism().getPorts();
	for(auto i = 0u; i < ports.size(); i++)
	{
		if(translator->getDesiresConnection(i)){
			for(GroupRobotWorldModel* robot: nearbyRobots){
				wm->connectTo(robot);
			}
		}
	}

}


