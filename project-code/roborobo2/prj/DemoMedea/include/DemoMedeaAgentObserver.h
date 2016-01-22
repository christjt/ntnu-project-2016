/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 * NNlib: Leo Cazenille <leo.cazenille@upmc.fr>
 */


#ifndef DEMOMEDEAAGENTOBSERVER_H
#define DEMOMEDEAAGENTOBSERVER_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"
#include "Observers/AgentObserver.h"
#include "WorldModels/RobotWorldModel.h"
#include "DemoMedea/include/DemoMedeaSharedData.h"

#include <iomanip>

class DemoMedeaAgentObserver : public AgentObserver
{
	public:
		DemoMedeaAgentObserver(RobotWorldModel *wm);
		~DemoMedeaAgentObserver();

		void reset();
		void step();

};

#endif

