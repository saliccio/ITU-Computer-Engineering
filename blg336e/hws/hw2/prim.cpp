#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

struct City {
    int index;
    int pount;
    std::vector<std::pair<int, City*>> adj;     // Pair of plow and city pointer

    City(int index, int pount) : index(index), pount(pount) {}

    int operator - (const City& rhs) const {    // Pount difference operator
        return std::abs(pount - rhs.pount);
    }
};

class Prim {
    private:
        int no_of_cities;
        int no_of_bakeries;
        float threshold;
        std::vector<int> source_city_indexes;   // ith bakery will start at city with index source_city_indexes[i]
        std::vector<City*> cities;      // ith city's pointer is at cities[i]

        // Solves the problem and returns city vectors for each bakery
        std::vector<std::vector<City*>> solve() {
            auto pq_comparator = [](std::pair<int, City*> city1, std::pair<int, City*> city2) {     // This custom comparator function will first check by weights (plows), and if weights are the same, it will prioritize lower indexes.
                if (city1.first == city2.first) {
                    return city1.second->index > city2.second->index;
                }
                return city1.first < city2.first;
            };

            typedef std::priority_queue<std::pair<int, City*>, std::vector<std::pair<int, City*>>, decltype(pq_comparator)> priority_queue_type;
            std::vector<priority_queue_type> bakery_queues(no_of_bakeries, priority_queue_type(pq_comparator));

            for (int i = 0; i < no_of_bakeries; i++) {
                City* source_city = cities[source_city_indexes[i]];
                bakery_queues[i].push({0, source_city});    // Initialize starting node weights as 0
            }

            std::vector<std::vector<City*>> solution(no_of_bakeries);
            std::vector<bool> occupied_cities(no_of_cities, false);     // Boolean vector that stores whether the cities have bakery branches or not
            int finished_bakery_count = 0;  // If finished_bakery_count reaches no_of_bakeries, this means all bakeries' jobs have been done, so the solution is done
            while (finished_bakery_count != no_of_bakeries) {
                finished_bakery_count = 0;
                for (int i = 0; i < no_of_bakeries; i++) {
                    if (bakery_queues[i].size() == 0) {     // If no city exists at priority queue for bakery i, this means it cannot expand more, therefore finished its job
                        finished_bakery_count++;
                        continue;
                    }
                    
                    City* city = NULL;
                    while (bakery_queues[i].size() != 0) {
                        City* next_city = bakery_queues[i].top().second;
                        bakery_queues[i].pop();     // Pop the next city from the priority queue of bakery i
                        if (!occupied_cities[next_city->index]) {    // And if it is not occupied, this means we found our next city, and continue further processing on it
                            city = next_city;
                            break;
                        }
                    }
                    if (city == NULL) {     // If we could not pick an unoccupied city, this means this bakery cannot expand further, and finished its job
                        finished_bakery_count++;
                        continue;
                    }
                    
                    // If a city is picked, below lines do Prim's logic on it
                    solution[i].push_back(city);    // The city is added to the solution list for bakery i
                    occupied_cities[city->index] = true;    // The city is marked as occupied

                    for (std::pair<int, City*>& adj_city: city->adj) {  // For each adjacent city of the picked city
                        if (occupied_cities[adj_city.second->index]) {  // If the adjacent is occupied, skip it
                            continue;
                        }
                        bakery_queues[i].push(adj_city);    // If not occupied, push the adjacent city to the priority queue for bakery i to visit it later (If its plow is higher, it will be visited sooner since we use a priority queue)
                    }
                }
            }
            return solution;
        }
    public:
        // Constructor reads the inputs and forms the graph
        Prim(std::string input_file_name) {
            std::ifstream input_file(input_file_name);
            input_file >> no_of_cities >> no_of_bakeries >> threshold;
            for (int i = 0; i < no_of_bakeries; i++) {
                int source_index;
                input_file >> source_index;
                source_city_indexes.push_back(source_index);
            }
            for (int i = 0; i < no_of_cities; i++) {
                int x, y, pount;
                input_file >> x >> y >> pount;
                cities.push_back(new City(i, pount));
            }

            // Form the graph
            for (int i = 0; i < no_of_cities - 1; i++) {
                for (int j = i + 1; j < no_of_cities; j++) {
                    int plow = *cities[i] - *cities[j];     // Custom operator is used
                    if (plow > 0 && plow <= threshold * (cities[i]->pount + cities[j]->pount) / 2.0) {  // If two cities fulfill the conditions, they would have an edge connecting them
                        cities[i]->adj.push_back({plow, cities[j]});    // Add the cities to each other's adjacency vector along with the weights (plows)
                        cities[j]->adj.push_back({plow, cities[i]});
                    }
                }
            }
            input_file.close();
        }

        // Solve the problem and write the solution to the given input file name
        void write_solution(std::string output_file_name) {
            std::ofstream output_file(output_file_name);
            std::vector<std::vector<City*>> solution = solve();

            // Write the city vectors for each bakery
            for (int i = 0; i < no_of_bakeries; i++) {
                std::vector<City*> branches = solution[i];
                output_file << "k" << i << " " << branches.size() << std::endl;
                for (int j = 0; j < (int)branches.size(); j++) {
                    output_file << branches[j]->index;
                    if (j != (int)branches.size() - 1) {
                        output_file << "->";
                    }
                }
                output_file << std::endl;
            }
            output_file.close();
        }

        ~Prim() {   // Delete city pointers at destruction to avoid memory leak
            for (auto& city_ptr : cities) {
                delete city_ptr;
                city_ptr = NULL;
            }
        }
};

int main(int argc, char** argv){
    Prim prim(argv[1]);
    prim.write_solution("prim.txt");

    return 0;
}