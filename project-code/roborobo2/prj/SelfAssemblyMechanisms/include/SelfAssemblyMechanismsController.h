/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */



#ifndef SELFASSEMBLYMECHANISMSCONTROLLER_H
#define SELFASSEMBLYMECHANISMSCONTROLLER_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"

#include "Controllers/Controller.h"

#include "WorldModels/RobotWorldModel.h"

class SelfAssemblyMechanismsController : public Controller
{
	public:
		//Initializes the variables
		SelfAssemblyMechanismsController( RobotWorldModel *__wm );
		~SelfAssemblyMechanismsController();
		
		void reset();
		void step();
};


#endif

