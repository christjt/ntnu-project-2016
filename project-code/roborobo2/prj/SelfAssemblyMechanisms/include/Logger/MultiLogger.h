#ifndef ROBOROBO2_MULTILOGGER_H
#define ROBOROBO2_MULTILOGGER_H

#include <vector>
#include "../EA/Logger.h"
class MultiLogger: public EA::Logger
{
    private:
        std::vector<EA::Logger*> loggers;
    public:
        MultiLogger(std::initializer_list<EA::Logger*> _loggers):loggers(_loggers){}

        void logGeneration(const std::vector<EA::DoubleVectorGenotype>& elites, const std::vector<EA::DoubleVectorGenotype>& generation)
        {
            for(auto logger: loggers)
            {
                logger->logGeneration(elites, generation);
            }
        }
};
#endif //ROBOROBO2_MULTILOGGER_H
