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

	gProperties.checkAndGetPropertyValue("gEvolutionaryGenerationIterations",&SelfAssemblyMechanismsSharedData::gEvolutionaryGenerationIterations,true);
	gProperties.checkAndGetPropertyValue("gPopulationSize",&SelfAssemblyMechanismsSharedData::gPopulationSize,true);
	gProperties.checkAndGetPropertyValue("gMaxGenerations",&SelfAssemblyMechanismsSharedData::gMaxGenerations,true);
	gProperties.checkAndGetPropertyValue("gTargetFitness",&SelfAssemblyMechanismsSharedData::gTargetFitness,true);
	gProperties.checkAndGetPropertyValue("gNNFactory",&SelfAssemblyMechanismsSharedData::gNNFactory,true);

}

SelfAssemblyMechanismsWorldObserver::~SelfAssemblyMechanismsWorldObserver()
{
	// nothing to do.
}

void SelfAssemblyMechanismsWorldObserver::reset()
{
	std::cout << SelfAssemblyMechanismsSharedData::gEvolutionaryGenerationIterations << "\n";
	std::cout << SelfAssemblyMechanismsSharedData::gPopulationSize << "\n";
	std::cout << SelfAssemblyMechanismsSharedData::gMaxGenerations << "\n";
	std::cout << SelfAssemblyMechanismsSharedData::gTargetFitness << "\n";
	std::cout << SelfAssemblyMechanismsSharedData::gNNFactory << "\n";
}

void SelfAssemblyMechanismsWorldObserver::step()
{


}
