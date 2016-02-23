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


	gProperties.checkAndGetPropertyValue("gEvolutionaryGenerationIterations",&SelfAssemblyMechanismsSharedData::gEvolutionaryGenerationIterations,true);
	gProperties.checkAndGetPropertyValue("gPopulationSize",&SelfAssemblyMechanismsSharedData::gPopulationSize,true);
	gProperties.checkAndGetPropertyValue("gMaxGenerations",&SelfAssemblyMechanismsSharedData::gMaxGenerations,true);
	gProperties.checkAndGetPropertyValue("gTargetFitness",&SelfAssemblyMechanismsSharedData::gTargetFitness,true);
	gProperties.checkAndGetPropertyValue("gNNFactory",&SelfAssemblyMechanismsSharedData::gNNFactory,true);

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

	algorithm.generateInitialPopulation(10, nWeights, 2, generator);
	currentGenome = 0;
	steps = 0;
	stepsPerGeneration = 1500;
	generationSize = (int)algorithm.getGenomes().size();
	worldSeed = gRandomSeed+1;
	updateAgentWeights(algorithm.getGenomes()[currentGenome]);

}
void SelfAssemblyMechanismsWorldObserver::updateAgentWeights(EA::DoubleVectorGenotype& genotype)
{
	for(int i = 0; i <  gNumberOfRobots; i++)
	{
		Robot* robot = _world->getRobot(i);
		if(!robot->getIsPredator())
		{
			((SelfAssemblyMechanismsController*)robot->getController())->getGenomeTranslator()->translateToWeights(genotype);
		}
	}
}
void SelfAssemblyMechanismsWorldObserver::step()
{
	if(steps == stepsPerGeneration)
	{
		algorithm.getGenomes()[currentGenome].setFitness(evaluate());
		steps = 0;
		currentGenome++;
		if(currentGenome == generationSize)
		{
			algorithm.nextGeneration(2, 0.005, generator);
			currentGenome = 0;
			worldSeed++;
		}
		srand(worldSeed);
		_world->resetWorld();
		updateAgentWeights(algorithm.getGenomes()[currentGenome]);
	}
	steps++;
}

double SelfAssemblyMechanismsWorldObserver::evaluate()
{
	int nRobots = gNumberOfRobots - gNumberOfPredators;
	int nDead = 0;
	for(int i = 0; i < gNumberOfRobots; i++){
		Robot* robot = _world->getRobot(i);
		if(!robot->getIsPredator()){
			if(!robot->getWorldModel()->isAlive())
				nDead++;
		}
	}

	return 1 - (double)nDead/nRobots;
}
