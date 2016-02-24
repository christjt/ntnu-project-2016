cmake_minimum_required(VERSION 3.3)
project(roborobo2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
include_directories(include/core)
include_directories(include/contrib)
include_directories(include/ext)
include_directories(prj/SelfAssemblyMechanisms/include)
include_directories(prj/)


set(SOURCE_FILES main.cpp prj/SelfAssemblyMechanisms/include/EA/DoubleVectorGenotype.h prj/SelfAssemblyMechanisms/include/SelfAssemblyMechanismsSharedData.h prj/SelfAssemblyMechanisms/include/NetworkFactories/MLPFactory.h prj/SelfAssemblyMechanisms/include/NetworkFactories/NetworkFactory.h prj/Aggregate/include/AggregateSharedData.h prj/Aggregate/include/EA/RouletteWheel.h prj/Aggregate/src/EA/RouletteWheel.cpp prj/Aggregate/include/EA/EvolutionaryAlgorithm.h prj/Aggregate/src/EA/EvolutionaryAlgorithm.cpp prj/Aggregate/include/EA/SigmaScalingSelectionMechanism.h prj/Aggregate/src/EA/SigmaScalingSelectionMechanism.cpp include/ext/SelfAssembly/WorldModels/GroupRobotWorldModel.h src/ext/GroupRobotWorldModel.cpp  src/ext/Vector2.cpp include/ext/Utilities/Vector2.h include/ext/ include/ext/SelfAssembly/RobotGroup.h src/ext/RobotGroup.cpp include/ext/SelfAssembly/RobotGroup.h include/ext/SelfAssembly/ConnectionMechanisms.h include/ext/SelfAssembly/Communication/CommunicationModule.h src/ext/CommunicationModule.cpp include/ext/Utilities/memory.h include/ext/SelfAssembly/ConnectionPort.h src/ext/ConnectionPort.cpp src/ext/Vector2.cpp include/ext/SelfAssembly/GroupRobot.h src/ext/GroupRobot.cpp include/ext/SelfAssembly/GroupRobot.h include/ext/SelfAssembly/Config/PortConfiguration.h include/ext/SelfAssembly/Config/PortFactory.h prj/SelfAssemblyMechanisms/include/GenomeTranslator.h prj/SelfAssemblyMechanisms/include/NetworkTranslator.h prj/SelfAssemblyMechanisms/include/NetworkFactories/NetworkFactory.h prj/SelfAssemblyMechanisms/src/NetworkTranslator.cpp prj/SelfAssemblyMechanisms/include/DoubleVectorGenomeTranslator.h )



add_executable(roborobo2 ${SOURCE_FILES})