//--- 2021-2022 Summer Object Oriented Programing Assignment 3 ---//
//--------------------------//
//---Name & Surname: Furkan Salık
//---Student Number: 150200056
//--------------------------//

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//

#ifndef __UTILS_H
#define __UTILS_H

#include "statistics.h"

StatisticalDistribution* choose_function(const int inDistributionType);

double many_trials(const StatisticalDistribution* const inDistributionPtr, std::vector<double>& inRandomSamples, double inTValue, const int inTrialCount, const int inSampleSize, int inSeedValue);

#endif