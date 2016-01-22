/*
 * AggregateConfigurationLoader.h
 */

#ifndef AGGREGATECONFIGURATIONLOADER_H
#define	AGGREGATECONFIGURATIONLOADER_H

#include "Config/ConfigurationLoader.h"

class AggregateConfigurationLoader : public ConfigurationLoader
{
	public:
		AggregateConfigurationLoader();
		~AggregateConfigurationLoader();

		WorldObserver *make_WorldObserver(World* wm) ;
		RobotWorldModel *make_RobotWorldModel();
		AgentObserver *make_AgentObserver(RobotWorldModel* wm) ;
		Controller *make_Controller(RobotWorldModel* wm) ;
};

#endif
