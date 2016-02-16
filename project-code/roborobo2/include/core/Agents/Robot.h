/*
 *  Robot.h
 *  roborobo
 *
 *  Created by Nicolas on 17/12/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef ROBOT_H
#define ROBOT_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"
#include "Agents/Agent.h"

#include "Utilities/Graphics.h"

#include "Controllers/Controller.h"
#include "Observers/Observer.h"
#include "Observers/WorldObserver.h"
#include "Observers/AgentObserver.h"
#include "WorldModels/RobotWorldModel.h"
#include "WorldModels/RobotWorldModel.h"
#include "World/World.h"

// *** begin: add new includes here ***

#include "Observers/Observer.h"


#include "Agents/Agent.h"

// *** end ***


class World;

class Robot : public Agent
{
	
	private:

        int _groupId; // used for seperating populations
    
		// real displacement (x/y format, delta applied to real coordinates (_xReal,_yReal))
		double _xDeltaReal;
		double _yDeltaReal;
	
		double _lastAgentAbsoluteOrientation; // backup in case of collision

		int _iterations;

        int castSensorRay(SDL_Surface * image, double x1, double y1, double * x2pt, double * y2pt , int __maxValue = -1);
    
        void initRobotPhysics( );


	protected:
		RobotWorldModel *_wm;

		Controller *_controller;
		AgentObserver *_agentObserver;

		bool _isPredator;

		void traceRayRGBA(SDL_Surface * dst, int x1, int y1, int x2, int y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a); // for screen rendering only
		virtual void applyRobotPhysics( );

		void initWorldModel(RobotWorldModel *_wm, World *__world);
		void initSensors(RobotWorldModel *_wm);
		void initRegisterSensors(RobotWorldModel *_wm);


	public:
		//Initializes the variables
		Robot();
		Robot( World *__world );
		virtual ~Robot();

		void reset();

		virtual void stepBehavior();
		virtual void stepBehavior(Uint8* __keyboardStates);
		virtual void applyDynamics();
		void callObserver(); // call the embedded genetic engine -- always called before stepBehavior.

		 // use transl/rot delta to compute x/y delta.

		//Moves the agent
		virtual void move( int __recursiveIt = 0 );
		
		virtual void show();

		bool isCollision();

		void setIsPredator(bool isPredator){ _isPredator = isPredator; };

		bool getIsPredator(){ return _isPredator; };

		void setCoordReal (int __x, int __y); // agent is centered on point
		
		virtual void registerRobot();
		virtual void unregisterRobot();
		
		void behaviorUpdate_remoteController(Uint8* __keyStates);

        Controller* getController() { return _controller; }

		void setController(Controller* controller){ _controller = controller; }

        AgentObserver* getObserver() { return _agentObserver; }
		WorldObserver* getWorldObserver();
        RobotWorldModel* getWorldModel() { return _wm; }
    
		void displayInfo(); // display input/output values on console. (used for inspect agent mode, cf. help on console) -- keep it simple: one line only.

		
		// return a list of agents in the vincinity (ie. in the communication area)
		// the content of this list depends on the max communication range (see properties file).
		// works only if communication network is active.
		/* std::vector<int> getNeighbors(); */
};



#endif /* ROBOTAGENT_H */


