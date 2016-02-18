//
// Created by eirikjak on 10.11.15.
//

#include "Aggregate/include/EA/RouletteWheel.h"
#include <algorithm>
#include <iostream>
#include <stdexcept>
using namespace EA;
RouletteWheel::RouletteWheel(std::default_random_engine &random, std::vector<DoubleVectorGenotype> phenotypes):_random(random)
{
    _adults =phenotypes;
    std::sort(_adults.begin(), _adults.end());
}

std::vector<DoubleVectorGenotype> RouletteWheel::selectAdults(int n_adults)
{

    std::vector<DoubleVectorGenotype> selected_parents;
    double sum = 0.0;
    for(DoubleVectorGenotype &adult: _adults){
        sum += adult.getScaledFitness();
    }
    int previousSelection = -1;
    int selected;
    std::uniform_real_distribution<double> distribution(0,sum);
    double point = distribution(_random);
    for(int i = 0; i < n_adults; i++){

        do{
            selected = selectAdult(point);
            point = distribution(_random);
        }while(previousSelection == selected);

        previousSelection = selected;
        selected_parents.push_back(_adults[selected]);
    }
    return selected_parents;
}


int RouletteWheel::selectAdult(double selected_range)
{
    double count = 0;

    for(unsigned int i = 0; i < _adults.size(); i++)
    {
        auto adult = _adults[i];
        if(adult.getScaledFitness() + count >= selected_range)
        {
            return i;
        }
        count += adult.getScaledFitness();
    }
    throw std::invalid_argument("Range Not found in roulette");
}
