/*
 * SelfAssemblyMechanismsConfigurationLoader.h
 */

#ifndef SELFASSEMBLYMECHANISMSCONFIGURATIONLOADER_H
#define	SELFASSEMBLYMECHANISMSCONFIGURATIONLOADER_H

#include "Config/ConfigurationLoader.h"

class SelfAssemblyMechanismsConfigurationLoader : public ConfigurationLoader
{
	public:
		SelfAssemblyMechanismsConfigurationLoader();
		~SelfAssemblyMechanismsConfigurationLoader();

		WorldObserver *make_WorldObserver(World* wm) ;
		RobotWorldModel *make_RobotWorldModel();
		AgentObserver *make_AgentObserver(RobotWorldModel* wm) ;
		Controller *make_Controller(RobotWorldModel* wm) ;
};

#endif
