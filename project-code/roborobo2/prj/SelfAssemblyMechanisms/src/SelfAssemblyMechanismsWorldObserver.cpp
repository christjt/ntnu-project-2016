/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */


#include "SelfAssemblyMechanisms/include/SelfAssemblyMechanismsWorldObserver.h"

#include "World/World.h"
#include "SelfAssembly/WorldModels/GroupRobotWorldModel.h"


SelfAssemblyMechanismsWorldObserver::SelfAssemblyMechanismsWorldObserver( World *__world ) : WorldObserver( __world )
{
	_world = __world;
}

SelfAssemblyMechanismsWorldObserver::~SelfAssemblyMechanismsWorldObserver()
{
	// nothing to do.
}

void SelfAssemblyMechanismsWorldObserver::reset()
{
	// nothing to do.
}

void SelfAssemblyMechanismsWorldObserver::step()
{
	for(int i = 0; i < gNumberOfRobots; i++){
		Robot* robot = _world->getRobot(i);
		auto groupWM = ((GroupRobotWorldModel*)robot->getWorldModel());
		if(groupWM->getDesiredConnections().size() > 0)
		{
			auto other = (GroupRobotWorldModel*)_world->getRobot(groupWM->getDesiredConnections()[0])->getWorldModel();
			groupWM->addRobotToGroup(other);
			other->addRobotToGroup(groupWM);
		}
		groupWM->completeConnections();

	}
}
