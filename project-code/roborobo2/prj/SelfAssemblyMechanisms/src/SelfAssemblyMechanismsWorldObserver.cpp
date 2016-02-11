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

}

void SelfAssemblyMechanismsWorldObserver::step()
{


}
