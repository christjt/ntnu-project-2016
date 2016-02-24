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

#include "SelfAssemblyMechanisms/include/SelfAssemblyMechanismsSharedData.h"

class World;

class SelfAssemblyMechanismsWorldObserver : public WorldObserver
{
	protected:
		EA::EvolutionaryAlgorithm algorithm;
		std::default_random_engine generator;
		void updateAgentWeights(EA::DoubleVectorGenotype& genotype);
		int currentGenome;
		int steps;
		int stepsPerGeneration;
		int generationSize;
		int worldSeed;
		void saveGeneration();
		void loadGeneration();
	public:
		SelfAssemblyMechanismsWorldObserver( World *__world );
		~SelfAssemblyMechanismsWorldObserver();
				
		void reset();
		void step();
		double evaluate();
		
};

#endif

