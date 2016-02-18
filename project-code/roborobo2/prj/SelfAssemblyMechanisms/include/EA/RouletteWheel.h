//
// Created by eirikjak on 10.11.15.
//

#ifndef ROBOROBO2_ROULETTEWHEEL_H
#define ROBOROBO2_ROULETTEWHEEL_H

#include <random>
#include <vector>

#include "DoubleVectorGenotype.h"

namespace EA
{
    class RouletteWheel
    {
    private:
        int _previousSelection;
        std::default_random_engine &_random;
        std::vector<DoubleVectorGenotype> _adults;
        int selectAdult(double selected_range);
    public:
        RouletteWheel(std::default_random_engine &random, std::vector<DoubleVectorGenotype> adults);
        std::vector<DoubleVectorGenotype> selectAdults(int n_adults);

    };
}
#endif //ROBOROBO2_ROULETTEWHEEL_H
