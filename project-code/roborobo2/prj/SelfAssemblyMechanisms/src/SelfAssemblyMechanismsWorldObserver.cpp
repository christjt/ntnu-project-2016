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
#include "SelfAssemblyMechanisms/include/EA/DoubleVectorGenotype.h"
#include <iostream>
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
	gProperties.checkAndGetPropertyValue("gDisplayBestGenome", &SelfAssemblyMechanismsSharedData::gDisplayBestGenome, true);
	SelfAssemblyMechanismsSharedData::gGenomeFileName = gProperties.getProperty("gGenomeFilename");
	SelfAssemblyMechanismsSharedData::gEAResultsOutputFilename = gProperties.getProperty("gEAResultsOutputFilename");
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

	currentGenome = 0;
	steps = 0;
	stepsPerGeneration = SelfAssemblyMechanismsSharedData::gEvolutionaryGenerationIterations;
	generationSize = SelfAssemblyMechanismsSharedData::gPopulationSize;

	algorithm.generateInitialPopulation(generationSize, nWeights, 2, generator);
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
			cGenerations++;

			for (auto& genome : algorithm.getGenomes())
			{
				if(genome.getFitness() >= SelfAssemblyMechanismsSharedData::gTargetFitness)
				{
					std::cout << "Target fitness: " << genome.getFitness() << " is reached" << std::endl;
					saveGeneration();
					exit(0);
				}
			}

			algorithm.nextGeneration(2, 0.05, generator);
			currentGenome = 0;

			if(cGenerations == SelfAssemblyMechanismsSharedData::gMaxGenerations){
				std::cout << "Max generations " << SelfAssemblyMechanismsSharedData::gMaxGenerations << " is reached" << std::endl;
				exit(0);
			}

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

void SelfAssemblyMechanismsWorldObserver::saveGeneration()
{
	std::ofstream out;
	out.open(SelfAssemblyMechanismsSharedData::gEAResultsOutputFilename);
	auto genomes = algorithm.getGenomes();
	for(auto& genome: genomes)
	{
		out << genome.getFitness() << ":" << genome.toString() << "," << std::endl;
	}
	out.close();
}

void SelfAssemblyMechanismsWorldObserver::loadGeneration()
{
	std::ifstream in;
	in.open(SelfAssemblyMechanismsSharedData::gGenomeFileName);
	std::string inLine;
	std::getline(in,inLine);
	auto separator = inLine.find(":");
	std::string weightsString;
	weightsString.replace(inLine.begin() + separator, inLine.end(), inLine);

	std::vector<double> weights;
	while(weightsString.find(",") != std::string::npos)
	{
		auto pos = weightsString.find(",");
		double weight = stod(weightsString.substr(0, pos));
		weightsString.erase(0, pos +1);
		weights.push_back(weight);
	}

	
}
