/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */


#ifndef BASICPROJECTWORLDOBSERVER_H
#define BASICPROJECTWORLDOBSERVER_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"

#include "Observers/WorldObserver.h"

class World;

class BasicProjectWorldObserver : public WorldObserver
{
	protected:
		
	public:
		BasicProjectWorldObserver( World *__world );
		~BasicProjectWorldObserver();
				
		void reset();
		void step();
		
};

#endif

