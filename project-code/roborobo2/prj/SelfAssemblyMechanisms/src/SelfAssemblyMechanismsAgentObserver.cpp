/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */

#include "SelfAssemblyMechanisms/include/SelfAssemblyMechanismsAgentObserver.h"
#include "SelfAssembly/WorldModels/GroupRobotWorldModel.h"
#include "SelfAssemblyMechanisms/include/SelfAssemblyMechanismsSharedData.h"


SelfAssemblyMechanismsAgentObserver::SelfAssemblyMechanismsAgentObserver( )
{
}

SelfAssemblyMechanismsAgentObserver::SelfAssemblyMechanismsAgentObserver( RobotWorldModel *__wm )
{
	_wm = __wm;
    _wm->setEnergyLevel(gEnergyInit);
    robotLifetime = 0;
}

SelfAssemblyMechanismsAgentObserver::~SelfAssemblyMechanismsAgentObserver()
{
	// nothing to do.
}

void SelfAssemblyMechanismsAgentObserver::reset()
{
    robotLifetime = 0;
}

void SelfAssemblyMechanismsAgentObserver::step()
{
    if(_wm->isAlive()){
        robotLifetime++;
    }

    bool isPredator = ((GroupRobotWorldModel*)_wm)->getWorld()->getRobot(_wm->getId())->getIsPredator();
    if(!isPredator){
        auto wm = (GroupRobotWorldModel*)_wm;
        if(wm->getGroup()->size() >= 3)
        {
            auto nearbyPredators = findPredators();
            for(auto& predator: nearbyPredators)
            {
                if(predator.second <= 5 )
                {
                    auto predatorWm = predator.first->getWorldModel();
                    predatorWm->setAlive(false);
                    predator.first->unregisterRobot();
                    _wm->_world->unregisterRobot(predatorWm->getId());
                    for(auto it = wm->getGroup()->begin(); it != wm->getGroup()->end(); it++)
                    {
                        (*it).second->addEnergy(500);
                    }
                }
            }
        }
    }


    if(_wm->getEnergyLevel() > 0 && !isPredator)
    {
        _wm->substractEnergy(SelfAssemblyMechanismsSharedData::gPassiveEnergyDrain);
        if(((GroupRobotWorldModel*)_wm)->getGroup()->size() > 1){
            _wm->substractEnergy(SelfAssemblyMechanismsSharedData::gConnectionEnergyDrain);
        }
        if(_wm->getEnergyLevel() <= 0){
            for(auto connection: (((GroupRobotWorldModel*)_wm)->getConnectionMechanism().getConnections())) {
                ((GroupRobotWorldModel*)_wm)->disconnectFrom(connection.first);
            }
            _wm->setAlive(false);
        }


    }
    // through distance sensors
    for( int i = 0 ; i < _wm->_cameraSensorsNb; i++)
    {
        int targetIndex = _wm->getObjectIdFromCameraSensor(i);
      //  std::cout << "target Index" << std::endl;
        if ( targetIndex >= gPhysicalObjectIndexStartOffset && targetIndex < gRobotIndexStartOffset )   // sensor ray bumped into a physical object
        {
            targetIndex = targetIndex - gPhysicalObjectIndexStartOffset;
            //std::cout << "[DEBUG] Robot #" << _wm->getId() << " touched " << targetIndex << "\n";
            gPhysicalObjects[targetIndex]->isTouched(_wm->getId());

        }

    }
    
    // through floor sensor
    int targetIndex = _wm->getGroundSensorValue();
    if ( targetIndex >= gPhysicalObjectIndexStartOffset && targetIndex < gPhysicalObjectIndexStartOffset + (int)gPhysicalObjects.size() )   // ground sensor is upon a physical object (OR: on a place marked with this physical object footprint, cf. groundsensorvalues image)
    {
        targetIndex = targetIndex - gPhysicalObjectIndexStartOffset;
        //std::cout << "[DEBUG] #" << _wm->getId() << " walked upon " << targetIndex << "\n";
        gPhysicalObjects[targetIndex]->isWalked(_wm->getId());
    }
}

std::vector<std::pair<Robot*, double>> SelfAssemblyMechanismsAgentObserver::findPredators()
{
    std::vector<std::pair<Robot*, double>> predators;
    for(int i = 0; i < _wm->_cameraSensorsNb; i++)
    {

        if(_wm->getDistanceValueFromCameraSensor(i) >= gSensorRange)
        {
            continue;
        }

        int objectId = _wm->getObjectIdFromCameraSensor(i);
        bool isOtherRobot =  Agent::isInstanceOf(objectId);
        if(!isOtherRobot){
            continue;
        }
        int id = objectId - gRobotIndexStartOffset;
        auto robot = _wm->getWorld()->getRobot(id);
        if(!robot->getIsPredator())
            continue;
        predators.push_back(std::make_pair(robot, _wm->getDistanceValueFromCameraSensor(i)));

    }

    return predators;
}
