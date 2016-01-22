/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */


#include "Aggregate/include/AggregateController.h"
#include <Agents/Agent.h>
#include <World/PhysicalObject.h>

AggregateController::AggregateController( RobotWorldModel *__wm ) : Controller ( __wm )
{
	_nInputNodes = _wm->_cameraSensorsNb*2;
	_nOutputNodes = 3;
	std::vector<double> weights(_nInputNodes*_nOutputNodes, 0.0);
	_inputs = std::vector<double>(_nInputNodes, 0);
	_nn = new Neural::MLP(weights, _nInputNodes, _nOutputNodes, false, false, 0);
}

void AggregateController::setWeights(std::vector<double> weights)
{
	_nn->setWeigths(weights);
}

int AggregateController::getNWeights(){
	return _nOutputNodes*_nOutputNodes;
}
AggregateController::~AggregateController()
{
	// nothing to do.
}

void AggregateController::reset()
{
	// nothing to do.
}

void AggregateController::step()
{
	for(int i = 0; i < _wm->_cameraSensorsNb; i++){
		int index = i*2;
		_inputs[index] = (double)gSensorRange - _wm->getDistanceValueFromCameraSensor(i);
		_inputs[index+1] = (double)Agent::isInstanceOf(_wm->getObjectIdFromCameraSensor(i));
	}

	_nn->setInputs(_inputs);
	_nn->step();

	_wm->_desiredTranslationalValue = 9 -9*_nn->readOut()[0];
	_wm->_desiredRotationalVelocity = (_nn->readOut()[1] + _nn->readOut()[2]);
}

