#ifndef ROBOROBO2_FILELOGGER_H
#define ROBOROBO2_FILELOGGER_H

#include "../EA/Logger.h"
#include <fstream>
#include <iostream>

class FileLogger: public EA::Logger
{

    private:
        std::ofstream logFile;
    public:
        FileLogger(std::string logFilePath)
        {
            logFile.open(logFilePath);
        }

        void logGeneration(const std::vector<EA::DoubleVectorGenotype>& elites, const std::vector<EA::DoubleVectorGenotype>& generation)
        {
            std::stringstream ss;
            for(auto i = 0u; i < generation.size(); i++)
            {
                ss << generation[i].getFitness();
                if(i < generation.size() -1)
                    ss << ",";
            }
            ss << ":";
            for(auto i = 0u; i < elites.size(); i++)
            {
                ss << elites[i].getFitness();
                if(i< elites.size()-1)
                    ss << ",";
            }
            logFile << ss.str() << std::endl;
        }
};
#endif //ROBOROBO2_FILELOGGER_H
