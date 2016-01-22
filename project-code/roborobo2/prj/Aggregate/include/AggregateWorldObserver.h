/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */


#ifndef AGGREGATEWORLDOBSERVER_H
#define AGGREGATEWORLDOBSERVER_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"
#include "EA/DoubleVectorGenotype.h"
#include "Observers/WorldObserver.h"
#include "EA/EvolutionaryAlgorithm.h"
class World;

class AggregateWorldObserver : public WorldObserver
{
	protected:
		int _generationSize;
		int _maxTrialIter;
		int _genIterCntr;
		int _currentPopulationIndex;
		std::default_random_engine _generator;
		EA::EvolutionaryAlgorithm _algorithm;

		void generateInitialPopulation(int size);
		void updateAgentWeights(int currentPopulationIndex);
		
	public:
		AggregateWorldObserver( World *__world );
		~AggregateWorldObserver();
				
		void reset();
		void step();

		double fitness();
};

#endif

