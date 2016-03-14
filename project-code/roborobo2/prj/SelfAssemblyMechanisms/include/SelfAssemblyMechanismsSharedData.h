#ifndef ROBOROBO2_SELFASSEMBLYMECHANISMSSHAREDDATA_H
#define ROBOROBO2_SELFASSEMBLYMECHANISMSSHAREDDATA_H

#include <RoboroboMain/roborobo.h>
class SelfAssemblyMechanismsSharedData {
    public:
        static int gEvolutionaryGenerationIterations;
        static int gNScenarios;
        static double gExplorationThreshold;
        static double gExplorationMutationRate;
        static int gTournamentGroupSize;
        static bool gCanEatPredators;
        static double gTournamentPickChance;
        static int gPopulationSize;
        static int gMaxGenerations;
        static int gCrossover;
        static double gMutation;
        static int gElitism;
        static int gNHiddenLayers;
        static double gMutationStep;
        static std::vector<unsigned > gHiddenLayers;
        static double gTargetFitness;
        static int gNNFactory;
        static std::string gEAResultsOutputFilename;
        static std::string gEALog;
        static bool gDisplayBestGenome;
        static std::string gGenomeFileName;
        static double gPassiveEnergyDrain;
        static double gConnectionEnergyDrain;
};


#endif //ROBOROBO2_SELFASSEMBLYMECHANISMSSHAREDDATA_H
