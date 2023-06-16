//--- 2021-2022 Summer Object Oriented Programing Assignment 3 ---//
//--------------------------//
//---Name & Surname: Furkan Salık
//---Student Number: 150200056
//--------------------------//

#ifndef __STATISTICS_H
#define __STATISTICS_H

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//

#include <vector>

class StatisticalDistribution {
    protected:
        double m_Mean;
    public:
        StatisticalDistribution(const double inMean);

        inline double getMean() const { return m_Mean; }

        virtual std::vector<double> sample(const int inSampleSize, const int inSeedValue) const = 0;
        virtual std::vector<double> calculate_confidence_interval(const std::vector<double>& inRandomSamples, const int inSampleSize, const double inTValue) const;

        virtual ~StatisticalDistribution();
};

class NormalDistribution : public StatisticalDistribution {
    private:
        double m_Stddev;
    public:
        NormalDistribution();

        virtual std::vector<double> sample(const int inSampleSize, const int inSeedValue) const override;

        virtual ~NormalDistribution();
};

class UniformDistribution : public StatisticalDistribution {
    private:
        double m_A;
        double m_B;
    public:
        UniformDistribution();

        virtual std::vector<double> sample(const int inSampleSize, const int inSeedValue) const override;

        virtual ~UniformDistribution();
};

class ExponentialDistribution : public StatisticalDistribution {
    private:
        double m_Lambda;
    public:
        ExponentialDistribution();

        virtual std::vector<double> sample(const int inSampleSize, const int inSeedValue) const override;

        virtual ~ExponentialDistribution();
};

#endif