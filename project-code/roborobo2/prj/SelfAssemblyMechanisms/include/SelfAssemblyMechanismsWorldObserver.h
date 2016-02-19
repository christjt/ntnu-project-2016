/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */


#ifndef SELFASSEMBLYMECHANISMSWORLDOBSERVER_H
#define SELFASSEMBLYMECHANISMSWORLDOBSERVER_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"

#include "Observers/WorldObserver.h"

#include "SelfAssemblyMechanisms/include/SelfAssemblyMechanismsSharedData.h"

class World;

class SelfAssemblyMechanismsWorldObserver : public WorldObserver
{
	protected:
		
	public:
		SelfAssemblyMechanismsWorldObserver( World *__world );
		~SelfAssemblyMechanismsWorldObserver();
				
		void reset();
		void step();
		
};

#endif

