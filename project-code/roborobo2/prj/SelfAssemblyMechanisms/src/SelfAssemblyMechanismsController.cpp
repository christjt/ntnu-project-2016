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
	if(!wm->isAlive()){
		wm->_desiredTranslationalValue = 0.0;
		wm->_desiredRotationalVelocity = 0.0;
		wm->getConnectionMechanism().setDesiredRotationalVelocity(0.0);
		return;
	}

	std::vector<GroupRobotWorldModel*> nearbyRobots;
	for(int i = 0; i < wm->_cameraSensorsNb; i++)
	{
		auto objectId = wm->getObjectIdFromCameraSensor(i);
		if(Agent::isInstanceOf(objectId))
		{
			int id = objectId - gRobotIndexStartOffset;
			Robot* robot = wm->getWorld()->getRobot(id);
			if(!robot->getIsPredator()){
				translator->setRobotInput(i, (gSensorRange - wm->getDistanceValueFromCameraSensor(i)/gSensorRange));
				nearbyRobots.push_back((GroupRobotWorldModel*)robot->getWorldModel());
			}else{
				translator->setPredatorInput(i, (gSensorRange - wm->getDistanceValueFromCameraSensor(i)/gSensorRange));
			}
		}else
		{
			translator->setEnvironmentInput(i, (gSensorRange - wm->getDistanceValueFromCameraSensor(i))/gSensorRange);
		}
	}

	translator->setMessageInput(wm->getCommunicationModule().read(messageWidth));
	auto connectionMechanism = wm->getConnectionMechanism();
	auto ports = connectionMechanism.getPorts();
	for(auto i = 0u; i < ports.size(); i++)
	{
		translator->setConnectionInput(i, ports[i]->isEngaged());
	}

	translator->step();

	wm->_desiredTranslationalValue = translator->getTranslationOutput()*2;
	if(wm->_desiredTranslationalValue < 0)
		wm->_desiredTranslationalValue = 0;
	wm->_desiredRotationalVelocity = translator->getRotationOutput();

	connectionMechanism.setDesiredRotationalVelocity(translator->getSensorRotationOutput());

	wm->getCommunicationModule().broadcast(translator->getMessageOut());
	for(auto i = 0u; i < ports.size(); i++)
	{
		if(translator->getDesiresConnection(i)){
			for(GroupRobotWorldModel* robot: nearbyRobots){
				wm->connectTo(robot);
			}
		}
	}

}

