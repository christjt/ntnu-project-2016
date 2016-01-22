/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */



#ifndef BASICPROJECTCONTROLLER_H
#define BASICPROJECTCONTROLLER_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"

#include "Controllers/Controller.h"

#include "WorldModels/RobotWorldModel.h"

class BasicProjectController : public Controller
{
	public:
		//Initializes the variables
		BasicProjectController( RobotWorldModel *__wm );
		~BasicProjectController();
		
		void reset();
		void step();
};


#endif

