/*
 * BasicProjectConfigurationLoader.h
 */

#ifndef BASICPROJECTCONFIGURATIONLOADER_H
#define	BASICPROJECTCONFIGURATIONLOADER_H

#include "Config/ConfigurationLoader.h"

class BasicProjectConfigurationLoader : public ConfigurationLoader
{
	public:
		BasicProjectConfigurationLoader();
		~BasicProjectConfigurationLoader();

		WorldObserver *make_WorldObserver(World* wm) ;
		RobotWorldModel *make_RobotWorldModel();
		AgentObserver *make_AgentObserver(RobotWorldModel* wm) ;
		Controller *make_Controller(RobotWorldModel* wm) ;
};

#endif
