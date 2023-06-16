#include <fstream>
#include <iostream>
#include <chrono>
#include <vector>
#include "CompletelyFairScheduler.h"
#include "Process.h"
#include "RBTree.h"

void CompletelyFairScheduler::simulate(const std::string &input_path, const std::string &output_path) const
{
    std::ifstream input_stream(input_path);
    std::ofstream output_stream(output_path);
    std::string data_read;
    getline(input_stream, data_read, ' ');
    int num_processes = std::stoi(data_read);
    getline(input_stream, data_read);
    int sim_runtime = std::stoi(data_read);

    RBTree<Process> process_tree;
    RBNode<Process> *current_processPtr = nullptr;
    std::vector<std::string> completed_process_names;
    int total_process_count = 0;
    int min_runtime = 0;
    auto time_begin = std::chrono::steady_clock::now();
    for (int sim_time = 0; sim_time < sim_runtime; sim_time++)
    {
        int new_file_pos = input_stream.tellg();
        std::string name;
        bool end_of_file;
        while (getline(input_stream, name, ' '))
        { // This loop controls the next processes that are ready to be scheduled (and ready to be in the tree)
            getline(input_stream, data_read, ' ');
            int time_of_arrival = std::stoi(data_read);
            if (time_of_arrival != sim_time)
            {
                break;  // Break if the arrival time has not yet come
            }
            getline(input_stream, data_read);
            int burst_time = std::stoi(data_read);
            process_tree.insert(Process(name, time_of_arrival, burst_time));
            min_runtime = 0;
            total_process_count++;
            new_file_pos = input_stream.tellg();
            end_of_file = input_stream.peek() == EOF;
        }
        input_stream.seekg(new_file_pos, std::ios::beg); // Restore the file position to be valid

        if (current_processPtr == nullptr)  // Look for something to process
        {
            if (process_tree.isEmpty())
            {
                output_stream << sim_time << ",-,-,-,-,-,-" << std::endl;   // If there is nothing to process, simply continue
                continue;
            }
            current_processPtr = process_tree.getMin();     // If the tree is not empty, get and start processing the element with minimum runtime
            if (current_processPtr->getParent() != nullptr)     // Check parent for updating min_runtime
            {
                min_runtime = current_processPtr->getParent()->getValue().running_time;
            }
            if (!current_processPtr->getRight()->isNIL())   // Check right child for updating min_runtime
            {
                min_runtime = std::min(min_runtime, current_processPtr->getRight()->getValue().running_time);
            }
        }
        if (current_processPtr != nullptr)  // If CPU is processing something right now
        {
            Process current_process = current_processPtr->getValue();   // Get the value of the node

            // Write this iteration's stats to the output file
            output_stream << sim_time << ',';
            output_stream << current_process.name << ',';
            output_stream << current_process.running_time << ',';
            output_stream << std::min(min_runtime, current_process.running_time) << ',';
            output_stream << process_tree.getInorder() << ',';

            current_processPtr->getValueRef().running_time++;   // Increase directly in the tree (using the node's reference)
            current_process.running_time++;     // Increase the copy of the node's value

            bool process_is_completed = current_process.running_time == current_process.burst_time;     // Check whether the process is completed
            output_stream << (process_is_completed ? (completed_process_names.size() + 1 == total_process_count ? "Completed" : "Complete") : "Incomplete");    // Write "Completed" if all processes have come to an end, write "Complete" if this process ended but still there are processes needed to be run, and write "Incomplete" if this process has not yet completed.
            output_stream << std::endl;

            if (process_is_completed)
            {
                process_tree.pop();     // If the process is completed, remove it from the tree.
                completed_process_names.push_back(current_processPtr->getValue().name);     // Add to the completed process names vector
                current_processPtr = nullptr;   // Make the pointer null to allow searching in the next iteration
                if (process_tree.isEmpty() && end_of_file)      // If the tree is empty, this means all processes have completed, and if also the input file is completely read, this means every possible process has completed, therefore the simulation should end.
                {
                    break;
                }
            }
            else if (!process_tree.isEmpty() && current_process.running_time > min_runtime)     // If there are processes in the tree, and there is at least one process with lower runtime than current process, pop and insert current process to update the tree for getting the process with minimum runtime in the next iteration (also this is why the pointer is set to null).
            {
                process_tree.pop();
                process_tree.insert(current_process);
                current_processPtr = nullptr;
            }
        }
    }

    // Write all other statistics to the output
    auto time_end = std::chrono::steady_clock::now();
    int time_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(time_end - time_begin).count();
    output_stream << std::endl;
    output_stream << "Scheduling finished in " << time_elapsed << "ms." << std::endl;
    output_stream << completed_process_names.size() << " of " << total_process_count << " processes are completed." << std::endl;
    output_stream << "The order of completion of the tasks: ";
    if (completed_process_names.size() > 0)
    {
        for (int i = 0; i < completed_process_names.size() - 1; i++)
        {
            output_stream << completed_process_names[i] << '-';
        }
        output_stream << completed_process_names.back() << std::endl;
    }
    input_stream.close();
    output_stream.close();
}