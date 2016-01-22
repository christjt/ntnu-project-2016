/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */


 
#ifndef SANDBOXAGENTOBSERVER_H
#define SANDBOXAGENTOBSERVER_H 

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"
#include "WorldModels/RobotWorldModel.h"
#include "Observers/AgentObserver.h"

class SandboxAgentObserver : public AgentObserver
{
	public:
		SandboxAgentObserver( );
		SandboxAgentObserver( RobotWorldModel *__wm );
		~SandboxAgentObserver();
				
		void reset();
		void step();
		
};


#endif

