/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */


#include "Aggregate/include/AggregateWorldObserver.h"
#include "World/World.h"
#include "Aggregate/include/AggregateController.h"
#include "Aggregate/include/EA/RouletteWheel.h"

#include <math.h>

#include <vector>

#include <random>


AggregateWorldObserver::AggregateWorldObserver( World *__world ) : WorldObserver( __world )
{
	_world = __world;
	_maxTrialIter = 1000;
	_genIterCntr = 0;
	_generationSize = 16;
	_currentPopulationIndex = 0;
	_generator.seed((unsigned int)time(0));
}

void AggregateWorldObserver::updateAgentWeights(int currentPopulationIndex)
{
	int n_robots = _world->getNbOfRobots();
	auto genome = _algorithm.getGenomes()[currentPopulationIndex];

	for(int i = 0; i < n_robots; i++){

		Robot* robot = _world->getRobot(i);
		AggregateController* controller = (AggregateController*)robot->getController();
		controller->setWeights(genome.getVector());
	}
}
AggregateWorldObserver::~AggregateWorldObserver()
{
	// nothing to do.
}

void AggregateWorldObserver::reset()
{
	int nWeights = ((AggregateController*)_world->getRobot(0)->getController())->getNWeights();
	_algorithm.generateInitialPopulation(_generationSize, nWeights, _generator);
	updateAgentWeights(_currentPopulationIndex);
}

void AggregateWorldObserver::step()
{
	if (_genIterCntr == _maxTrialIter){
		_algorithm.getGenomes()[_currentPopulationIndex].setFitness(fitness());
		_genIterCntr = 0;
		_currentPopulationIndex++;
		if(_currentPopulationIndex == _generationSize){
			_algorithm.nextGeneration(2, 0.05, _generator);
			_currentPopulationIndex = 0;
		}
		srand(gRandomSeed);
		_world->resetWorld();
		updateAgentWeights(_currentPopulationIndex);
	}

	_genIterCntr++;
}

double AggregateWorldObserver::fitness()
{
	int x1, y1, x2, y2, numOfComparisons, numOfActors;

	double sumDistance = 0;

	double averageDistance, maxDistance, fitness;

	numOfActors = _world->getNbOfRobots();

	maxDistance = sumDistance += sqrt(pow(1350, 2) + pow(800, 2));

	numOfComparisons = numOfActors*(numOfActors - 1)/2;


	for (int i = 0; i < numOfActors - 1; ++i) {
		_world->getRobot(i)->getCoord(x1, y1);
		for (int j = i + 1; j < numOfActors; ++j) {
			_world->getRobot(j)->getCoord(x2, y2);
			sumDistance += sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
		}
	}

	averageDistance = sumDistance/numOfComparisons;

	fitness = 1 - averageDistance/maxDistance;

	return fitness;


}
