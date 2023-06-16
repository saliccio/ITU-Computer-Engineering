#ifndef PROCESS_H
#define PROCESS_H

#include <string>

struct Process {
    std::string name;
    int time_of_arrival;
    int burst_time;
    int running_time;

    Process() {}
    Process(const std::string& name, const int time_of_arrival, const int burst_time)
        : name(name), time_of_arrival(time_of_arrival), burst_time(burst_time), running_time(0) {}

    bool operator<(const Process& other) const {
        return running_time < other.running_time;
    }
};

#endif