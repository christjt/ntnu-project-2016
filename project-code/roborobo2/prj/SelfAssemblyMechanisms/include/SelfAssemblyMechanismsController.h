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
#include "NetworkTranslator.h"
#include "DoubleVectorGenomeTranslator.h"
class SelfAssemblyMechanismsController : public Controller
{

	private:
		GroupRobotWorldModel* wm;
		NetworkTranslator* translator;
		DoubleVectorGenotypeTranslator* genomeTranslator;
		int messageWidth;
	public:
		//Initializes the variables
		SelfAssemblyMechanismsController( RobotWorldModel *__wm );
		~SelfAssemblyMechanismsController();
		bool done = false;
		void reset();
		void step();
		DoubleVectorGenotypeTranslator* getGenomeTranslator()
		{
			return genomeTranslator;
		}
};


#endif

