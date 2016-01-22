//
// Created by christopher on 10.11.15.
//

#include "Aggregate/include/EA/DoubleVectorGenotype.h"

using namespace EA;
DoubleVectorGenotype::DoubleVectorGenotype(int size, double rangeMin, double rangeMax){
    this->vector = std::vector<double>(size);
    this->rangeMax = rangeMax;
    this->rangeMin = rangeMin;
}

DoubleVectorGenotype::DoubleVectorGenotype(std::vector<double> vector, double rangeMin, double rangeMax){
    this->vector = vector;
    this->rangeMax = rangeMax;
    this->rangeMin = rangeMin;
}

void DoubleVectorGenotype::randomize(std::default_random_engine &random){

    std::uniform_real_distribution<double> distribution(rangeMin, rangeMax);

    for (unsigned int i = 0; i < vector.size(); ++i) {
        vector[i] = distribution(random);
    }
}

std::string DoubleVectorGenotype::toString(){
    std::stringstream ss;
    for (unsigned int i = 0; i < vector.size(); ++i) {
        if(i != 0)
            ss << ",";
        ss << vector[i];
    }

    return ss.str();
}
std::vector<double> DoubleVectorGenotype::getVector(){
    return vector;
}
double DoubleVectorGenotype::getFitness() const{
    return _fitness;
};

double DoubleVectorGenotype::getScaledFitness() const{
    return _scaledFitness;
}

void DoubleVectorGenotype::setFitness(double fitness){
    _fitness = fitness;
}

void DoubleVectorGenotype::setScaledFitness(double fitness){
    _scaledFitness= fitness;
}

bool DoubleVectorGenotype::operator < (const DoubleVectorGenotype& genotype) const{
    return getScaledFitness() < genotype.getScaledFitness();
}

double DoubleVectorGenotype::getRangeMin(){
    return rangeMin;
};

double DoubleVectorGenotype::getRangeMax(){
    return rangeMax;
};
