/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */
 
#ifndef AGGREGATEAGENTOBSERVER_H
#define AGGREGATEAGENTOBSERVER_H 

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"
#include "WorldModels/RobotWorldModel.h"
#include "Observers/AgentObserver.h"

class AggregateAgentObserver : public AgentObserver
{
	public:
		AggregateAgentObserver( );
		AggregateAgentObserver( RobotWorldModel *__wm );
		~AggregateAgentObserver();
				
		void reset();
		void step();
		
};


#endif

