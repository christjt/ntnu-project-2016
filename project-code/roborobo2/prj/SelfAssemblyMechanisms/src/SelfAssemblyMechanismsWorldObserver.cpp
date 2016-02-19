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
#include "SelfAssemblyMechanisms/include/SelfAssemblyMechanismsController.h"
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
	int nWeights = 0;
	for(int i = 0; i < gNumberOfRobots; i++)
	{
		Robot* robot = _world->getRobot(0);
		if(robot->getIsPredator())
			continue;
		nWeights = ((SelfAssemblyMechanismsController*)robot->getController())->getGenomeTranslator()->getRequiredNumberOfWeights();
		break;
	}

	algorithm.generateInitialPopulation(gNumberOfRobots - gNumberOfPredators, nWeights, generator);
	updateAgentWeights(algorithm.getGenomes()[1]);

}
void SelfAssemblyMechanismsWorldObserver::updateAgentWeights(EA::DoubleVectorGenotype& genotype)
{
	for(int i = 0; i <  gNumberOfRobots; i++)
	{
		Robot* robot = _world->getRobot(i);
		if(!robot->getIsPredator()){
			((SelfAssemblyMechanismsController*)robot->getController())->getGenomeTranslator()->translateToWeights(genotype);

		}
	}
}
void SelfAssemblyMechanismsWorldObserver::step()
{


}
