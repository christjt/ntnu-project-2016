#ifndef ROBOROBO2_SELFASSEMBLYMECHANISMSSHAREDDATA_H
#define ROBOROBO2_SELFASSEMBLYMECHANISMSSHAREDDATA_H

#include <string>
class SelfAssemblyMechanismsSharedData {
    public:
        static int gEvolutionaryGenerationIterations;
        static int gPopulationSize;
        static int gMaxGenerations;
        static double gTargetFitness;
        static int gNNFactory;
        static std::string gEAResultsOutputFilename;
        static bool gDisplayBestGenome;
        static std::string gGenomeFileName;
};


#endif //ROBOROBO2_SELFASSEMBLYMECHANISMSSHAREDDATA_H
