#include "SelfAssemblyMechanisms/include/Logger/StatisticsLogger.h"

json serializeScenario(const ScenarioData& scenarioData);
json serializeGenome(const GenomeData& genomeData);
json serializeGeneration(const GenerationData& generationData);
json serializeGroupSnapshot(const GroupSnaphot& snapshot);
json serializeGroup(const GroupData& groupData);
StatisticsLogger* StatisticsLogger::instance = nullptr;
StatisticsLogger::StatisticsLogger()
{
}

void StatisticsLogger::beginScenario(int scenario)
{
    currentScenario = ScenarioData();
    currentScenario.seed = scenario;
}

void StatisticsLogger::beginGenome(EA::DoubleVectorGenotype* genome)
{
    currentGenome = GenomeData();
    currentGenome.weights = genome->getVector();
}

void StatisticsLogger::beginGeneration(int generation)
{
    currentGeneration = GenerationData();
    currentGeneration.generation = generation;
}

void StatisticsLogger::logScenarioSeed(int seed)
{
    currentScenario.seed = seed;
}

void StatisticsLogger::logFitness(double fitness)
{
    currentScenario.fitness = fitness;
}

void StatisticsLogger::logRobotStarvedToDeath()
{
    currentScenario.robotsStarvedToDeath++;
}

void StatisticsLogger::logRobotEaten()
{
    currentScenario.robotsEaten++;
}

void StatisticsLogger::logRobotConsumedEnergy()
{
    currentScenario.energyConsumedByRobot++;
}

void StatisticsLogger::logGroupConsumedEnergy()
{
    currentScenario.energyConsumedByGroup++;
}

void StatisticsLogger::logPredatorEaten()
{
    currentScenario.predatorsEaten++;
}

void StatisticsLogger::logGroupSnapshot(GroupSnaphot& groupSnapshot)
{
    if(groupSnapshot.groups.size() == 0){
        if(currentScenario.groupSnapshots.size() == 0 || currentScenario.groupSnapshots.back().numberOfGroups == 0)
            return;
    }
    currentScenario.groupSnapshots.push_back(groupSnapshot);
}


void StatisticsLogger::endScenario()
{
    currentGenome.scenarios.push_back(currentScenario);
}

void StatisticsLogger::endGenome()
{
    currentGeneration.genomes.push_back(currentGenome);
}

void StatisticsLogger::endGeneration()
{
    statistics.push_back(currentGeneration);
}

json StatisticsLogger::serializeToJson()
{

    std::vector<json> generations;
    for(auto& generationData: statistics){
        generations.push_back(serializeGeneration(generationData));
    }

    json out = {
            {"generations", generations}
    };

    return out;
}

json serializeGeneration(const GenerationData& generationData)
{
    std::vector<json> genomes;
    for(auto& genomeData: generationData.genomes){
        genomes.push_back(serializeGenome(genomeData));
    }

    json generation = {
            {"generation", generationData.generation},
            {"genomes", genomes}
    };
    return generation;
}

json serializeGenome(const GenomeData& genomeData)
{
    std::vector<json> scenarios;
    for(auto& scenarioData: genomeData.scenarios){
        scenarios.push_back(serializeScenario(scenarioData));
    }

    json genome = {
         //   {"weights", genomeData.weights},
            {"scenarios", scenarios}
    };

    return genome;
}

json serializeScenario(const ScenarioData& scenarioData)
{
    std::vector<json> snapshots;
    for(auto& snapshot: scenarioData.groupSnapshots){
        snapshots.push_back(serializeGroupSnapshot(snapshot));
    }

    json scenario = {
            {"scenario", scenarioData.seed},
            {"fitness", scenarioData.fitness},
            {"robotsStarvedToDeath", scenarioData.robotsStarvedToDeath},
            {"robotsEaten", scenarioData.robotsEaten},




            {"energyConsumedByRobot", scenarioData.energyConsumedByRobot},
            {"energyConsumedByGroup", scenarioData.energyConsumedByGroup},

            {"predatorsEaten", scenarioData.predatorsEaten},
            {"groupSnapshots", snapshots},
    };

    return scenario;
}

json serializeGroupSnapshot(const GroupSnaphot& snapshot)
{
    std::vector<json> groups;
    for(auto& group: snapshot.groups){
        groups.push_back(serializeGroup(group));
    }

    json groupSnapshot = {
            {"numberOfGroups", snapshot.numberOfGroups},
            {"timestamp", snapshot.timestamp},
            {"groups", groups},

    };
    return groupSnapshot;
}

json serializeGroup(const GroupData& groupData)
{
    json group {
            {"id", groupData.id},
            {"size", groupData.size}
    };

    return group;
}
