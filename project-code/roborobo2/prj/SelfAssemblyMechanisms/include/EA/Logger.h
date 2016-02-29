#ifndef ROBOROBO2_LOGGER_H
#define ROBOROBO2_LOGGER_H

#include <vector>
#include "DoubleVectorGenotype.h"

namespace EA
{
    class Logger
    {
        public:
            virtual void logGeneration(const std::vector<EA::DoubleVectorGenotype>& elites, const std::vector<DoubleVectorGenotype>& generation) = 0;
    };
}
#endif //ROBOROBO2_LOGGER_H
