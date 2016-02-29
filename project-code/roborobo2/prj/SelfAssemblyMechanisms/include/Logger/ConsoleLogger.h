#ifndef ROBOROBO2_CONSOLELOGGER_H
#define ROBOROBO2_CONSOLELOGGER_H

#include <iostream>
#include "../EA/Logger.h"
#include <algorithm>
class ConsoleLogger: public EA::Logger
{
    void logGeneration(const std::vector<EA::DoubleVectorGenotype>& elites, const std::vector<EA::DoubleVectorGenotype>& generation)
    {
        static int generationCount;
        generationCount++;
        std::cout << "Generation " << generationCount << std::endl;

        for(auto& genome: generation)
        {
            std::cout << genome.getFitness() << std::endl;
        }

        std::cout << "Elites" << std::endl;
        for(auto& elite: elites){
            std::cout << elite.getFitness() << std::endl;
        }
    }
};
#endif //ROBOROBO2_CONSOLELOGGER_H
