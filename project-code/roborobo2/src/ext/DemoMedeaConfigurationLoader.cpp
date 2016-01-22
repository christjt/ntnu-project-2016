#if defined PRJ_DEMOMEDEA || !defined MODULAR

#include "Config/DemoMedeaConfigurationLoader.h"

#include "DemoMedea/include/DemoMedeaWorldObserver.h"
#include "DemoMedea/include/DemoMedeaAgentObserver.h"
#include "DemoMedea/include/DemoMedeaController.h"

#include "WorldModels/RobotWorldModel.h"

DemoMedeaConfigurationLoader::DemoMedeaConfigurationLoader()
{
}

DemoMedeaConfigurationLoader::~DemoMedeaConfigurationLoader()
{
	//nothing to do
}

WorldObserver* DemoMedeaConfigurationLoader::make_WorldObserver(World* wm)
{
	return new DemoMedeaWorldObserver(wm);
}

RobotWorldModel* DemoMedeaConfigurationLoader::make_RobotWorldModel()
{
	return new RobotWorldModel();
}

AgentObserver* DemoMedeaConfigurationLoader::make_AgentObserver(RobotWorldModel* wm)
{
	return new DemoMedeaAgentObserver(wm);
}

Controller* DemoMedeaConfigurationLoader::make_Controller(RobotWorldModel* wm)
{
	return new DemoMedeaController(wm);
}

#endif
