/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */
 
#ifndef SELFASSEMBLYMECHANISMSAGENTOBSERVER_H
#define SELFASSEMBLYMECHANISMSAGENTOBSERVER_H 

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"
#include "WorldModels/RobotWorldModel.h"
#include "Observers/AgentObserver.h"
#include "SelfAssembly/WorldModels/GroupRobotWorldModel.h"
#include "SelfAssemblyMechanisms/include/Logger/StatisticsLogger.h"

class SelfAssemblyMechanismsAgentObserver : public AgentObserver
{
	private:
		int robotLifetime;
		std::vector<std::pair<Robot*, double>> findPredators();
		StatisticsLogger* logger;
	public:
		SelfAssemblyMechanismsAgentObserver( );
		SelfAssemblyMechanismsAgentObserver( RobotWorldModel *__wm );
		~SelfAssemblyMechanismsAgentObserver();

		int getLifetime(){ return robotLifetime; };
				
		void reset();
		void step();
		
};


#endif

