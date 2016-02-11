#if defined PRJ_SELFASSEMBLYMECHANISMS || !defined MODULAR

#include "Config/SelfAssemblyMechanismsConfigurationLoader.h"

#include "SelfAssemblyMechanisms/include/SelfAssemblyMechanismsWorldObserver.h"
#include "SelfAssemblyMechanisms/include/SelfAssemblyMechanismsAgentObserver.h"
#include "SelfAssemblyMechanisms/include/SelfAssemblyMechanismsController.h"
#include "SelfAssemblyMechanisms/include/SelfAssemblyMechanismsPredatorController.h"
#include "SelfAssembly/WorldModels/GroupRobotWorldModel.h"
#include "SelfAssembly/GroupRobot.h"
#include "Agents/Predator.h"

SelfAssemblyMechanismsConfigurationLoader::SelfAssemblyMechanismsConfigurationLoader()
{
	// create the single instance of Agent-World Interface.
}

SelfAssemblyMechanismsConfigurationLoader::~SelfAssemblyMechanismsConfigurationLoader()
{
	//nothing to do
}

WorldObserver* SelfAssemblyMechanismsConfigurationLoader::make_WorldObserver(World* wm)
{
	return new SelfAssemblyMechanismsWorldObserver(wm);
}

RobotWorldModel* SelfAssemblyMechanismsConfigurationLoader::make_RobotWorldModel()
{
	return new GroupRobotWorldModel();
}

AgentObserver* SelfAssemblyMechanismsConfigurationLoader::make_AgentObserver(RobotWorldModel* wm)
{
	return new SelfAssemblyMechanismsAgentObserver(wm);
}

Controller* SelfAssemblyMechanismsConfigurationLoader::make_Controller(RobotWorldModel* wm)
{
	return new SelfAssemblyMechanismsController(wm);
}

Robot* SelfAssemblyMechanismsConfigurationLoader::make_Robot(World* wm){
	return new GroupRobot(wm);
}

Predator* SelfAssemblyMechanismsConfigurationLoader::make_Predator(World* wm) {
	return new Predator(wm);
}

SelfAssemblyMechanismsPredatorController* SelfAssemblyMechanismsConfigurationLoader::make_PredatorController(RobotWorldModel* wm) {
	return new SelfAssemblyMechanismsPredatorController(wm);
}

#endif
