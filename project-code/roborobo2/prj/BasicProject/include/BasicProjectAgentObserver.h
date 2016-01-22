/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */
 
#ifndef BASICPROJECTAGENTOBSERVER_H
#define BASICPROJECTAGENTOBSERVER_H 

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"
#include "WorldModels/RobotWorldModel.h"
#include "Observers/AgentObserver.h"

class BasicProjectAgentObserver : public AgentObserver
{
	public:
		BasicProjectAgentObserver( );
		BasicProjectAgentObserver( RobotWorldModel *__wm );
		~BasicProjectAgentObserver();
				
		void reset();
		void step();
		
};


#endif

