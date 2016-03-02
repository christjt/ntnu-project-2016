/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */
 
#ifndef SELFASSEMBLYMECHANISMSAGENTOBSERVER_H
#define SELFASSEMBLYMECHANISMSAGENTOBSERVER_H 

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"
#include "WorldModels/RobotWorldModel.h"
#include "Observers/AgentObserver.h"

class SelfAssemblyMechanismsAgentObserver : public AgentObserver
{
	private:
		int robotLifetime;

	public:
		SelfAssemblyMechanismsAgentObserver( );
		SelfAssemblyMechanismsAgentObserver( RobotWorldModel *__wm );
		~SelfAssemblyMechanismsAgentObserver();

		int getLifetime(){ return robotLifetime; };
				
		void reset();
		void step();
		
};


#endif

