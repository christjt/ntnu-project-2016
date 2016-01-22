#if defined PRJ_AGGREGATE || !defined MODULAR

#include "Config/AggregateConfigurationLoader.h"

#include "Aggregate/include/AggregateWorldObserver.h"
#include "Aggregate/include/AggregateAgentObserver.h"
#include "Aggregate/include/AggregateController.h"

#include "WorldModels/RobotWorldModel.h"


AggregateConfigurationLoader::AggregateConfigurationLoader()
{
	// create the single instance of Agent-World Interface.
}

AggregateConfigurationLoader::~AggregateConfigurationLoader()
{
	//nothing to do
}

WorldObserver* AggregateConfigurationLoader::make_WorldObserver(World* wm)
{
	return new AggregateWorldObserver(wm);
}

RobotWorldModel* AggregateConfigurationLoader::make_RobotWorldModel()
{
	return new RobotWorldModel();
}

AgentObserver* AggregateConfigurationLoader::make_AgentObserver(RobotWorldModel* wm)
{
	return new AggregateAgentObserver(wm);
}

Controller* AggregateConfigurationLoader::make_Controller(RobotWorldModel* wm)
{
	return new AggregateController(wm);
}


#endif
