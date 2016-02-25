#ifndef ROBOROBO2_SELFASSEMBLYMECHANISMSSHAREDDATA_H
#define ROBOROBO2_SELFASSEMBLYMECHANISMSSHAREDDATA_H

#include <RoboroboMain/roborobo.h>
class SelfAssemblyMechanismsSharedData {
    public:
        static int gEvolutionaryGenerationIterations;
        static int gPopulationSize;
        static int gMaxGenerations;
        static int gCrossover;
        static double gMutation;
        static int gElitism;
        static int gNHiddenLayers;
        static std::vector<unsigned > gHiddenLayers;
        static double gTargetFitness;
        static int gNNFactory;
        static std::string gEAResultsOutputFilename;
        static bool gDisplayBestGenome;
        static std::string gGenomeFileName;
};


#endif //ROBOROBO2_SELFASSEMBLYMECHANISMSSHAREDDATA_H
