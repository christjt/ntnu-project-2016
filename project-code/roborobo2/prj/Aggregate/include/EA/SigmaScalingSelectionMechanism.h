//
// Created by eirikjak on 11.11.15.
//

#ifndef ROBOROBO2_SIGMASCALINGSELECTIONMECHANISM_H
#define ROBOROBO2_SIGMASCALINGSELECTIONMECHANISM_H

#include "DoubleVectorGenotype.h"
#include <vector>
#include <random>
namespace EA
{
    class SigmaScalingSelectionMechanism
    {
    public:
        std::vector<DoubleVectorGenotype> selectParents(std::vector<DoubleVectorGenotype> &adultPool, int selectCount, std::default_random_engine &random);
    };
}
#endif //ROBOROBO2_SIGMASCALINGSELECTIONMECHANISM_H
