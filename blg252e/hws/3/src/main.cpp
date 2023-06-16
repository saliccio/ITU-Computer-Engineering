//--- 2021-2022 Summer Object Oriented Programing Assignment 3 ---//

//-------------DO NOT EDIT MAIN FILE-------------//

#include "statistics.h"
#include "utils.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <random>


int main(int argc, char **argv) {
    try {
        int dist_type, mode, sample_size, trials, seed_value;
        double significance_level, t_value;

        // Fix floating numbers precision to 3 while printing.
        std::cout << std::setprecision(3) << std::fixed;

        //-------------File Read Section-------------//

        std::ifstream myfile(argv[1]);
        myfile >> dist_type >> mode >> sample_size >> significance_level >> t_value >> trials >> seed_value;
        myfile.close();

        //-------------Instance Creation-------------//

        //****Code this function in "utils.cpp" file.****//
        StatisticalDistribution *dist = choose_function(dist_type);

        //****Code this method in "statistics.cpp" file.****//
        std::vector<double> random_sample = dist->sample(sample_size, seed_value);

        //-------------Program Modes-------------//

        if(mode == 0) { // Prints the sampled values.

            for(int i=0; i<sample_size; i++) {
                std::cout << random_sample[i] << std::endl;
            }

        } else if(mode == 1) { // Prints the confidence interval for one sample.

            //****Code this method in "statistics.cpp" file.****//
            std::vector<double> interval = dist->calculate_confidence_interval(random_sample, sample_size, t_value);

            std::cout << "lower bound: " << interval[0] << std::endl;
            std::cout << "mean: " << interval[1] << std::endl;
            std::cout << "upper bound: " << interval[2] << std::endl;

        } else if(mode == 2) { // Prints the comparison between significance level and calculated precision.

            //****Code this function in "utils.cpp" file.****//
            double precision = many_trials(dist, random_sample, t_value, trials, sample_size, seed_value);

            std::cout << "significance level: " << significance_level << std::endl;
            std::cout << "precision: " << precision << std::endl;

        } else {

            throw "Selected mode is invalid!";
        }

        return 0;

    } catch(char const *c) {
	    std::cout << c << std::endl;
	}
}