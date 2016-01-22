/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 * NNlib: Leo Cazenille <leo.cazenille@upmc.fr>
 */

#include "DemoMedea/include/DemoMedeaController.h"
#include "DemoMedea/include/DemoMedeaWorldObserver.h"

#include "World/World.h"
#include "Utilities/Misc.h"
#include <math.h>
#include <string>

#include <neuralnetworks/MLP.h>
#include <neuralnetworks/Perceptron.h>
#include <neuralnetworks/Elman.h>

using namespace Neural;

DemoMedeaController::DemoMedeaController( RobotWorldModel *wm )
{
	_wm = wm;
    
    nn = NULL;
    
    // evolutionary engine
    
    _minValue = -1.0;
	_maxValue = 1.0;
    
	_currentSigma = DemoMedeaSharedData::gSigmaRef;
    
	resetRobot();

    // behaviour

	_iteration = 0;

    _birthdate = 0;

    if ( gEnergyLevel )
        _wm->setEnergyLevel(gEnergyInit);

    _wm->updateLandmarkSensor();
    
	_wm->setAlive(true);
    _wm->setRobotLED_colorValues(255, 0, 0);
    
    //std::cout << "["<< _wm->getId() <<"]BREAKPOINT.0: " << _wm->_desiredTranslationalValue << " , " << _wm->_desiredRotationalVelocity << "\n";


}

DemoMedeaController::~DemoMedeaController()
{
    _parameters.clear();
	delete nn;
	nn = NULL;
}

void DemoMedeaController::reset()
{
	_parameters.clear();
	_parameters = _genome;
}


void DemoMedeaController::step()
{
	_iteration++;
    stepEvolution();
    if ( _wm->isAlive() )
	{
        stepBehaviour();
    }
    else
    {
        _wm->_desiredTranslationalValue = 0.0;
        _wm->_desiredRotationalVelocity = 0.0;
    }

}


// ################ ######################## ################
// ################ ######################## ################
// ################ BEHAVIOUR METHOD(S)      ################
// ################ ######################## ################
// ################ ######################## ################



void DemoMedeaController::stepBehaviour()
{
    // pre-compute closest landmark information (if needed)
    if ( gLandmarks.size() > 0 )
    {
        _wm->updateLandmarkSensor();
    }
    
    // ---- Build inputs ----
    
    std::vector<double>* inputs = new std::vector<double>(_nbInputs);
    int inputToUse = 0;
    
    // distance sensors
    for(int i  = 0; i < _wm->_cameraSensorsNb; i++)
    {
        (*inputs)[inputToUse] = _wm->getDistanceValueFromCameraSensor(i) / _wm->getCameraSensorMaximumDistanceValue(i);
        inputToUse++;
        
        if ( gExtendedSensoryInputs ) // EXTENDED SENSORY INPUTS: code provided as example, should be rewritten to suit your need.
        {
            // WHAT FOLLOWS IS AN EXAMPLE OF EXTENDED SENSORY INPUTS
            // Rewrite to match your own extended input scheme, if needed.
            // You may tune it on/off using gExtendedSensoryInputs defined in the properties file.
            // When modifying this code, dont forget to update the initialization in the resetRobot() method
            // Example:
            //      - you may want to distinguish between robot's groups (if more than 1)
            //      - you may want to restrict the number of objects that can be identified (if not all possible objects are in use)
            //      - you may want to compress inputs (e.g. binary encoding instead of one-input-per-object-type.
            //      - (...)
            //
            // In the following
            //      - inputs[N_physicalobjecttypes]: 0 or 1 is active, other are set to zero.
            //      - inputs[2]: (a) is it a robot? (b) is it from the same group? (c) what is its relative orientation wrt. current robot
            //      - inputs[1]: is it a wall (=1), or nothing (=0)
            //      Comment: from 0 (nothing) to 2 (robot, same group) active inputs.
            
            int objectId = _wm->getObjectIdFromCameraSensor(i);
            
            // input: physical object? which type?
            if ( PhysicalObject::isInstanceOf(objectId) )
            {
                int nbOfTypes = PhysicalObjectFactory::getNbOfTypes();
                for ( int i = 0 ; i != nbOfTypes ; i++ )
                {
                    // if ( i == ( objectId - gPhysicalObjectIndexStartOffset ) ) // [bug]: discovered by Inaki F. -- solved 2014-09-21
                    if ( i == gPhysicalObjects[objectId - gPhysicalObjectIndexStartOffset]->getType() )
                        (*inputs)[inputToUse] = 1; // match
                    else
                        (*inputs)[inputToUse] = 0;
                    inputToUse++;
                }
            }
            else
            {
                // not a physical object. But: should still fill in the inputs (with zeroes)
                int nbOfTypes = PhysicalObjectFactory::getNbOfTypes();
                for ( int i = 0 ; i != nbOfTypes ; i++ )
                {
                    (*inputs)[inputToUse] = 0;
                    inputToUse++;
                }
            }

            // input: another agent? If yes: same group?
            if ( Agent::isInstanceOf(objectId) )
            {
                // this is an agent
                (*inputs)[inputToUse] = 1;
                inputToUse++;

                // same group?
                if ( gWorld->getRobot(objectId-gRobotIndexStartOffset)->getWorldModel()->getGroupId() == _wm->getGroupId() )
                {
                    (*inputs)[inputToUse] = 1; // match: same group
                }
                else
                {
                    (*inputs)[inputToUse] = 0; // not the same group
                }
                inputToUse++;
                
                // relative orientation? (ie. angle difference wrt. current agent)
                double srcOrientation = _wm->_agentAbsoluteOrientation;
                double tgtOrientation = gWorld->getRobot(objectId-gRobotIndexStartOffset)->getWorldModel()->_agentAbsoluteOrientation;
                double delta_orientation = - ( srcOrientation - tgtOrientation );
                if ( delta_orientation >= 180.0 )
                    delta_orientation = - ( 360.0 - delta_orientation );
                else
                    if ( delta_orientation <= -180.0 )
                        delta_orientation = - ( - 360.0 - delta_orientation );
                (*inputs)[inputToUse] = delta_orientation/180.0;
                inputToUse++;
                
                /* //todelete
                 // ----- DEBUG::SANDBOX
                std::cout << "src.orientation: " <<  srcOrientation
                    << "° ; tgt.orientation: " << tgtOrientation
                    << "° ; delta orientation: " << delta_orientation
                    << " <==> " << delta_orientation/180.0 << "°"
                    << std::endl;
                // ----- DEBUG::SANDBOX. 
                */
            }
            else
            {
                (*inputs)[inputToUse] = 0; // not an agent...
                inputToUse++;
                (*inputs)[inputToUse] = 0; // ...therefore no match wrt. group.
                inputToUse++;
                /*
                (*inputs)[inputToUse] = 0; // ...and no orientation.
                inputToUse++;
                */
            }
            
            // input: wall or empty?
            if ( objectId >= 0 && objectId < gPhysicalObjectIndexStartOffset ) // not empty, but cannot be identified: this is a wall.
                (*inputs)[inputToUse] = 1;
            else
                (*inputs)[inputToUse] = 0; // nothing. (objectId=-1)
            inputToUse++;
        }
    }
    
    // floor sensor
    (*inputs)[inputToUse++] = (double)_wm->getGroundSensor_redValue()/255.0;
    (*inputs)[inputToUse++] = (double)_wm->getGroundSensor_greenValue()/255.0;
    (*inputs)[inputToUse++] = (double)_wm->getGroundSensor_blueValue()/255.0;
    
    // closest landmark (if exists)
    if ( gLandmarks.size() > 0 )
    {
        (*inputs)[inputToUse++] = _wm->getLandmarkDirectionAngleValue();
        (*inputs)[inputToUse++] = _wm->getLandmarkDistanceValue();
    }
    
    // energy level
    if ( gEnergyLevel )
    {
        (*inputs)[inputToUse++] = _wm->getEnergyLevel() / gEnergyMax;
    }
    
    // ---- compute and read out ----
    
    nn->setWeigths(_parameters); // create NN
    
    nn->setInputs(*inputs);
        
    nn->step();
    
    std::vector<double> outputs = nn->readOut();

    _wm->_desiredTranslationalValue = outputs[0];
    _wm->_desiredRotationalVelocity = outputs[1];

    if ( DemoMedeaSharedData::gEnergyRequestOutput )
    {
        _wm->setEnergyRequestValue(outputs[2]);
    }
    
    // normalize to motor interval values
    _wm->_desiredTranslationalValue = _wm->_desiredTranslationalValue * gMaxTranslationalSpeed;
    _wm->_desiredRotationalVelocity = _wm->_desiredRotationalVelocity * gMaxRotationalSpeed;
    
    delete (inputs);
}


void DemoMedeaController::createNN()
{
    if ( nn != NULL ) // useless: delete will anyway check if nn is NULL or not.
        delete nn;
    
    switch ( DemoMedeaSharedData::gControllerType )
    {
        case 0:
        {
            // MLP
            nn = new MLP(_parameters, _nbInputs, _nbOutputs, *(_nbNeuronsPerHiddenLayer));
            break;
        }
        case 1:
        {
            // PERCEPTRON
            nn = new Perceptron(_parameters, _nbInputs, _nbOutputs);
            break;
        }
        case 2:
        {
            // ELMAN
            nn = new Elman(_parameters, _nbInputs, _nbOutputs, *(_nbNeuronsPerHiddenLayer));
            break;
        }
        default: // default: no controller
            std::cerr << "[ERROR] gController type unknown (value: " << DemoMedeaSharedData::gControllerType << ").\n";
            exit(-1);
    };
}


unsigned int DemoMedeaController::computeRequiredNumberOfWeights()
{
    unsigned int res = nn->getRequiredNumberOfWeights();
    return res;
}

// ################ ######################## ################
// ################ ######################## ################
// ################ EVOLUTION ENGINE METHODS ################
// ################ ######################## ################
// ################ ######################## ################

void DemoMedeaController::stepEvolution()
{
    // * broadcasting genome : robot broadcasts its genome to all neighbors (contact-based wrt proximity sensors)
    if  ( gRadioNetwork )
    {
        broadcastGenome();
    }
    
	// * lifetime ended: replace genome (if possible)
	if( dynamic_cast<DemoMedeaWorldObserver*>(gWorld->getWorldObserver())->getLifeIterationCount() >= DemoMedeaSharedData::gEvaluationTime-1 )
	{
        loadNewGenome();
    }
    
    if ( getNewGenomeStatus() ) // check for new NN parameters
	{
		reset();
		setNewGenomeStatus(false);
	}
}


void DemoMedeaController::selectRandomGenome()
{
    if(_genomesList.size() != 0)
    {
        int randomIndex = rand()%_genomesList.size();
        std::map<int, std::vector<double> >::iterator it = _genomesList.begin();
        while (randomIndex !=0 )
        {
            it ++;
            randomIndex --;
        }
        
        _currentGenome = (*it).second;
        
        mutate(_sigmaList[(*it).first]);
        
        setNewGenomeStatus(true);
        
        _birthdate = gWorld->getIterations();
        
        // Logging
        std::string s = std::string("");
        s += "{" + std::to_string(gWorld->getIterations()) + "} [" + std::to_string(_wm->getId()) + "::" + std::to_string(_birthdate) + "] descends from [" + std::to_string((*it).first) + "::" + std::to_string(_birthdateList[(*it).first]) + "]\n";
        gLogManager->write(s);
        gLogManager->flush();
        
        _genomesList.clear();
    }
}


void DemoMedeaController::storeGenome(std::vector<double> genome, int senderId, int senderBirthdate, float sigma)
{
	_genomesList[senderId] = genome;
    _sigmaList[senderId] = sigma;
    _birthdateList[senderId] = senderBirthdate;
}


void DemoMedeaController::mutate( float sigma) // mutate within bounds.
{
	_genome.clear();
    
	_currentSigma = sigma;
    
	for (unsigned int i = 0 ; i != _currentGenome.size() ; i++ )
	{
		double value = _currentGenome[i] + getGaussianRand(0,_currentSigma);
		// bouncing upper/lower bounds
		if ( value < _minValue )
		{
			double range = _maxValue - _minValue;
			double overflow = - ( (double)value - _minValue );
			overflow = overflow - 2*range * (int)( overflow / (2*range) );
			if ( overflow < range )
				value = _minValue + overflow;
			else // overflow btw range and range*2
				value = _minValue + range - (overflow-range);
		}
		else if ( value > _maxValue )
		{
			double range = _maxValue - _minValue;
			double overflow = (double)value - _maxValue;
			overflow = overflow - 2*range * (int)( overflow / (2*range) );
			if ( overflow < range )
				value = _maxValue - overflow;
			else // overflow btw range and range*2
				value = _maxValue - range + (overflow-range);
		}
        
		_genome.push_back(value);
	}
    
	_currentGenome = _genome;
    
    // Logging
    std::string s = std::string("");
    s += "{" + std::to_string(gWorld->getIterations()) + "} [" + std::to_string(_wm->getId()) + "::" + std::to_string(_birthdate) + "] [sigma=" + std::to_string(_currentSigma) + "]\n";
    gLogManager->write(s);
    gLogManager->flush();
}


void DemoMedeaController::resetRobot()
{
    _nbInputs = 0;
    
    if ( gExtendedSensoryInputs ) // EXTENDED SENSORY INPUTS: code provided as example, should be rewritten to suit your need.
    {
        _nbInputs = ( PhysicalObjectFactory::getNbOfTypes()+3+1 ) * _wm->_cameraSensorsNb; // nbOfTypes + ( isItAnAgent? + isItSameGroupId? + agentAngleDifference?) + isItAWall?
    }
        
    _nbInputs += _wm->_cameraSensorsNb + 3; // proximity sensors + ground sensor (3 values)
    if ( gEnergyLevel )
        _nbInputs += 1; // incl. energy level
    if ( gLandmarks.size() > 0 )
        _nbInputs += 2; // incl. landmark (angle,dist)

	_nbOutputs = 2;
    if ( DemoMedeaSharedData::gEnergyRequestOutput )
        _nbOutputs += 1; // incl. energy request
    
	_nbHiddenLayers = DemoMedeaSharedData::gNbHiddenLayers;
    
    _nbNeuronsPerHiddenLayer = new std::vector<unsigned int>(_nbHiddenLayers);
	for(unsigned int i = 0; i < _nbHiddenLayers; i++)
		(*_nbNeuronsPerHiddenLayer)[i] = DemoMedeaSharedData::gNbNeuronsPerHiddenLayer;
    
    createNN();
    
	unsigned int const nbGene = computeRequiredNumberOfWeights();
    
    if ( gVerbose )
        std::cout << std::flush ;

	_genome.clear();
    
	for ( unsigned int i = 0 ; i != nbGene ; i++ )
	{
        _genome.push_back((double)(rand()%DemoMedeaSharedData::gNeuronWeightRange)/(DemoMedeaSharedData::gNeuronWeightRange/2)-1.0); // weights: random init between -1 and +1
	}
	_currentGenome = _genome;
	setNewGenomeStatus(true);
	_genomesList.clear();
    
}


void DemoMedeaController::broadcastGenome()
{
    if ( _wm->isAlive() == true )  	// only if agent is active (ie. not just revived) and deltaE>0.
    {
        for( int i = 0 ; i < _wm->_cameraSensorsNb; i++)
        {
            int targetIndex = _wm->getObjectIdFromCameraSensor(i);
            
            if ( targetIndex >= gRobotIndexStartOffset )   // sensor ray bumped into a robot : communication is possible
            {
                targetIndex = targetIndex - gRobotIndexStartOffset; // convert image registering index into robot id.
                
                DemoMedeaController* targetRobotController = dynamic_cast<DemoMedeaController*>(gWorld->getRobot(targetIndex)->getController());
                
                if ( ! targetRobotController )
                {
                    std::cerr << "Error from robot " << _wm->getId() << " : the observer of robot " << targetIndex << " is not compatible" << std::endl;
                    exit(-1);
                }
                
                float dice = float(rand()%100) / 100.0;
                float sigmaSendValue = _currentSigma;
                
                if ( dice <= DemoMedeaSharedData::gProbaMutation )
                {
                    dice = float(rand() %100) / 100.0;
                    if ( dice < 0.5 )
                    {
                        sigmaSendValue = _currentSigma * ( 1 + DemoMedeaSharedData::gUpdateSigmaStep ); // increase sigma
                        
                        if (sigmaSendValue > DemoMedeaSharedData::gSigmaMax)
                        {
                            sigmaSendValue = DemoMedeaSharedData::gSigmaMax;
                        }
                    }
                    else
                    {
                        sigmaSendValue = _currentSigma * ( 1 - DemoMedeaSharedData::gUpdateSigmaStep ); // decrease sigma
                        
                        if ( sigmaSendValue < DemoMedeaSharedData::gSigmaMin )
                        {
                            sigmaSendValue = DemoMedeaSharedData::gSigmaMin;
                        }
                    }
                }
                
                targetRobotController->storeGenome(_currentGenome, _wm->getId(), _birthdate, sigmaSendValue); // other agent stores my genome.
            }
        }
    }
}

void DemoMedeaController::loadNewGenome()
{
    if ( _wm->isAlive() || gEnergyRefill )
    {
        // Logging
        std::string s = "{" + std::to_string(gWorld->getIterations()) + "} [" + std::to_string(_wm->getId()) + "::" + std::to_string(_birthdate) + "] [energy:" +  std::to_string(_wm->getEnergyLevel()) + "] [genomeList:" + std::to_string(_genomesList.size()) + "]\n";
        gLogManager->write(s);
        gLogManager->flush();
        
        // note: at this point, agent got energy, whether because it was revived or because of remaining energy.
        
        if (_genomesList.size() > 0)
        {
            // case: 1+ genome(s) imported, random pick.
            
            selectRandomGenome();
            
            _wm->setAlive(true);
            if ( _wm->getEnergyLevel() == 0 )
                _wm->setEnergyLevel(gEnergyInit);
            _wm->setRobotLED_colorValues(255, 0, 0);
            
        }
        else
        {
            // case: no imported genome - wait for new genome.
            
            // Logging
            std::string s = std::string("");
            s += "{" + std::to_string(gWorld->getIterations()) + "} [" + std::to_string(_wm->getId()) + "::" + std::to_string(_birthdate) + "] no_genome.\n";
            gLogManager->write(s);
            gLogManager->flush();
            
            resetRobot(); // destroy then create a new NN
            
            _wm->setAlive(false); // inactive robot *must* import a genome from others (ie. no restart).
            _wm->setRobotLED_colorValues(0, 0, 255);
        }
        
        // log the genome
        
        if ( _wm->isAlive() )
        {
            // Logging
            std::string s = std::string("");
            s += "{" + std::to_string(gWorld->getIterations()) + "} [" + std::to_string(_wm->getId()) + "::" + std::to_string(_birthdate) + "] new_genome: ";
            for(unsigned int i=0; i<_genome.size(); i++)
            {
                s += std::to_string(_genome[i]) + " ";
                //gLogFile << std::fixed << std::showpoint << _wm->_genome[i] << " ";
            }
            s += "\n";
            gLogManager->write(s);
            gLogManager->flush();
        }
    }
}

