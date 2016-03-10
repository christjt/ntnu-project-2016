#ifndef ROBOROBO2_RANKSELECTIONMECHANISM_H
#define ROBOROBO2_RANKSELECTIONMECHANISM_H

#include "SelectionMechanism.h"
#include "math.h"
namespace EA
{
    class TournamentSelectionMechanism: public SelectionMechanism
    {
        private:
            int groupSize;
            double _pickChance;
        public:
        TournamentSelectionMechanism(int _groupSize, double _pickChance):
                    groupSize(_groupSize), _pickChance(_pickChance){}

            std::vector<DoubleVectorGenotype> selectParents(std::vector<DoubleVectorGenotype> &adultPool, int selectCount, std::default_random_engine &random)
            {
                std::vector<DoubleVectorGenotype> group;
                DoubleVectorGenotype* previous = nullptr;
                std::vector<DoubleVectorGenotype> parents;
                std::uniform_int_distribution<int> adult_dist(0, adultPool.size()-1);
                std::uniform_int_distribution<int> group_dist(0, groupSize-1);
                std::uniform_real_distribution<double> pick_dist(0.0, 1.0);

                for(int i= 0; i < selectCount; i++)
                {
                    for(int j= 0; j < groupSize; j++)
                    {
                        auto individual = adultPool[adult_dist(random)];
                        group.push_back(individual);
                    }
                    std::sort(group.begin(), group.end(), [](DoubleVectorGenotype a, DoubleVectorGenotype b){
                        return a.getFitness() > b.getFitness();
                    });

                    DoubleVectorGenotype* selected = nullptr;
                    for(int j = 0; j < groupSize; j++)
                    {
                        bool pick = pick_dist(random) < _pickChance*pow((1-_pickChance), j);
                        if(!pick)
                            continue;
                        selected = &group[j];
                        if(parents.size() % 2 == 0 && selected == previous)
                        {
                            selected = nullptr;
                            continue;
                        }
                    }

                    if(selected == nullptr)
                    {
                        do{
                            selected = &group[group_dist(random)];
                        }while(parents.size() % 2 == 0 && selected == previous);

                    }

                    parents.push_back(*selected);
                    previous = selected;
                    group.clear();
                }

                return parents;
            }
    };
}
#endif //ROBOROBO2_RANKSELECTIONMECHANISM_H
