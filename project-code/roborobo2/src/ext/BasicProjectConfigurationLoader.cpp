#if defined PRJ_BASICPROJECT || !defined MODULAR

#include "Config/BasicProjectConfigurationLoader.h"

#include "BasicProject/include/BasicProjectWorldObserver.h"
#include "BasicProject/include/BasicProjectAgentObserver.h"
#include "BasicProject/include/BasicProjectController.h"

#include "WorldModels/RobotWorldModel.h"


BasicProjectConfigurationLoader::BasicProjectConfigurationLoader()
{
	// create the single instance of Agent-World Interface.
}

BasicProjectConfigurationLoader::~BasicProjectConfigurationLoader()
{
	//nothing to do
}

WorldObserver* BasicProjectConfigurationLoader::make_WorldObserver(World* wm)
{
	return new BasicProjectWorldObserver(wm);
}

RobotWorldModel* BasicProjectConfigurationLoader::make_RobotWorldModel()
{
	return new RobotWorldModel();
}

AgentObserver* BasicProjectConfigurationLoader::make_AgentObserver(RobotWorldModel* wm)
{
	return new BasicProjectAgentObserver(wm);
}

Controller* BasicProjectConfigurationLoader::make_Controller(RobotWorldModel* wm)
{
	return new BasicProjectController(wm);
}


#endif
