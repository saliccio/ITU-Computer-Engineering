//--- 2021-2022 Summer Object Oriented Programing Assignment 3 ---//
//--------------------------//
//---Name & Surname: Furkan Salık
//---Student Number: 150200056
//--------------------------//

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//

#include "statistics.h"
#include <random>
#include <iostream>

StatisticalDistribution::StatisticalDistribution(const double inMean)
    : m_Mean(inMean)
{

}

std::vector<double> StatisticalDistribution::calculate_confidence_interval(const std::vector<double>& inRandomSamples, const int inSampleSize, const double inTValue) const {
    double sampleSum = 0.0;
    for (auto& i : inRandomSamples) {
        sampleSum += i;
    }

    double sampleMean = sampleSum / inSampleSize;

    double sampleStandardDeviationSquare = 0.0;
    for (auto& i : inRandomSamples) {
        sampleStandardDeviationSquare += pow(i - sampleMean, 2) / inSampleSize;
    }

    double sampleStandardDeviation = sqrt(sampleStandardDeviationSquare);
    
    return std::vector<double> { sampleMean - (inTValue * sampleStandardDeviation / sqrt(inSampleSize)), sampleMean, sampleMean + (inTValue * sampleStandardDeviation / sqrt(inSampleSize)) };
}

StatisticalDistribution::~StatisticalDistribution() {

}

NormalDistribution::NormalDistribution() 
    : StatisticalDistribution(0.0), m_Stddev(1.0)
{

}

std::vector<double> NormalDistribution::sample(const int inSampleSize, const int inSeedValue) const {
    std::vector<double> samples;
    samples.reserve(inSampleSize);

    std::default_random_engine generator;
    generator.seed(inSeedValue);

    std::normal_distribution<double> distribution(m_Mean, m_Stddev);
    for(int i = 0; i < inSampleSize; i++) {
        double number = distribution(generator);
        samples.push_back(number);
    }

    return samples;
}

UniformDistribution::UniformDistribution()
    : StatisticalDistribution(0.0), m_A(-1.0), m_B(1.0)
{

}

std::vector<double> UniformDistribution::sample(const int inSampleSize, const int inSeedValue) const {
    std::vector<double> samples;
    samples.reserve(inSampleSize);

    std::default_random_engine generator;
    generator.seed(inSeedValue);

    std::uniform_real_distribution<double> distribution(m_A, m_B);
    for(int i = 0; i < inSampleSize; i++) {
        double number = distribution(generator);
        samples.push_back(number);
    }

    return samples;
}

ExponentialDistribution::ExponentialDistribution()
    : StatisticalDistribution(1.0), m_Lambda(1.0)
{

}

std::vector<double> ExponentialDistribution::sample(const int inSampleSize, const int inSeedValue) const {
    std::vector<double> samples;
    samples.reserve(inSampleSize);

    std::default_random_engine generator;
    generator.seed(inSeedValue);

    std::exponential_distribution<double> distribution(m_Lambda);
    for(int i = 0; i < inSampleSize; i++) {
        double number = distribution(generator);
        samples.push_back(number);
    }

    return samples;
}

NormalDistribution::~NormalDistribution() {

}

UniformDistribution::~UniformDistribution() {
    
}

ExponentialDistribution::~ExponentialDistribution() {
    
}