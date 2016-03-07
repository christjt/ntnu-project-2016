//
// Created by eirikjak on 03.03.16.
//

#ifndef ROBOROBO2_GENOMEVARIATIONLOGGER_H
#define ROBOROBO2_GENOMEVARIATIONLOGGER_H

#include <math.h>
#include "../EA/Logger.h"
class GenomeVariationLogger: public EA::Logger
{
    void logGeneration(const std::vector<EA::DoubleVectorGenotype>& elites, const std::vector<EA::DoubleVectorGenotype>& generation)
    {
        auto& best = generation[generation.size()-1];
        double difference = 0.0;
        for(auto& genome: generation)
        {
            for(auto i = 0u; i < genome.getVector().size(); i++)
            {
                difference += abs(best.getVector()[i] - genome.getVector()[i]);
            }
        }
        std::cout << "Genome variation " << difference << std::endl;
        std::cout << "Variation per genome " << difference/generation.size() << std::endl;
    }
};
#endif //ROBOROBO2_GENOMEVARIATIONLOGGER_H
