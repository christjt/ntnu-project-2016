/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */


#include "SelfAssemblyMechanisms/include/SelfAssemblyMechanismsWorldObserver.h"

#include "World/World.h"
#include "SelfAssembly/WorldModels/GroupRobotWorldModel.h"

#include "Config/GlobalConfigurationLoader.h"

#include "SelfAssemblyMechanisms/include/SelfAssemblyMechanismsPredatorController.h"


#include "SelfAssembly/PortPosition.h"

PortPosition* first;
PortPosition* second;

SelfAssemblyMechanismsWorldObserver::SelfAssemblyMechanismsWorldObserver( World *__world ) : WorldObserver( __world )
{
	_world = __world;

	first = new PortPosition((GroupRobotWorldModel*) _world->getRobot(0)->getWorldModel());
	second = new PortPosition((GroupRobotWorldModel*) _world->getRobot(1)->getWorldModel());

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
	//BEGIN::ConnectionPortTesting

	//END::ConnectionPortTesting

}
