#include <cstdlib>
#include <float.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <math.h>
#include <string>
#include "RBTree.h"

int sample_count = 0;
double mean = 0;
double variance = 0;
double min = DBL_MAX;
double max = DBL_MIN;
double firstq = 0;
double median = 0;
double thirdq = 0;
std::string starting_date = "";
std::string starting_time = "";
std::string last_date = "";
std::string last_time = "";

// These are the functions to get the estimator values, which are called by function pointers in main.
double getMean() {
    return mean;
}

double getStdDev() {
    return std::sqrt(variance);
}

double getMin() {
    return min;
}

double getMax() {
    return max;
}

double getFirstq() {
    return firstq;
}

double getMedian() {
    return median;
}

double getThirdq() {
    return thirdq;
}

int main(int argc, char** argv) {
    auto file_stream = std::ifstream(argv[1]);
    
    // Read the estimators and set the desired ones' getter functions in a function pointer array.
    std::string line;
    getline(file_stream, line);
    int estimator_count = std::stoi(line);
    double (*estimator_func_ptrs[7])();
    bool compute_firstq = false;
    bool compute_median = false;
    bool compute_thirdq = false;
    for(int i = 0; i < estimator_count; i++) {
        getline(file_stream, line);
        if(line == "mean") {
            estimator_func_ptrs[i] = getMean;
        }
        else if(line == "std") {
            estimator_func_ptrs[i] = getStdDev;
        }
        else if(line == "min") {
            estimator_func_ptrs[i] = getMin;
        }
        else if(line == "firstq") {
            estimator_func_ptrs[i] = getFirstq;
            compute_firstq = true;
        }
        else if(line == "median") {
            estimator_func_ptrs[i] = getMedian;
            compute_median = true;
        }
        else if(line == "thirdq") {
            estimator_func_ptrs[i] = getThirdq;
            compute_thirdq = true;
        }
        else if(line == "max") {
            estimator_func_ptrs[i] = getMax;
        }
    }

    getline(file_stream, line);  // For skipping the empty line
    getline(file_stream, line);  // Total input count, desired feature (For example: '19,gap')
    int total_input_count = std::stoi(line.substr(0, line.find(',')));
    line = line.substr(line.find(',') + 1, line.length());

    // Set the feature index to later use for indexing the samples.
    int feature_index;
    if(line == "gap") {
        feature_index = 0;
    }
    if(line == "grp") {
        feature_index = 1;
    }
    if(line == "v") {
        feature_index = 2;
    }
    if(line == "gi") {
        feature_index = 3;
    }

    std::ostringstream total_output;  // All outputs of 'print' are appended to this stream to lower the I/O speed boundedness of the program. This stream is then flushed to the output file at the end of the program.
    total_output << std::setprecision(7);

    RBTree<double> tree;  // Red-black tree which stores the desired feature of all samples.

    while(getline(file_stream, line)) {
        if(line == "add") {
            getline(file_stream, last_date, ',');
            getline(file_stream, last_time, ',');
            if(starting_date == "") { starting_date = last_date; starting_time = last_time; }

            double sample[4];
            getline(file_stream, line, ',');
            sample[0] = std::stod(line);
            getline(file_stream, line, ',');
            sample[1] = std::stod(line);
            getline(file_stream, line, ',');
            sample[2] = std::stod(line);
            getline(file_stream, line, '\n');
            sample[3] = std::stod(line);
            sample_count += 1;

            // Calculate new mean, variance, min and max values.
            double value = sample[feature_index];
            double old_mean = mean;
            mean = ((sample_count - 1) * mean + value) / sample_count;
            if(sample_count > 1) {
                variance = ((sample_count - 2) * variance / (sample_count - 1)) + (value - old_mean) * (value - old_mean) / sample_count;
            }
            if(value < min) {
                min = value;
            }
            if(value > max) {
                max = value;
            }
            if(compute_firstq || compute_median || compute_thirdq) {
                tree.insert(value);
            }
        } else if(line == "print") {
            // Calculate the first quartile, median and third quartile indexes, if the divison result is an integer, do not apply floor/ceil operations on it, since for example it would ceil 2.00001 to 3.
            int firstq_index1 = ((sample_count - 1) % 4 == 0) ? ((sample_count - 1) / 4) : std::floor((sample_count - 1) / 4.0);
            int firstq_index2 = ((sample_count - 1) % 4 == 0) ? ((sample_count - 1) / 4) : std::ceil((sample_count - 1) / 4.0);
            int median_index1 = ((sample_count - 1) % 2 == 0) ? ((sample_count - 1) / 2) : std::floor((sample_count - 1) / 2.0);
            int median_index2 = ((sample_count - 1) % 2 == 0) ? ((sample_count - 1) / 2) : std::ceil((sample_count - 1) / 2.0);
            int thirdq_index1 = sample_count - 1 - firstq_index2;
            int thirdq_index2 = sample_count - 1 - firstq_index1;
            
            // For each quartile if desired, calculate the values by linear interpolation.
            // (For example, let's say [(sample_count - 1) / 4] is 0.75, firstq_index1 would be 0 and firstq_index2 would be 1. Since 0.75 is closer to 1, the calculation would be like values[0] * (1 - 0.75) + values[1] * 0.75).
            // Values are obtained by calling getithSmallest method of red-black tree.
            if(compute_firstq) {
                if(firstq_index1 == firstq_index2) {
                    firstq = tree.getithSmallest(tree.getRoot(), firstq_index1 + 1);
                } else {
                    firstq = tree.getithSmallest(tree.getRoot(), firstq_index1 + 1) * (1 - ((sample_count - 1) / 4.0) + firstq_index1) + tree.getithSmallest(tree.getRoot(), firstq_index2 + 1) * (((sample_count - 1) / 4.0) - firstq_index1);
                }
            }
            if(compute_median) {
                if(median_index1 == median_index2) {
                    median = tree.getithSmallest(tree.getRoot(), median_index1 + 1);
                } else {
                    median = tree.getithSmallest(tree.getRoot(), median_index1 + 1) * (1 - ((sample_count - 1) / 2.0) + median_index1) + tree.getithSmallest(tree.getRoot(), median_index2 + 1) * (1 - median_index2 + (sample_count - 1) / 2.0);
                }
            }
            if(compute_thirdq) {
                if(thirdq_index1 == thirdq_index2) {
                    thirdq = tree.getithSmallest(tree.getRoot(), thirdq_index1 + 1);
                } else {
                    thirdq = tree.getithSmallest(tree.getRoot(), thirdq_index1 + 1) * (1 - (3 * (sample_count - 1) / 4.0) + thirdq_index1) + tree.getithSmallest(tree.getRoot(), thirdq_index2 + 1) * (1 - thirdq_index2 + 3 * (sample_count - 1) / 4.0);
                }
            }
            
            total_output << starting_date << "," << starting_time << "," << last_date << "," << last_time;
            for(int i = 0; i < estimator_count; i++) {
                double estimator_value = estimator_func_ptrs[i]();
                if(estimator_value == 0) {
                    total_output << "," << "0.0";  // To write 0.0 instead of 0
                } else {
                    total_output << "," << estimator_value;
                }
            }
            total_output << "\n";
        }
    }
    file_stream.close();
    
    // Flush the accumulated output string from all print calls into the output file.
    std::ofstream output_file("output.txt");
    output_file << std::setprecision(7);
    output_file << total_output.str();
    output_file.close();

    return EXIT_SUCCESS;
}