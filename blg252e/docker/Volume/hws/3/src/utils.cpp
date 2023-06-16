//--- 2021-2022 Summer Object Oriented Programing Assignment 3 ---//
//--------------------------//
//---Name & Surname: Furkan Salık
//---Student Number: 150200056
//--------------------------//

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//

#include "utils.h"

StatisticalDistribution* choose_function(const int inDistributionType) {
    StatisticalDistribution* functionPtr = nullptr;
    switch(inDistributionType) {
        case 0:
            functionPtr = new NormalDistribution();
            break;
        case 1:
            functionPtr = new UniformDistribution();
            break;
        case 2:
            functionPtr = new ExponentialDistribution();
            break;
        default:
            throw "Unidentified distribution function!";
    }

    return functionPtr;
}

double many_trials(const StatisticalDistribution* const inDistributionPtr, std::vector<double>& inRandomSamples, double inTValue, const int inTrialCount, const int inSampleSize, int inSeedValue) {
    int numberOfSuccess = 0;

    for (int i = 0; i < inTrialCount; i++) {
        std::vector<double> samples = inDistributionPtr->sample(inSampleSize, inSeedValue);

        std::vector<double> confidenceInterval = inDistributionPtr->calculate_confidence_interval(samples, inSampleSize, inTValue);
        if (confidenceInterval[0] <= inDistributionPtr->getMean() && confidenceInterval[2] >= inDistributionPtr->getMean()) {
            numberOfSuccess++;
        }

        inSeedValue++;
    }

    return numberOfSuccess / (double)inTrialCount;
}