/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */



#ifndef SANDBOXWORLDOBSERVER_H
#define SANDBOXWORLDOBSERVER_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"

#include "Observers/WorldObserver.h"

class World;

class SandboxWorldObserver : public WorldObserver
{
	protected:
		
	public:
		SandboxWorldObserver( World *__world );
		~SandboxWorldObserver();
				
		void reset();
		void step();
		
};

#endif

