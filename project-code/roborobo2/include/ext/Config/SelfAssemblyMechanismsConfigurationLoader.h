/*
 * SelfAssemblyMechanismsConfigurationLoader.h
 */

#ifndef SELFASSEMBLYMECHANISMSCONFIGURATIONLOADER_H
#define	SELFASSEMBLYMECHANISMSCONFIGURATIONLOADER_H

#include "Config/ConfigurationLoader.h"

#include "SelfAssemblyMechanisms/include/SelfAssemblyMechanismsPredatorController.h"

#include "Agents/Predator.h"

class SelfAssemblyMechanismsConfigurationLoader : public ConfigurationLoader
{
	public:
		SelfAssemblyMechanismsConfigurationLoader();
		~SelfAssemblyMechanismsConfigurationLoader();

		WorldObserver *make_WorldObserver(World* wm) ;
		RobotWorldModel *make_RobotWorldModel();
		AgentObserver *make_AgentObserver(RobotWorldModel* wm) ;
		Controller *make_Controller(RobotWorldModel* wm) ;
		SelfAssemblyMechanismsPredatorController *make_PredatorController(RobotWorldModel* vm);
		Predator *make_Predator(World* wm);
		Robot *make_Robot(World* wm);
};

#endif
