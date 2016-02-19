/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */


#include "SelfAssemblyMechanisms/include/SelfAssemblyMechanismsWorldObserver.h"
#include "World/World.h"
#include "SelfAssembly/WorldModels/GroupRobotWorldModel.h"
#include "Config/GlobalConfigurationLoader.h"
#include "SelfAssemblyMechanisms/include/SelfAssemblyMechanismsPredatorController.h"
#include "SelfAssembly/PortPosition.h"
#include "SelfAssemblyMechanisms/include/NetworkFactories/NetworkFactory.h"
PortPosition* first;
PortPosition* second;

SelfAssemblyMechanismsWorldObserver::SelfAssemblyMechanismsWorldObserver( World *__world ) : WorldObserver( __world )
{
	_world = __world;
	generator.seed(0);
	NetworkFactory::factoryType = ANNType::MLP;

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
