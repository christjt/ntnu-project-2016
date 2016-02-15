/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */



#ifndef SELFASSEMBLYMECHANISMSCONTROLLER_H
#define SELFASSEMBLYMECHANISMSCONTROLLER_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"

#include "Controllers/Controller.h"

#include "WorldModels/RobotWorldModel.h"
#include "SelfAssembly/WorldModels/GroupRobotWorldModel.h"

class SelfAssemblyMechanismsController : public Controller
{
	protected:
		GroupRobotWorldModel* groupWM;
	public:
		//Initializes the variables
		SelfAssemblyMechanismsController( RobotWorldModel *__wm );
		~SelfAssemblyMechanismsController();
		bool done = false;
		void reset();
		void step();
};


#endif

