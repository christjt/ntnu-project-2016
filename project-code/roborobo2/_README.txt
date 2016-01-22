=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
=-=-=-=-=-=-=-=-=-=-=-= ROBOROBO.2=-=-=-=-=-=-=
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
=- 2008-2014 -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
-=-=-=-= nicolas.bredeche(at)upmc.fr -=-=-=-=-=
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

How to know about current version and target build? Launch "roborobo -v" in the console.

Check _INSTALL.TXT for installation guide.

Check _FAQ.TXT for trouble shooting.

Check this file for anything else.


==== QUICK START : COMPILING AND RUNNING ROBOROBO ====

>>> Check _INSTALL.TXT <<<


==== DESCRIPTION ====

Roborobo! is a fast and simple 2D mobile robot simulator written in C++ loosely based on a khepera/epuck model. It is targeted for fast single and multi-robots simulation (primary motivation is evolutionary robotics et swarm/collective robotics). Its dependencies to external libraries are kept to the minimum (SDL 1.2, SDL_IMAGE 1.2 and BOOST) and the code rely on a simple philosophy: "Keep it simple". It can be compiled with a simple Makefile. And new projects can be introduced quickly and easily. Any new project can be created in a dedicated location in the prj/ directory, without any modifications to the roborobo core.

Some random bits of information:
- Robot position and mouvement are real-valued (ie. precise)
- Collision is performed on a pixel-based information for fast speed (ie. fast but not precise)
- Robot-robot collision can be switched off (faster, less accurate)
- both GUI mode and batch mode are available. Note that batch mode is the fastest mode (gBatchMode=true, gVerbose=false).
- only one external dependencies: SDL library (multi-platform fast 2D library).
- most parameters are to be found in the config subdirectory (e.g. default.properties)
- full environment and robot specifications can set up directly with an image editor (check data directories). E.g. Robot proximity sensor positions are set up in the robot image. 
- the very first version of roborobo! can be found here: http://neuronik.free.fr/nemelith/?p=67 (it is quite different as it was first a game sort-of experience, eventhough i already had roborobo! in mind). An included html help file describes the overall idea behind parameterization through image files (some modifications may have occured since then).
- you can specify a properties file as command line option (see "./roborobo -h" for help)
- you can easily clone project with the clone_project.py script in the prj/ directory. 
- by defaut, two demos are available: random walker and environment-driven evolutionary robotics (mEDEA algorithm [Bredeche, Montanier, PPSN 2009]).

The current version is Roborobo.2 (since 2014). Compared to version 1, it requires Boost as dependencies (in addition to SDL 1.2 and SDL_IMAGE 1.2), it has been quite heavely modified, and is *much* faster than the previous version.


==== CREDITS ====

roborobo!: 
 - main developper: nicolas.bredeche(at)upmc.fr
included contributions:
 - the Properties class from Evert Haasdijk (VU Amsterdam)
 - box-muller algorithm from Everett F. Carter Jr. (1994) - ref: http://www.taygeta.com/random/gaussian.html
 - other contribs are mentionned in the code (check: core/Misc.h and contrib/*)
 - past contributor(s): Jean-Marc Montanier, Leo Cazenille, Pierre Delarboulas


==== CITING ROBOROBO ====

If you use roborobo in your work, please cite the following paper:

N. Bredeche, J.-M. Montanier, B. Weel, and E. Haasdijk. Roborobo! a fast robot simulator for swarm and collective robotics. CoRR, abs/1304.2888, 2013. 

@article{roborobo,
  author    = {Nicolas Bredeche and Jean-Marc Montanier and Berend Weel and Evert Haasdijk},
  title     = {Roborobo! a Fast Robot Simulator for Swarm and Collective Robotics},
  journal   = {CoRR},
  volume    = {abs/1304.2888},
  year      = {2013},
  ee        = {http://arxiv.org/abs/1304.2888},
  bibsource = {DBLP, http://dblp.uni-trier.de}
}

The paper is available on Arxiv: http://arxiv.org/abs/1304.2888 


=================================
==== DEVELOPER'S QUICK START ====
=================================

** QUICK OVERVIEW **

The philosophy is that in the standard case, the designer should be able to code the agent behavior (the ''Controller'') and to access both the world and agents states in a seperate fashion (''World'' and ''Agent'' observers). The world and agents observers are run before the actual agent behavioral update, meaning that the observers do observe a ''stable'' snapshot of the environment. Then, agent behavioral update are performed in turn-based fashion (ie. asynchroneous), to deal with possible collision. While roborobo is turn-based, the update order of robots is randomized between each updates of the world (to avoid deleterious effects due to ordering).

- WorldObserver: object dealing with world level, used for accessing state of the world, including all agents (methods: reset and step).
- AgentObserver: object dealing with agent level, used for accessing state of agent. All agent observers are called before behavior update (methods: reset and step)
	=> Observers are really useful for monitoring, logging, computing fitness updates, managing off-line evolutionary optimization, etc.
- Controller: object dealing with behavior at the robot level (useful methods: init and reset)
- *WorldModel: object where the (robot) world model is stored. May or may not be extended depending on your needs.

From the Controllers, you can access the world and robot(s) world-models. All the rest is simulator-specific implementation.
- of course, you may want to create a new properties file in the config sub-directory

About the simulation update method scheme:
	- AgentObserver is called N times per iterations (N = nb of agents)
	- WorldObserver is called once per iterations
	- Update method: turn-based, synchroneous and shuffle-ordered update method.
		- update method call sequence: WorldObserver => N_a * agentObservers => (N_e * energyPoints update) => N_a * agent steps => N_a agent moves
			- worldObserver is called *before* agentObservers, agentObservers are all called *before* agent.stepBehavior
			- environment physics and actual moving of agents are performed in a row *after* all agent.stepBehavior has been called
			- Agent position movements is performed using synchroneous position updates. Hence, solving collisions is robust to agent index ordering
		- the update ordering is shuffled for each new world iterations, ie. agent indexes are shuffled (to avoid update ordering nasty effects accross time)
			- a typical problem if shuffling is not done is that agents with low indexes always act and move first, hence a big survival advantage.
			- however, agentObservers and agent.stepBehavior are called in the same order (ie. no re-shuffling)
	- WorldModel: contains all information on on agent, ie. its representation of the outside world, including its own status (e.g. energy level).
		- in practical, neither controlarchitecture or observers should contain general agent-related information. All should be stored in the worldmodel.

The best way to learn is to practice. Clone an existing project and toy with it. See next paragraph to start playing.


** QUICK START : SETTING UP A NEW PROJECT **

- clone an existing project with the ./prj/clone_project.py python script.
- (Linux:) update your makefile with the ./makefile-manager script.
- (MacOSX:) update XCode project to include the newly created files.
- create a dedicated properties file in the ./config/ directory.
- (Linux and MacOSX): build, then run roborobo with your newly created properties file as parameter (program parameter: "-l config/<mypropertiesfile.properties>").


** METHODOLOGY GUIDELINES **

- Any new project should start, *and be limited to*, a specific sub-directory in prj/, with both an include/ and src/ sub-directories. E.g. ./prj/MyProject/[include&src].
- Observers should be understood as "deals with everything that happens inbetween two lifetimes" while Behavior should be understood as "everything that happens during lifetime".

A last remark: roborobo! is not exactly the paragon of Clean Coding philosophy as it was originaly, and still is, a single-coder-in-a-very-big-hurry short term project. While I tried to keep the code clean, there are several do-as-i-say-not-as-i-do features (lack of accessing methods, etc.). Hence, roborobo! may not be the best starting point for developping your homebrew robot simulator. However, it can still be pretty useful if you just intend to extend it for a particular application (e.g. a specific swarm mobile robotics environment and simulation), and it has proven to be quite useful for several published works in the last few years, from several authors and places (Paris, Orsay, Nancy, Amsterdam, etc.).


** DIRECTORY STRUCTURE **

- prj    : project locations, each project is indenpendant, and may be seen as a special instance of roborobo - parameterized through ConfigurationLoader and .properties file.
- core   : core roborobo! code. Contains the elementary elements for running roborobo.
- ext    : derived class and extensions for roborobo! code, which may be of global interest. It contains addition to roborobo core, including all code that can be factorised from projects (ie. re-usable code, such as e.g. neural nets, logger), as well as project specific code.
- contrib: imported code with useful features.
- log    : log files.
- data   : contains image files.
- config : contains properties files.


** CONTENT OF ./DATA/ : IMAGES OF ROBOTS AND ENVIRONMENT **

Environments and robots are all described as images. 

IMPORTANT: USE ONLY UNCOMPRESSED FORMAT!

gAgentMaskFilename				: the agent as how it is displayed and used for collision.
gAgentSpecsFilename				: the agent specification regarding proximity sensor (location and orientation).
gForegroundImageFilename 		: the environment decorative image, ie. only used for displaying -- should more or less match environment image.
gEnvironmentImageFilename  		: the environment description image. 
									R component is unused
									G component is used to determine agent #G starting position (if more than one pixel with same G value, choose the most upper-left), 
									B component is used to determine object type.
									obstacle (and agent) Id ("type") are returned by proximity sensors. 0..255: #obstacle, 1000..1256..+++: #agent
									R=255 means "no obstacle", G=255 means nothing, ie.: pure white means "no obstacle"
									(!) use png to avoid pixel exact color loss
									note that the sensor beam lenght parameter is set in the config file.
gBackgroundImageFilename  		: this image is purely decorative. Change parralax factor for faster scrolling (if screen size is smaller that environment/foreground size).
gGroundSensorImageFilename: this image specifies the footprint value that will be sensed by the ground sensor.

Some image files are available by default in the data subdirectory. Here's a quick summary (but you may add anything you like):
- agent*: a 32x32 robot image, with 8 sensors (khepera-like)
- miniagent*: a 5x5 robot image, with 8 sensors (sensor belt)


[-n].