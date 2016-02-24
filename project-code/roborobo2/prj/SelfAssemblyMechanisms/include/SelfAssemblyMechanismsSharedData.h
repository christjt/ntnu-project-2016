#ifndef ROBOROBO2_SELFASSEMBLYMECHANISMSSHAREDDATA_H
#define ROBOROBO2_SELFASSEMBLYMECHANISMSSHAREDDATA_H

#include <RoboroboMain/roborobo.h>
class SelfAssemblyMechanismsSharedData {
    public:
        static int gEvolutionaryGenerationIterations;
        static int gPopulationSize;
        static int gMaxGenerations;
        static double gTargetFitness;
        static int gNNFactory;
        static std::string gEAResultsOutputFilename;
        static int gDisplayBestGenome;
        static std::string gGenomeFileName;
};


#endif //ROBOROBO2_SELFASSEMBLYMECHANISMSSHAREDDATA_H
