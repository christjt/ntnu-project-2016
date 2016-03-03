//
// Created by christopher on 10.11.15.
//

#ifndef ROBOROBO2_DOUBLEVECTORGENOTYPE_H
#define ROBOROBO2_DOUBLEVECTORGENOTYPE_H

#include <vector>
#include <sstream>
#include <random>

namespace EA{
    class DoubleVectorGenotype
    {
    private:
        std::vector<double> vector;
        double rangeMin, rangeMax;

        double _fitness;
        double _scaledFitness;

    public:
        DoubleVectorGenotype(int size, double rangeMin, double rangeMax);
        DoubleVectorGenotype(std::vector<double> vector, double rangeMin, double rangeMax);

        void setRangeMin();
        void setRangeMax();
        double getRangeMin();
        double getRangeMax();

        const std::vector<double>& getVector() const;

        void randomize(std::default_random_engine &random);

        std::string toString();

        double getFitness() const;

        double getScaledFitness() const;

        void setFitness(double fitness);

        void setScaledFitness(double fitness);

        bool operator < (const DoubleVectorGenotype& genotype) const;

        protected:
            void setVector(std::vector<double> vector);
    };

}

#endif //ROBOROBO2_DOUBLEVECTORGENOTYPE_H
