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
#include "SelfAssemblyMechanisms/include/DenseInputNetworkTranslator.h"
#include "SelfAssemblyMechanisms/include/SparseInputNetworkTranslator.h"
#include "SelfAssemblyMechanisms/include/SelfAssemblyMechanismsSharedData.h"

SelfAssemblyMechanismsController::SelfAssemblyMechanismsController( RobotWorldModel *__wm ) :
		Controller ( __wm )
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
	messageWidth = wm->getConnectionMechanism().getPorts().size();
	translator = std::shared_ptr<DenseInputNetworkTranslator>(new DenseInputNetworkTranslator(wm->_cameraSensorsNb, messageWidth));
	genomeTranslator =  std::shared_ptr<CTRNNGenomeTranslator>(new CTRNNGenomeTranslator(translator->getAnn()));

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
				translator->setRobotInput(i, (gSensorRange - wm->getDistanceValueFromCameraSensor(i))/gSensorRange);
			}else{
				translator->setPredatorInput(i, (gSensorRange - wm->getDistanceValueFromCameraSensor(i))/gSensorRange);
			}
		}else
		{
			if(EnergyItem::isInstanceOf(objectId)){
				translator->setEnergyInput(i, (gSensorRange - wm->getDistanceValueFromCameraSensor(i))/gSensorRange);
			}else{
				translator->setEnvironmentInput(i, (gSensorRange - wm->getDistanceValueFromCameraSensor(i))/gSensorRange);
			}
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

void SelfAssemblyMechanismsController::updateEnergyLevel()
{
	translator->setEnergyLevel(wm->getEnergyLevel()/gEnergyMax);
}

void SelfAssemblyMechanismsController::applyTranslationOutput()
{
	wm->_desiredTranslationalValue = translator->getTranslationOutput()*1.99;
	if(wm->_desiredTranslationalValue < 0)
		wm->_desiredTranslationalValue = 0;
}

void SelfAssemblyMechanismsController::applyRotationalOutput()
{
	wm->_desiredRotationalVelocity = SelfAssemblyMechanismsUtilities::normalizeDouble(translator->getRotationOutput(), 0.0, 1.0, -1.0, 1.0);
	wm->getConnectionMechanism().setDesiredRotationalVelocity(SelfAssemblyMechanismsUtilities::normalizeDouble(translator->getSensorRotationOutput(), 0.0, 1.0, -1.0, 1.0));

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
				if(wm->connectTo(robot))
					SelfAssemblyMechanismsSharedData::groupEventTriggered = true;

			}
		}

		if(translator->getDesiresDisconnect(i))
		{
			for(auto connection: wm->getConnectionMechanism().getConnections())
			{
				if(connection.second == ports[i])
				{
					if(wm->disconnectFrom(connection.first))
						SelfAssemblyMechanismsSharedData::groupEventTriggered = true;
				}
			}
		}
	}

}


