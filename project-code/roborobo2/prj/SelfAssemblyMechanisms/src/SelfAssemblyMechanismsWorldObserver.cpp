/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */


#include "SelfAssemblyMechanisms/include/SelfAssemblyMechanismsWorldObserver.h"
#include "SelfAssemblyMechanisms/include/SelfAssemblyMechanismsAgentObserver.h"
#include "World/World.h"
#include "SelfAssembly/WorldModels/GroupRobotWorldModel.h"
#include "Config/GlobalConfigurationLoader.h"
#include "SelfAssemblyMechanisms/include/SelfAssemblyMechanismsPredatorController.h"
#include "SelfAssembly/PortPosition.h"
#include "SelfAssemblyMechanisms/include/NetworkFactories/NetworkFactory.h"
#include "SelfAssemblyMechanisms/include/SelfAssemblyMechanismsController.h"
#include "SelfAssemblyMechanisms/include/EA/DoubleVectorGenotype.h"
#include "SelfAssemblyMechanisms/include/EA/SigmaScalingSelectionMechanism.h"
#include "SelfAssemblyMechanisms/include/EA/TournamentSelectionMechanism.h"
#include <iostream>
#include <mpi/mpi.h>
#include "SelfAssemblyMechanisms/include/Logger/ConsoleLogger.h"
#include "SelfAssemblyMechanisms/include/Logger/MultiLogger.h"
#include "SelfAssemblyMechanisms/include/Logger/FileLogger.h"
#include "SelfAssemblyMechanisms/include/Logger/GenomeVariationLogger.h"
#include <stddef.h>
#include <stdio.h>
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
	gProperties.checkAndGetPropertyValue("gMutationStep", &SelfAssemblyMechanismsSharedData::gMutationStep, true);
	gProperties.checkAndGetPropertyValue("gNHiddenLayers", &SelfAssemblyMechanismsSharedData::gNHiddenLayers, true);
	gProperties.checkAndGetPropertyValue("gEALogFilename", &SelfAssemblyMechanismsSharedData::gEALog, true);
	gProperties.checkAndGetPropertyValue("gStatisticsLog", &SelfAssemblyMechanismsSharedData::gStatisticsLog, true);
	gProperties.checkAndGetPropertyValue("gPassiveEnergyDrain", &SelfAssemblyMechanismsSharedData::gPassiveEnergyDrain, true);
	gProperties.checkAndGetPropertyValue("gConnectionEnergyDrain", &SelfAssemblyMechanismsSharedData::gConnectionEnergyDrain, true);
	gProperties.checkAndGetPropertyValue("gNScenarios", &SelfAssemblyMechanismsSharedData::gNScenarios, true);
	gProperties.checkAndGetPropertyValue("gExplorationThreshold", &SelfAssemblyMechanismsSharedData::gExplorationThreshold, true);
	gProperties.checkAndGetPropertyValue("gExplorationMutationRate", &SelfAssemblyMechanismsSharedData::gExplorationMutationRate, true);
	gProperties.checkAndGetPropertyValue("gTournamentGroupSize", &SelfAssemblyMechanismsSharedData::gTournamentGroupSize, true);
	gProperties.checkAndGetPropertyValue("gTournamentPickChance", &SelfAssemblyMechanismsSharedData::gTournamentPickChance, true);
	gProperties.checkAndGetPropertyValue("gCanEatPredators", &SelfAssemblyMechanismsSharedData::gCanEatPredators, true);
	gProperties.checkAndGetPropertyValue("gPredatorEnergyReward", &SelfAssemblyMechanismsSharedData::gPredatorEnergyReward, true);


	SelfAssemblyMechanismsSharedData::gHiddenLayers = std::vector<unsigned>(SelfAssemblyMechanismsSharedData::gNHiddenLayers);

	for(int i = 0; i < SelfAssemblyMechanismsSharedData::gNHiddenLayers; i++)
	{
		std::ostringstream layerProp;
		layerProp << "layers[" << i << "]";
		SelfAssemblyMechanismsSharedData::gHiddenLayers[i] =  atoi(gProperties.getProperty(layerProp.str(), "0").c_str());
	}


	cGenerations = 0;
	srand(gRandomSeed);
	NetworkFactory::hiddenLayers = SelfAssemblyMechanismsSharedData::gHiddenLayers;
	switch (SelfAssemblyMechanismsSharedData::gNNFactory)
	{
		case 0: NetworkFactory::factoryType = ANNType::MLP;
			break;
		case 1: NetworkFactory::factoryType = ANNType::Elman;
			break;
		case 2: NetworkFactory::factoryType = ANNType::CTRNN;
			break;
	}

}


SelfAssemblyMechanismsWorldObserver::~SelfAssemblyMechanismsWorldObserver()
{
	// nothing to do.
}

void SelfAssemblyMechanismsWorldObserver::reset()
{
	numberOfWeights = getRequiredNumberOfWeights();
	steps = 0;
	cGenerations = 0;
	stepsPerGeneration = SelfAssemblyMechanismsSharedData::gEvolutionaryGenerationIterations;
	generationSize = SelfAssemblyMechanismsSharedData::gPopulationSize;
	worldSeed = gRandomSeed+1;

	initMPI();
	generator.seed(gRandomSeed);
	srand(gRandomSeed);


	for(int i = 0; i < SelfAssemblyMechanismsSharedData::gNScenarios; i++)
	{
		scenarios.push_back(gRandomSeed + i);
	}
	currentScenario = scenarios.begin();
	createMPIDatatypes();


	if(SelfAssemblyMechanismsSharedData::gDisplayBestGenome)
	{
		loadGeneration();
		return;
	}
	std::vector<EA::DoubleVectorGenotype> genomes;
	if(rank == 0)
	{
		algorithm.setElitism(SelfAssemblyMechanismsSharedData::gElitism);
		algorithm.setExplorationThreshold(SelfAssemblyMechanismsSharedData::gExplorationThreshold);
		algorithm.setSelectionMechanism(new EA::TournamentSelectionMechanism(SelfAssemblyMechanismsSharedData::gTournamentGroupSize, SelfAssemblyMechanismsSharedData::gTournamentPickChance));
		algorithm.setLogger(new MultiLogger{new ConsoleLogger(), new GenomeVariationLogger(), new FileLogger(SelfAssemblyMechanismsSharedData::gEALog)});
		genomes = initEA();
	}
	currentGeneration = distributeGenomes(genomes);
	currentGenome = currentGeneration.begin();
	initStatisticsLogger();
	statisticsLogger->beginGeneration(0);
	statisticsLogger->beginGenome(&(*currentGenome));
	statisticsLogger->beginScenario(*currentScenario);


	updateAgentWeights(*currentGenome);
}

void SelfAssemblyMechanismsWorldObserver::initMPI()
{
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
}

void SelfAssemblyMechanismsWorldObserver::initStatisticsLogger()
{
	statisticsLogger = StatisticsLogger::getInstance();
}
void SelfAssemblyMechanismsWorldObserver::createMPIDatatypes()
{
	const int nitems=2;
	int blocklengths[2] = {1, numberOfWeights};
	MPI_Datatype types[2] = {MPI_DOUBLE, MPI_DOUBLE};
	MPI_Aint offsets[2];

	offsets[0] = offsetof(GenomeDTO, fitness);
	offsets[1] = offsetof(GenomeDTO, weights);

	MPI_Type_create_struct(nitems, blocklengths, offsets, types, &genomeDTODatatype);
	MPI_Type_commit(&genomeDTODatatype);

}
std::vector<EA::DoubleVectorGenotype> SelfAssemblyMechanismsWorldObserver::initEA()
{

	return algorithm.generateInitialPopulation(generationSize, getRequiredNumberOfWeights(), generator);
}

int SelfAssemblyMechanismsWorldObserver::getRequiredNumberOfWeights()
{
	for(int i = 0; i < gNumberOfRobots; i++)
	{
		Robot* robot = _world->getRobot(0);
		if(robot->getIsPredator())
			continue;
		return ((SelfAssemblyMechanismsController*)robot->getController())->getGenomeTranslator()->getRequiredNumberOfWeights();
	}
	throw "No robots found";
}

std::vector<EA::DoubleVectorGenotype> SelfAssemblyMechanismsWorldObserver::distributeGenomes(std::vector<EA::DoubleVectorGenotype> genomes)
{


	GenomeDTO* sendBuff = nullptr;
	GenomeDTO* recvBuff = (GenomeDTO *) malloc((sizeof(GenomeDTO) + sizeof(double) * numberOfWeights) * generationSize/world_size);
	if(rank == 0)
	{
		sendBuff = pack(genomes);
	}

	MPI_Scatter(sendBuff, generationSize/world_size, genomeDTODatatype, recvBuff, generationSize/world_size, genomeDTODatatype, 0, MPI_COMM_WORLD);
	auto received = unpack(recvBuff, generationSize/world_size);

	if(rank == 0)
		free(sendBuff);
	free(recvBuff);

	return received;
}


GenomeDTO* SelfAssemblyMechanismsWorldObserver::pack(std::vector<EA::DoubleVectorGenotype> genomes)
{

	char* dtos = (char*)malloc((sizeof(GenomeDTO) + sizeof(double)*numberOfWeights)*genomes.size());
	for(size_t i = 0; i < genomes.size(); i++)
	{
		GenomeDTO* dto = (GenomeDTO*)(dtos + (sizeof(GenomeDTO) + sizeof(double)*numberOfWeights)*i);
		dto->fitness = genomes[i].getFitness();
		memcpy(dto->weights, &genomes[i].getVector().front(), sizeof(double)*numberOfWeights);
	}

	return (GenomeDTO*)dtos;
}

std::vector<EA::DoubleVectorGenotype> SelfAssemblyMechanismsWorldObserver::unpack(GenomeDTO* genomeDTO, size_t size)
{
	std::vector<EA::DoubleVectorGenotype> genomes;
	for(size_t i = 0; i < size; i++)
	{
		GenomeDTO* dto = (GenomeDTO*)((char*)genomeDTO + (sizeof(GenomeDTO) + sizeof(double)*numberOfWeights)*i);
		std::vector<double > weights(dto->weights, dto->weights + numberOfWeights);
		EA::DoubleVectorGenotype genome(weights, -1, 1);
		genome.setFitness(dto->fitness);
		genomes.push_back(genome);
	}

	return genomes;
}

std::vector<EA::DoubleVectorGenotype> SelfAssemblyMechanismsWorldObserver::gatherGenomes()
{

	GenomeDTO* sendBuff = pack(currentGeneration);
	GenomeDTO* recvBuff = nullptr;
	if(rank == 0)
	{
		recvBuff = (GenomeDTO *) malloc((sizeof(GenomeDTO) + sizeof(double) * numberOfWeights) * generationSize);
	}
	MPI_Gather(sendBuff, currentGeneration.size(), genomeDTODatatype, recvBuff, currentGeneration.size(), genomeDTODatatype, 0, MPI_COMM_WORLD);
	std::vector<EA::DoubleVectorGenotype> genomes;
	if(rank == 0)
	{
		genomes =  unpack(recvBuff, generationSize);
		free(recvBuff);
	}
	free(sendBuff);
	return genomes;
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

	if(SelfAssemblyMechanismsSharedData::groupEventTriggered)
		logGroupEvent();

	if(steps == stepsPerGeneration)
	{
		currentGenome->setFitness(currentGenome->getFitness() + evaluate()/scenarios.size());
		statisticsLogger->logFitness(currentGenome->getFitness());
		steps = 0;

		statisticsLogger->endScenario();
		currentScenario++;

		if(currentScenario == scenarios.end()){
			statisticsLogger->endGenome();
			currentGenome++;
			currentScenario = scenarios.begin();
			if(currentGenome != currentGeneration.end())
				statisticsLogger->beginGenome(&(*currentGenome));
		}

		if(currentGenome == currentGeneration.end())
		{
			statisticsLogger->endGeneration();
			cGenerations++;
			currentGeneration = gatherGenomes();
			saveGeneration();
			evaluateCompletionCriteria();
			nextGeneration();
			currentScenario = scenarios.begin();
			statisticsLogger->beginGeneration(cGenerations);

		}
		statisticsLogger->beginScenario(*currentScenario);
		srand(*currentScenario);
		_world->resetWorld();
		updateAgentWeights(*currentGenome);
	}

	steps++;
}


void SelfAssemblyMechanismsWorldObserver::logGroupEvent()
{
	GroupSnaphot snapshot;
	std::unordered_set<int> processedGroups;


	for(int i = 0; i < gNumberOfRobots; i++)
	{
		if(_world->getRobot(i)->getIsPredator())
			continue;

		auto wm = (GroupRobotWorldModel*)_world->getRobot(i)->getWorldModel();
		auto robotGroup = wm->getGroup();
		int groupId = robotGroup->getId();
		if(robotGroup->size() == 1)
			continue;

		if(processedGroups.find(groupId) == processedGroups.end()){
			processedGroups.insert(groupId);
			GroupData groupData;
			groupData.size = robotGroup->size();
			groupData.id = groupId;
			snapshot.groups.push_back(groupData);
		}
	}

	snapshot.numberOfGroups = snapshot.groups.size();
	snapshot.timestamp = steps;

	statisticsLogger->logGroupSnapshot(snapshot);

	SelfAssemblyMechanismsSharedData::groupEventTriggered = false;
}


void SelfAssemblyMechanismsWorldObserver::resetWorld()
{
	for(int i = 0; i < gNumberOfRobots; i++){

	}
}
void SelfAssemblyMechanismsWorldObserver::nextGeneration()
{
	std::vector<EA::DoubleVectorGenotype> nextGeneration;
	if(rank == 0)
		nextGeneration = algorithm.nextGeneration(currentGeneration, SelfAssemblyMechanismsSharedData::gCrossover, SelfAssemblyMechanismsSharedData::gMutation, generator);
	currentGeneration = distributeGenomes(nextGeneration);
	currentGenome = currentGeneration.begin();

}
void SelfAssemblyMechanismsWorldObserver::evaluateCompletionCriteria()
{

	int terminate = 0;
	if(rank == 0){


		for (auto& genome : currentGeneration)
		{
			if(genome.getFitness() >= SelfAssemblyMechanismsSharedData::gTargetFitness)
			{
				std::cout << "Target fitness: " << genome.getFitness() << " is reached" << std::endl;
				terminate = 1;
			}
		}

		if(cGenerations == SelfAssemblyMechanismsSharedData::gMaxGenerations){
			std::cout << "Max generations " << SelfAssemblyMechanismsSharedData::gMaxGenerations << " is reached" << std::endl;
			terminate = 1;
		}
	}

	MPI_Bcast(&terminate, 1, MPI_INT, 0, MPI_COMM_WORLD);
	if(terminate)
	{
		writeStatisticsLog();
		if(rank == 0){
			saveGeneration();
		}
		MPI_Finalize();
		exit(0);
	}
}

void SelfAssemblyMechanismsWorldObserver::writeStatisticsLog()
{


	json localLog = statisticsLogger->serializeToJson();
	std::string rawJson = localLog.dump();

	int localBufferSize = rawJson.size();

	int displacements[world_size];
	int recvCounts[world_size];
	MPI_Gather(&localBufferSize, 1, MPI_INT, recvCounts, 1, MPI_INT, 0, MPI_COMM_WORLD);


	int offset = 0;
	int recvBufferSize = 0;


	char* sendBuff = (char*)malloc(sizeof(char)*localBufferSize);
	memcpy(sendBuff, rawJson.c_str(), rawJson.size());

	char* recvBuff = nullptr;
	if(rank == 0)
	{
		for(int i = 0; i < world_size; i++)
		{
			displacements[i] = offset;
			offset += recvCounts[i];
			recvBufferSize += recvCounts[i];
		}

		recvBuff = (char *) malloc((sizeof(char)* recvBufferSize));
	}
	MPI_Gatherv(sendBuff, localBufferSize, MPI_CHAR, recvBuff, recvCounts, displacements, MPI_CHAR, 0, MPI_COMM_WORLD);



	if(rank == 0)
	{
		std::vector<json> partials;
		for(int i = 0; i < world_size; i++){
			json partial = json::parse(std::string(recvBuff + displacements[i], recvCounts[i]));
			partials.push_back(partial);
		}


		std::unordered_map<int, std::vector<json>> generations;
		for(auto& partial: partials){

			for(int i = 0; i < cGenerations; i++){
				json partialGeneration = partial["generations"][i]["genomes"];
				std::vector<json> genomes = partialGeneration.get<std::vector<json>>();
				for(auto& genome: genomes)
				{
				    generations[i].push_back(genome);
				}
			}
		}

		json final =  partials[0];
		for(int i = 0; i < cGenerations; i++){
			final["generations"][i]["genomes"] = generations[i];
		}


		std::ofstream out;
		out.open(SelfAssemblyMechanismsSharedData::gStatisticsLog);
		out << final.dump(1) << std::endl;
		free(recvBuff);
	}

	free(sendBuff);
}
double SelfAssemblyMechanismsWorldObserver::evaluate()
{
	int nRobots = gNumberOfRobots - gNumberOfPredators;
	int maxAllLifetime = nRobots * SelfAssemblyMechanismsSharedData::gEvolutionaryGenerationIterations;
	int sumLifetime = 0;


	for(int i = 0; i < gNumberOfRobots; i++){
		Robot* robot = _world->getRobot(i);
		if(!robot->getIsPredator()){
			SelfAssemblyMechanismsAgentObserver* observer = (SelfAssemblyMechanismsAgentObserver*) _world->getRobot(i)->getObserver();
			sumLifetime += observer->getLifetime();
		}
	}

	return (double)sumLifetime/maxAllLifetime;
}

void SelfAssemblyMechanismsWorldObserver::saveGeneration()
{
	if(rank != 0)
		return;

	std::ofstream out;
	out.open(SelfAssemblyMechanismsSharedData::gEAResultsOutputFilename);
	auto finalGenomes = currentGeneration;
	finalGenomes.insert(finalGenomes.end(), algorithm.getElites().begin(), algorithm.getElites().end());
	std::sort(finalGenomes.begin(), finalGenomes.end(), [](EA::DoubleVectorGenotype a, EA::DoubleVectorGenotype b){
		return a.getFitness() > b.getFitness();
	});

	for(auto& genome: finalGenomes)
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
