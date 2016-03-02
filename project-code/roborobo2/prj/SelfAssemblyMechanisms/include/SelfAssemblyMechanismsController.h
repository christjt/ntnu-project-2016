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
		int messageWidth;
		std::shared_ptr<NetworkTranslator> translator;
		std::shared_ptr<DoubleVectorGenotypeTranslator> genomeTranslator;
		void updateSensorValues();
		void findNearbyRobots(std::vector<GroupRobotWorldModel*>& dest);
		void updateMessageInput();
		void updateConnectionInput();
		void applyTranslationOutput();
		void applyRotationalOutput();
		void applyMessageOutput();
		void applyConnectionOutput(const std::vector<GroupRobotWorldModel*>& nearbyRobots);
	public:
		//Initializes the variables
		SelfAssemblyMechanismsController( RobotWorldModel *__wm );
		~SelfAssemblyMechanismsController();
		bool done = false;
		void reset();
		void step();
		std::shared_ptr<DoubleVectorGenotypeTranslator> getGenomeTranslator()
		{
			return genomeTranslator;
		}
};


#endif

