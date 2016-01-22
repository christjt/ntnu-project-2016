/*
 * MedeaConfigurationLoader.h
 */

#ifndef DEMOMEDEACONFIGURATIONLOADER_H
#define DEMOMEDEACONFIGURATIONLOADER_H

#include "Config/ConfigurationLoader.h"


class DemoMedeaConfigurationLoader : public ConfigurationLoader
{
	private:

	public:
		DemoMedeaConfigurationLoader();
		~DemoMedeaConfigurationLoader();

		WorldObserver *make_WorldObserver(World* wm) ;
		RobotWorldModel *make_RobotWorldModel();
		AgentObserver *make_AgentObserver(RobotWorldModel* wm) ;
		Controller *make_Controller(RobotWorldModel* wm) ;
};



#endif
