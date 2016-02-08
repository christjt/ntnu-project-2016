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

}

SelfAssemblyMechanismsWorldObserver::~SelfAssemblyMechanismsWorldObserver()
{
	// nothing to do.
}

void SelfAssemblyMechanismsWorldObserver::reset()
{
	first = new PortPosition((GroupRobotWorldModel*) _world->getRobot(0)->getWorldModel());
	second = new PortPosition((GroupRobotWorldModel*) _world->getRobot(1)->getWorldModel());
}

void SelfAssemblyMechanismsWorldObserver::step()
{
	//BEGIN::ConnectionPortTesting

	std::cout << first->getPosX(0) << " " << first->getPosY(0) << "\n";
	std::cout << second->getPosX(180) << " " << second->getPosY(180) << "\n";
	std::cout << first->isGeometricValidConnection(0, second, 180) << "\n\n";

	//END::ConnectionPortTesting

}
