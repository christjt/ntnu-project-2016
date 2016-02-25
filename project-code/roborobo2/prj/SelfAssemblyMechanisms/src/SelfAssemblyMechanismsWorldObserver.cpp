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
	gProperties.checkAndGetPropertyValue("gEAResultsOutputFilename", &SelfAssemblyMechanismsSharedData::gEAResultsOutputFilename, true);
	gProperties.checkAndGetPropertyValue("gDisplayBestGenome", &SelfAssemblyMechanismsSharedData::gDisplayBestGenome, true);
	gProperties.checkAndGetPropertyValue("gGenomeFilename", &SelfAssemblyMechanismsSharedData::gGenomeFileName, true);
	gProperties.checkAndGetPropertyValue("gElitism", &SelfAssemblyMechanismsSharedData::gElitism, true);
	gProperties.checkAndGetPropertyValue("gCrossover", &SelfAssemblyMechanismsSharedData::gCrossover, true);
	gProperties.checkAndGetPropertyValue("gMutation", &SelfAssemblyMechanismsSharedData::gMutation, true);
	gProperties.checkAndGetPropertyValue("gNHiddenLayers", &SelfAssemblyMechanismsSharedData::gNHiddenLayers, true);
	SelfAssemblyMechanismsSharedData::gHiddenLayers = std::vector<unsigned>(SelfAssemblyMechanismsSharedData::gNHiddenLayers);

	for(int i = 0; i < SelfAssemblyMechanismsSharedData::gNHiddenLayers; i++)
	{
		std::ostringstream layerProp;
		layerProp << "layers[" << i << "]";
		SelfAssemblyMechanismsSharedData::gHiddenLayers[i] =  atoi(gProperties.getProperty(layerProp.str(), "0").c_str());
	}

	algorithm.setElitism(SelfAssemblyMechanismsSharedData::gElitism);
	generator.seed(0);
	cGenerations = 0;

	NetworkFactory::hiddenLayers = SelfAssemblyMechanismsSharedData::gHiddenLayers;
	switch (SelfAssemblyMechanismsSharedData::gNNFactory)
	{
		case 0: NetworkFactory::factoryType = ANNType::MLP;
	}




}

SelfAssemblyMechanismsWorldObserver::~SelfAssemblyMechanismsWorldObserver()
{
	// nothing to do.
}

void SelfAssemblyMechanismsWorldObserver::reset()
{
	if(!SelfAssemblyMechanismsSharedData::gDisplayBestGenome){
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
		cGenerations = 0;
		stepsPerGeneration = SelfAssemblyMechanismsSharedData::gEvolutionaryGenerationIterations;
		generationSize = SelfAssemblyMechanismsSharedData::gPopulationSize;

		algorithm.generateInitialPopulation(generationSize, nWeights, generator);
		worldSeed = gRandomSeed+1;
		updateAgentWeights(algorithm.getGenomes()[currentGenome]);

	}else
	{
		loadGeneration();
	}



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
	if(SelfAssemblyMechanismsSharedData::gDisplayBestGenome)
		return;

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

			if(cGenerations == SelfAssemblyMechanismsSharedData::gMaxGenerations){
				std::cout << "Max generations " << SelfAssemblyMechanismsSharedData::gMaxGenerations << " is reached" << std::endl;
				saveGeneration();
				exit(0);
			}

			algorithm.nextGeneration(SelfAssemblyMechanismsSharedData::gCrossover, SelfAssemblyMechanismsSharedData::gMutation, generator);
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

void SelfAssemblyMechanismsWorldObserver::saveGeneration()
{
	std::ofstream out;
	out.open(SelfAssemblyMechanismsSharedData::gEAResultsOutputFilename);
	auto genomes = algorithm.getGenomes();
	std::sort(genomes.begin(), genomes.end(), [](EA::DoubleVectorGenotype a, EA::DoubleVectorGenotype b){
		return a.getFitness() > b.getFitness();
	});
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
	std::string weightsString = inLine.substr(separator+1);
	std::vector<double> weights;
	while(weightsString.find(",", 0) != std::string::npos)
	{
		auto pos = weightsString.find(",", 0);
		double weight = stod(weightsString.substr(0, pos));
		weightsString.erase(0, pos +1);
		weights.push_back(weight);
	}
	EA::DoubleVectorGenotype genotype(weights, -1, 1);
	updateAgentWeights(genotype);
}
