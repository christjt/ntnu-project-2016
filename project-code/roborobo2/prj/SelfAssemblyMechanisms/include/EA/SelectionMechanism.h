#ifndef ROBOROBO2_SELECTIONMECHANISM_H
#define ROBOROBO2_SELECTIONMECHANISM_H

#include "DoubleVectorGenotype.h"
#include <vector>
#include <random>
namespace EA
{
    class SelectionMechanism
    {
        public:
            virtual std::vector<DoubleVectorGenotype> selectParents(std::vector<DoubleVectorGenotype> &adultPool, int selectCount, std::default_random_engine &random) = 0;
    };
}

#endif //ROBOROBO2_SELECTIONMECHANISM_H
