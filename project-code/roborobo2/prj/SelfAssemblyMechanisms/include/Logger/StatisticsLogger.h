#ifndef ROBOROBO2_STATISTICSLOGGER_H
#define ROBOROBO2_STATISTICSLOGGER_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "SelfAssemblyMechanisms/include/json.hpp"
#include "SelfAssemblyMechanisms/include/EA/DoubleVectorGenotype.h"

struct GroupData
{
    int id;
    int size;
};

struct GroupSnaphot{
    int numberOfGroups;
    int timestamp;
    std::vector<int> groupSizes;
};

struct ScenarioData{
    int seed;
    double fitness;
    int robotsStarvedToDeath;
    int robotsEaten;

    int energyConsumedByRobot;
    int energyConsumedByGroup;

    int predatorsEaten;
    std::vector<GroupSnaphot> groupSnapshots;
};


struct GenomeData{

    std::vector<double> weights;
    std::vector<ScenarioData> scenarios;
};


struct GenerationData{
    int generation;
    std::vector<GenomeData> genomes;
    std::vector<double> best;
};




typedef nlohmann::json json;
class StatisticsLogger{

public:
    static StatisticsLogger* getInstance()
    {
        if(!instance)
            instance = new StatisticsLogger();
        return instance;
    }

    void beginScenario(int scenario);
    void beginGenome(EA::DoubleVectorGenotype* genome);
    void beginGeneration(int generation);
    void endScenario();
    void endGenome();
    void endGeneration();

    void logBestGenome(EA::DoubleVectorGenotype& genome);
    void logScenarioSeed(int seed);
    void logFitness(double fitness);
    void logRobotStarvedToDeath();
    void logRobotEaten();
    void logRobotConsumedEnergy();
    void logGroupConsumedEnergy();
    void logPredatorEaten();

    void logGroupSnapshot(GroupSnaphot& groupSnapshot);
    json serializeToJson();

private:
    StatisticsLogger();
    static StatisticsLogger* instance;

    std::ofstream logFile;
    GenerationData currentGeneration;
    ScenarioData currentScenario;
    GenomeData currentGenome;
    std::vector<GenerationData> statistics;
};



#endif //ROBOROBO2_STATISTICSLOGGER_H
