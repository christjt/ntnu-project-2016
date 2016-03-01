/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */


#ifndef SELFASSEMBLYMECHANISMSWORLDOBSERVER_H
#define SELFASSEMBLYMECHANISMSWORLDOBSERVER_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"

#include "Observers/WorldObserver.h"
#include "EA/EvolutionaryAlgorithm.h"
#include <random>
#include "EA/DoubleVectorGenotype.h"
#include "SelfAssemblyMechanisms/include/SelfAssemblyMechanismsSharedData.h"
#include <mpi/mpi.h>
class World;
struct GenomeDTO{
	double fitness;
	double weights[];
};
class SelfAssemblyMechanismsWorldObserver : public WorldObserver
{
	protected:
		EA::EvolutionaryAlgorithm algorithm;
		std::default_random_engine generator;
		void updateAgentWeights(EA::DoubleVectorGenotype& genotype);
		std::vector<EA::DoubleVectorGenotype>::iterator currentGenome;
		int steps;
		int stepsPerGeneration;
		int cGenerations;
		int generationSize;
		int worldSeed;
		int rank;
		int world_size;
		int numberOfWeights;
		MPI_Datatype genomeDTODatatype;
		std::vector<EA::DoubleVectorGenotype> currentGeneration;
		void saveGeneration();
		void loadGeneration();
		int getRequiredNumberOfWeights();
		void initMPI();
		void resetWorld();
		void createMPIDatatypes();
		GenomeDTO* pack(std::vector<EA::DoubleVectorGenotype> genome);
		std::vector<EA::DoubleVectorGenotype> unpack(GenomeDTO* genomeDTO, size_t size);
		std::vector<EA::DoubleVectorGenotype> distributeGenomes(std::vector<EA::DoubleVectorGenotype> genomes);
		std::vector<EA::DoubleVectorGenotype> gatherGenomes();
	public:
		SelfAssemblyMechanismsWorldObserver( World *__world );
		~SelfAssemblyMechanismsWorldObserver();
		void evaluateCompletionCriteria();
		void nextGeneration();
		void reset();
		std::vector<EA::DoubleVectorGenotype> initEA();
		void step();
		double evaluate();
		
};

#endif

