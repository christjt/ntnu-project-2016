//
// Created by christopher on 11.02.16.
//

#include "Agents/Predator.h"

#include "WorldModels/RobotWorldModel.h"

#include "Config/GlobalConfigurationLoader.h"

Predator::Predator( World *__world )
{
    _wm = new RobotWorldModel(); // TODO: externalize object referenced to create the new instance

    //init world model
    initWorldModel(_wm, __world);

    //init sensors
    initSensors(_wm);


    //register sensors
    initRegisterSensors(_wm);

    _agentObserver = gConfigurationLoader->make_AgentObserver(_wm);		// TODO: externalize
    _controller = gConfigurationLoader->make_PredatorController(_wm);		// TODO: externalize

    reset();
}
