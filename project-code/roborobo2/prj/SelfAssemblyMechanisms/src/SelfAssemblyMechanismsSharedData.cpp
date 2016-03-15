
#include "SelfAssemblyMechanisms/include/SelfAssemblyMechanismsSharedData.h"



int SelfAssemblyMechanismsSharedData::gEvolutionaryGenerationIterations = 100;
int SelfAssemblyMechanismsSharedData::gPopulationSize = 10;
int SelfAssemblyMechanismsSharedData::gMaxGenerations = 10;
int SelfAssemblyMechanismsSharedData::gNScenarios = 1;
int SelfAssemblyMechanismsSharedData::gElitism = 1;
int SelfAssemblyMechanismsSharedData::gCrossover = 1;
double SelfAssemblyMechanismsSharedData::gExplorationThreshold = 0.9;
double SelfAssemblyMechanismsSharedData::gExplorationMutationRate = 1.0;
int SelfAssemblyMechanismsSharedData::gTournamentGroupSize = 4;
double SelfAssemblyMechanismsSharedData::gTournamentPickChance = 0.5;
bool SelfAssemblyMechanismsSharedData::gCanEatPredators = false;
double SelfAssemblyMechanismsSharedData::gPredatorEnergyReward = 500;
double SelfAssemblyMechanismsSharedData::gMutationStep = 0;
double SelfAssemblyMechanismsSharedData::gMutation = 0.05;
int SelfAssemblyMechanismsSharedData::gNHiddenLayers = 0;
std::vector<unsigned> SelfAssemblyMechanismsSharedData::gHiddenLayers = std::vector<unsigned >();
std::string SelfAssemblyMechanismsSharedData::gEALog = "";
double SelfAssemblyMechanismsSharedData::gTargetFitness = 1.0;
int SelfAssemblyMechanismsSharedData::gNNFactory = 0;
std::string SelfAssemblyMechanismsSharedData::gEAResultsOutputFilename;
std::string SelfAssemblyMechanismsSharedData::gGenomeFileName;
bool SelfAssemblyMechanismsSharedData::gDisplayBestGenome;
double SelfAssemblyMechanismsSharedData::gPassiveEnergyDrain = 1;
double SelfAssemblyMechanismsSharedData::gConnectionEnergyDrain = 1;

