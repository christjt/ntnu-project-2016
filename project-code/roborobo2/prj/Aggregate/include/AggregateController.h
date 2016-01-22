/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */



#ifndef AGGREGATECONTROLLER_H
#define AGGREGATECONTROLLER_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"
#include <neuralnetworks/MLP.h>
#include "Controllers/Controller.h"
#include <vector>
#include "WorldModels/RobotWorldModel.h"

class AggregateController : public Controller
{
    private:
		Neural::MLP* _nn;
		std::vector<double> _inputs;
		int _nInputNodes;
		int _nOutputNodes;
	public:
		//Initializes the variables
		AggregateController( RobotWorldModel *__wm );
		~AggregateController();
	    void setWeights(std::vector<double> weights);
		int getNWeights();
		void reset();
		void step();
};


#endif

