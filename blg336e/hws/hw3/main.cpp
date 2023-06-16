#include <stdlib.h>     // EXIT_SUCCESS
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <set>
#include <map>
#include <unordered_map>
#include <algorithm>    // std::sort
#include <functional>   // std::function

// Hour comparator function used in sorting.
bool compare_hours(const std::string &lhs, const std::string &rhs) {
    int lhs_hours = std::stoi(lhs.substr(0, lhs.find_first_of(':')));
    int lhs_minutes = std::stoi(lhs.substr(lhs.find_first_of(':') + 1));

    int rhs_hours = std::stoi(rhs.substr(0, rhs.find_first_of(':')));
    int rhs_minutes = std::stoi(rhs.substr(rhs.find_first_of(':') + 1));

    if (lhs_hours == rhs_hours)
    {
        return lhs_minutes <= rhs_minutes;
    }

    return lhs_hours <= rhs_hours;
}

// Date comparator function used in sorting.
bool compare_dates(const std::string &lhs, const std::string &rhs) {
    int lhs_days = std::stoi(lhs.substr(0, lhs.find_first_of('.')));
    int lhs_months = std::stoi(lhs.substr(lhs.find_first_of('.') + 1));

    int rhs_days = std::stoi(rhs.substr(0, rhs.find_first_of('.')));
    int rhs_months = std::stoi(rhs.substr(rhs.find_first_of('.') + 1));

    if (lhs_months == rhs_months)
    {
        return lhs_days <= rhs_days;
    }

    return lhs_months <= rhs_months;
}

// Returns the number of days between two dates.
int get_day_count(const std::string &start_date, const std::string &end_date)
{
    int lhs_days = std::stoi(start_date.substr(0, start_date.find_first_of('.')));
    int lhs_months = std::stoi(start_date.substr(start_date.find_first_of('.') + 1));

    int rhs_days = std::stoi(end_date.substr(0, end_date.find_first_of('.')));
    int rhs_months = std::stoi(end_date.substr(end_date.find_first_of('.') + 1));

    int lhs_day_count = 31 * lhs_months + lhs_days;
    int rhs_day_count = 31 * rhs_months + rhs_days;

    return rhs_day_count - lhs_day_count;
}

class Salon {
private:
    std::string name;   // Name of the saloon
    std::vector<std::pair<std::string, std::string>> times;     // Availability hours for the saloon

    friend class ScheduleSolver;    // Solver class can access these properties
public:
    int capacity;

    Salon() {}

    Salon(std::string &p_name)
        : name(p_name) {}

    std::string get_name() const { return name; }

    // Add availability hour
    void add_time(const std::string &p_start, const std::string &p_end) {
        times.push_back({p_start, p_end});
    }
};

class Place {
private:
    std::string name;   // Name of the place
    std::map<std::string, Salon> salons;    // Maps the names of the saloons to the saloon class instances
    std::vector<std::pair<std::string, std::string>> availability_intervals;    // Available dates for the place

    friend class ScheduleSolver;    // Solver class can access these properties
public:
    Place() {}

    Place(std::string &p_name)
        : name(p_name) {}

    // Adds a saloon with an availability time to the map. If the given saloon already exists in the map, it only takes the given time and adds it to the existing saloon.
    void add_salon(const Salon &p_salon, const std::pair<std::string, std::string> &time) {
        if (salons.find(p_salon.get_name()) == salons.end()) {
            salons[p_salon.get_name()] = p_salon;
            salons[p_salon.get_name()].add_time(time.first, time.second);
        }
        else {
            salons[p_salon.get_name()].add_time(time.first, time.second);
        }
    }

    // Adds an availability date to this place.
    void add_availability_interval(const std::string &p_start, const std::string &p_end) {
        availability_intervals.push_back({p_start, p_end});
    }

    std::string get_name() const { return name; }

    void set_salon_capacity(const std::string &salon_name, const int &new_capacity) {
        salons[salon_name].capacity = new_capacity;
    }
};

class ScheduleSolver {
    // This struct is used when finding the best schedules for each place.
    struct SalonAvailabilityData {
        std::string place_name;
        std::string salon_name;
        int salon_capacity;
        std::string starting_time;
        std::string ending_time;
    };

    // This struct is used when finding the best tour.
    struct PlaceAvailabilityData {
        std::string place_name;
        std::string starting_date;
        std::string ending_date;
    };

private:
    std::vector<Place> places;

    // Solves and finds the best schedule for each place. Returns a vector whose each element is a pair giving the daily revenue of a place, and the salons' availability data (with hours).
    std::vector<std::pair<int, std::vector<SalonAvailabilityData>>> solve_for_each_place() {
        std::map<std::string, std::vector<SalonAvailabilityData>> place_salon_times;    // Maps the names of the places to the salon availability data.

        for (Place &place : places) {
            for (auto it = place.salons.begin(); it != place.salons.end(); ++it) {
                Salon &salon = it->second;
                for (auto &time : salon.times) {
                    place_salon_times[place.name].push_back({place.name, salon.name, salon.capacity, time.first, time.second});     // Form the map data structure above.
                }
            }
        }

        std::vector<std::pair<int, std::vector<SalonAvailabilityData>>> answer;
        for (auto it = place_salon_times.begin(); it != place_salon_times.end(); ++it) {    // For each place
            std::vector<SalonAvailabilityData> &time_data = place_salon_times[it->first];
            std::sort(time_data.begin(), time_data.end(), [](const SalonAvailabilityData &lhs, const SalonAvailabilityData &rhs)
                      { return compare_hours(lhs.ending_time, rhs.ending_time); });     // Sort the salons with ascending ending times.
            
            auto find_latest_non_conflict = [&](int index) {    // This function finds the latest non-conflicting index for the given index. It uses binary search.
                int low = 0;
                int high = index - 1;
                while (low <= high) {
                    int middle = (low + high) / 2;
                    if (compare_hours(time_data[middle].ending_time, time_data[index].starting_time)) {
                        if (compare_hours(time_data[middle + 1].ending_time, time_data[index].starting_time)) {
                            low = middle + 1;
                        }
                        else {
                            return middle;
                        }
                    }
                    else {
                        high = middle - 1;
                    }
                }
                return -1;
            };

            int *previous_indexes = new int[time_data.size()];
            for (unsigned int i = 0; i < time_data.size(); i++) {
                previous_indexes[i] = find_latest_non_conflict(i);  // Form the previous indexes.
            }

            int *memo = new int[time_data.size()];  // DP memoization array
            memo[0] = time_data[0].salon_capacity;
            // Form DP memo array with a bottom-up approach
            for (unsigned int i = 1; i < time_data.size(); i++) {
                int prev_memo = 0;
                if (previous_indexes[i] != -1) {
                    prev_memo = memo[previous_indexes[i]];
                }
                memo[i] = std::max(time_data[i].salon_capacity + prev_memo, memo[i - 1]);
            }

            std::vector<SalonAvailabilityData> best_schedule;   // Best schedule vector
            int i = time_data.size() - 1;
            while (i >= 0) {
                if (memo[i] == time_data[i].salon_capacity + memo[previous_indexes[i]]) {   // Determine if ith interval will be in the solution
                    best_schedule.push_back(time_data[i]);
                    i = previous_indexes[i];
                } else if (i == 0) {
                    best_schedule.push_back(time_data[i]);
                    break;
                } else {
                    i--;    // Decrement i if current index is not in the solution (skip)
                }
            }

            int max_revenue = memo[time_data.size() - 1];

            answer.push_back({max_revenue, best_schedule});

            delete[] memo;
            delete[] previous_indexes;
        }
        return answer;
    }

    // Solves and returns the tour with max revenue. It takes a parameter to get daily revenues for each place. It returns a pair, first element is the revenue, and the second element is the place data within the schedule.
    std::pair<int, std::stack<PlaceAvailabilityData>> solve_tour(std::unordered_map<std::string, int> &daily_revenues) {
        std::vector<PlaceAvailabilityData> data;

        for (Place &place : places) {
            for (auto &interval : place.availability_intervals) {
                data.push_back({place.name, interval.first, interval.second});  // Bring all place intervals into one data structure. This makes the algorithm very straightforward.
            }
        }

        std::sort(data.begin(), data.end(), [](const PlaceAvailabilityData &lhs, const PlaceAvailabilityData &rhs)
                  { return compare_dates(lhs.ending_date, rhs.ending_date); });     // Sort the intervals with ascending ending date.

        // Finds the latest non-conflicting interval using binary search.
        auto find_latest_non_conflict = [&](int index) {
            int low = 0;
            int high = index - 1;
            while (low <= high) {
                int middle = (low + high) / 2;
                if (compare_dates(data[middle + 1].ending_date, data[index].starting_date)) {
                    low = middle + 1;
                }
                else {
                    high = middle - 1;
                }
            }
            if (compare_dates(data[low].ending_date, data[index].starting_date)) {
                return low;
            }
            return -1;
        };

        int *previous_indexes = new int[data.size()];
        for (unsigned int i = 0; i < data.size(); i++) {
            previous_indexes[i] = find_latest_non_conflict(i);
        }

        int *memo = new int[data.size()];
        for (unsigned int i = 0; i < data.size(); i++) {
            memo[i] = -1;
        }

        std::function<int(int)> opt;
        opt = [&](int index) -> int {   // Recursive DP function
            if (memo[index] == -1) {
                int total_revenue = daily_revenues[data[index].place_name] * get_day_count(data[index].starting_date, data[index].ending_date);     // Weights are 'daily revenue * day count' now
                if (index == 0) {
                    memo[0] = total_revenue;
                }
                else {
                    memo[index] = std::max(total_revenue + opt(previous_indexes[index]), opt(index - 1));
                }
            }
            return memo[index];
        };

        opt(data.size() - 1);

        int max_revenue = -1;
        int max_revenue_index;
        for (unsigned int i = 0; i < data.size(); i++) {     // Find the index with max revenue from DP table
            if (memo[i] > max_revenue) {
                max_revenue = memo[i];
                max_revenue_index = i;
            }
        }

        std::stack<PlaceAvailabilityData> best_schedule;
        int i = max_revenue_index;
        while (i != -1) {   // Get the schedule that gives the max revenue
            best_schedule.push(data[i]);
            i = previous_indexes[i];
        }

        delete[] memo;
        delete[] previous_indexes;
        
        return {max_revenue, best_schedule};
    }

public:
    ScheduleSolver() {}

    ScheduleSolver(std::vector<Place> &p_places)
        : places(p_places) {}

    // Writes the solution to the file. Returns the total revenue from the tour.
    int write_solution(const std::string &output_folder_name) {
        auto ans = solve_for_each_place();

        std::unordered_map<std::string, int> place_revenues;    // This map gives the daily revenues for each place.

        std::ofstream output_file(output_folder_name + "/best_for_eachplace.txt");
        for (auto &schedule : ans) {
            output_file << schedule.second[0].place_name << " --> " << schedule.first << std::endl;
            place_revenues[schedule.second[0].place_name] = schedule.first;
            for (auto it = schedule.second.end() - 1; it != schedule.second.begin() - 1; it--) {    // Reversely iterate since the array is reversed
                SalonAvailabilityData salon_data = *it;
                output_file << salon_data.place_name << " " << salon_data.salon_name << " " << salon_data.starting_time << " " << salon_data.ending_time << std::endl;
            }
            output_file << std::endl;
        }
        output_file.close();

        std::pair<int, std::stack<PlaceAvailabilityData>> tour_ans = solve_tour(place_revenues);

        std::ofstream tour_output_file(output_folder_name + "/best_tour.txt");
        tour_output_file << "Total Revenue --> " << tour_ans.first << std::endl;
        while(!tour_ans.second.empty()) {   // Write the tour data
            PlaceAvailabilityData tour_data = tour_ans.second.top();
            tour_ans.second.pop();
            tour_output_file << tour_data.place_name << " " << tour_data.starting_date << " " << tour_data.ending_date << std::endl;
        }
        tour_output_file.close();

        return tour_ans.first;
    }
};

class Asset {
    private:
        std::string name;
        int price;
        float value;
        
        friend class KnapsackSolver;
    public:
        Asset(const std::string& p_name, int p_price, float p_value)
            : name(p_name), price(p_price), value(p_value) { }
};

class KnapsackSolver {
    private:
        std::vector<Asset> assets;
        int budget;

        // Forms and returns the DP table.
        std::vector<std::vector<float>> solve_knapsack() {
            std::vector<std::vector<float>> memo(assets.size() + 1, std::vector<float>(budget + 1));

            for (int w = 0; w < budget + 1; w++) {  // Initialize the first row in the DP table to 0
                memo[0][w] = 0;
            }

            // Form the DP table using a bottom-up approach.
            for (unsigned int i = 1; i < assets.size() + 1; i++) {
                for (int w = 0; w < budget + 1; w++) {
                    if (assets[i - 1].price <= w) {
                        memo[i][w] = std::max(assets[i - 1].value + memo[i - 1][w - assets[i - 1].price], memo[i - 1][w]);
                    } else {
                        memo[i][w] = memo[i - 1][w];
                    }
                }
            }
            return memo;
        }
    public:
        KnapsackSolver(int p_budget) 
            : budget(p_budget) { }

        // Add an asset to the vector.
        void add_asset(const std::string& p_name, int p_price, float p_value) {
            assets.emplace_back(p_name, p_price, p_value);
        }

        // Write the solution to the file.
        void write_solution(const std::string &output_folder_name) {
            auto table = solve_knapsack();

            std::ofstream output_file(output_folder_name + "/upgrade_list.txt");
            int n = assets.size();
            int b = budget;
            output_file << "Total Value −−> " << table[n][budget] << std::endl;
            while (n > 0 && b > 0){
                if (table[n][b] != table[n - 1][b]) {   // If this row and previous row are different, the item is taken. Write it to the file.
                    output_file << assets[n - 1].name << std::endl;
                    b = b - assets[n - 1].price;
                }
                n = n - 1;
            }
            output_file.close();
        }
};

int main(int argc, char **argv) {
    if (argc == 1) {
        std::cout << "Please give a case ID." << std::endl;
        return EXIT_FAILURE;
    }

    std::map<std::string, Place> places;

    std::ifstream daily_schedule_file = std::ifstream("inputs/case_" + std::string(argv[1]) + "/daily_schedule.txt");
    std::string junk_line;
    std::getline(daily_schedule_file, junk_line); // Pass head line
    // Read the daily schedule file.
    while (daily_schedule_file.peek() != EOF) {
        std::string name;
        daily_schedule_file >> name;
        std::string salon_name;
        daily_schedule_file >> salon_name;
        std::string starts_at;
        daily_schedule_file >> starts_at;
        std::string ends_at;
        daily_schedule_file >> ends_at;
        std::getline(daily_schedule_file, junk_line, '\n'); // Get to the next line

        Salon salon = Salon(salon_name);
        if (places.find(name) == places.end()) {
            Place place(name);
            place.add_salon(salon, {starts_at, ends_at});
            places[name] = place;
        }
        else {
            places[name].add_salon(salon, {starts_at, ends_at});
        }
    }
    daily_schedule_file.close();

    std::ifstream capacity_file = std::ifstream("inputs/case_" + std::string(argv[1]) + "/capacity.txt");
    std::getline(capacity_file, junk_line); // Pass head line
    // Read the capacity file.
    while (capacity_file.peek() != EOF) {
        std::string name;
        capacity_file >> name;
        std::string salon_name;
        capacity_file >> salon_name;
        int capacity;
        capacity_file >> capacity;
        std::getline(capacity_file, junk_line, '\n'); // Get to the next line

        places[name].set_salon_capacity(salon_name, capacity);
    }
    capacity_file.close();

    std::ifstream availability_intervals_file = std::ifstream("inputs/case_" + std::string(argv[1]) + "/availability_intervals.txt");
    std::getline(availability_intervals_file, junk_line); // Pass head line
    // Read the availability intervals file.
    while (availability_intervals_file.peek() != EOF) {
        std::string name;
        availability_intervals_file >> name;
        std::string starts_at;
        availability_intervals_file >> starts_at;
        std::string ends_at;
        availability_intervals_file >> ends_at;
        std::getline(availability_intervals_file, junk_line, '\n'); // Get to the next line

        places[name].add_availability_interval(starts_at, ends_at);
    }
    availability_intervals_file.close();

    std::vector<Place> places_vec;
    for (auto it = places.begin(); it != places.end(); ++it) {
        places_vec.push_back(it->second);
    }

    ScheduleSolver schedule_solver = ScheduleSolver(places_vec);
    int total_revenue = schedule_solver.write_solution("outputs/case_" + std::string(argv[1]));

    KnapsackSolver knapsack_solver(total_revenue);
    std::ifstream assets_file = std::ifstream("inputs/case_" + std::string(argv[1]) + "/assets.txt");
    std::getline(assets_file, junk_line); // Pass head line
    // Read the assets file.
    while (assets_file.peek() != EOF) {
        std::string name;
        assets_file >> name;
        int price;
        assets_file >> price;
        float value;
        assets_file >> value;
        std::getline(assets_file, junk_line, '\n'); // Get to the next line

        knapsack_solver.add_asset(name, price, value);
    }
    assets_file.close();

    knapsack_solver.write_solution("outputs/case_" + std::string(argv[1]));

    return EXIT_SUCCESS;
}