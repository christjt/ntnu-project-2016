/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */



#ifndef SANDBOXCONTROLLER_H
#define SANDBOXCONTROLLER_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"

#include "Controllers/Controller.h"

#include "WorldModels/RobotWorldModel.h"

class SandboxController : public Controller
{
	public:
		//Initializes the variables
		SandboxController( RobotWorldModel *__wm );
		~SandboxController();
		
		void reset();
		void step();
};


#endif

