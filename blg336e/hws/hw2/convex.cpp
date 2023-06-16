#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

struct point {
    int real_index;
    int x;
    int y;
};
using points = std::vector<point>;

class ConvexHull {
    private:
        points cities;

        // Finds upper or lower tangent and returns two point indexes, first is the index of leftmost point, and second is the index of rightmost point
        std::pair<int, int> find_tangent(bool isUpper, points& left_hull, points& right_hull) {
            float x_median;
            if (left_hull.size() == 1 && right_hull.size() == 1) {  // Base case 1
                return {0, 0};
            }
            if (left_hull.size() + right_hull.size() == 3) {    // Base case 2 (left size=1, right size=2 OR left size=2, right size=1)
                if (left_hull.size() == 2) {
                    float slope1 = ((float)left_hull[0].y - left_hull[1].y) / ((float)left_hull[0].x - left_hull[1].x);
                    float slope2 = ((float)left_hull[0].y - right_hull[0].y) / ((float)left_hull[0].x - right_hull[0].x);
                    if (slope1 > slope2) {
                        return isUpper ? std::pair<int, int>(1, 0) : std::pair<int, int>{0, 0};
                    } else {
                        return isUpper ? std::pair<int, int>(0, 0) : std::pair<int, int>(1, 0);
                    }
                } else if (right_hull.size() == 2) {
                    float slope1 = ((float)left_hull[0].y - right_hull[0].y) / ((float)left_hull[0].x - right_hull[0].x);
                    float slope2 = ((float)left_hull[0].y - right_hull[1].y) / ((float)left_hull[0].x - right_hull[1].x);
                    if (slope1 > slope2) {
                        return isUpper ? std::pair<int, int>(0, 0) : std::pair<int, int>{0, 1};
                    } else {
                        return isUpper ? std::pair<int, int>(0, 1) : std::pair<int, int>(0, 0);
                    }
                }
            }
            
            auto line_func = [&](point& left_hull_point, point& right_hull_point) {     // This function computes the y values at x median value for candidate tangent lines [returns f(x_median) where f is a candidate tangent line]
                return (((float)left_hull_point.y - right_hull_point.y) / ((float)left_hull_point.x - right_hull_point.x)) * (x_median - left_hull_point.x) + left_hull_point.y;
            };
            int left_size = left_hull.size();
            int right_size = right_hull.size();
            int left_hull_index = 0;
            int right_hull_index = 0;
            
            // Find the rightmost node for the left hull
            for (int i = 0; i < left_size; i++) {
                if (left_hull[i].x > left_hull[left_hull_index].x) {
                    left_hull_index = i;
                }
            }

            // Find the leftmost node for the right hull
            for (int i = 0; i < right_size; i++) {
                if (right_hull[i].x < right_hull[right_hull_index].x) {
                    right_hull_index = i;
                }
            }

            x_median = (left_hull[left_hull_index].x + right_hull[right_hull_index].x) / 2.0;   // Median x value which is between the left and right hulls
            float median_line_y = line_func(left_hull[left_hull_index], right_hull[right_hull_index]);  // y value at median for current candidate tangent points
            if (isUpper) {  // Upper tangent logic
                float left_hull_next_median_y;   // Median y value if counterclockwise next point of the current point in left hull is picked
                float right_hull_next_median_y;   // Median y value if clockwise next point of the current point in right hull is picked
                auto update_median_line_values = [&]() {
                    left_hull_next_median_y = line_func(left_hull[(left_hull_index + 1) % left_size], right_hull[right_hull_index]);
                    right_hull_next_median_y = line_func(left_hull[left_hull_index], right_hull[(right_size + right_hull_index - 1) % right_size]);
                };
                update_median_line_values();    // Initial update

                // Continue until we reached to maximum median y value
                while (left_hull_next_median_y >= median_line_y || right_hull_next_median_y >= median_line_y) {
                    if (left_hull_next_median_y >= median_line_y) {     // If the next node in the left hull caused a greater value in median y
                        left_hull_index = (left_hull_index + 1) % left_size;    // Counterclockwise next point in left hull
                        median_line_y = left_hull_next_median_y;    // Update median y to the greater value 
                        update_median_line_values();    // Update next points' median y values to compare them in the next check
                    } else {     // If the next node in the right hull caused a greater value in median y
                        right_hull_index = (right_size + right_hull_index - 1) % right_size;    // Clockwise next point in right hull
                        median_line_y = right_hull_next_median_y;
                        update_median_line_values();
                    }
                }
            } else {    // General logic for lower tangent is the same as upper tangent (like above). Now we go clockwise for left hull, and counterclockwise for right hull. Also instead of maximum, we look for minimum median y value now.
                float median_line_lower_left;
                float median_line_lower_right;
                auto update_median_line_values = [&]() {
                    median_line_lower_left = line_func(left_hull[(left_size + left_hull_index - 1) % left_size], right_hull[right_hull_index]);
                    median_line_lower_right = line_func(left_hull[left_hull_index], right_hull[(right_hull_index + 1) % right_size]);
                };
                update_median_line_values();
                while (median_line_lower_left <= median_line_y || median_line_lower_right <= median_line_y) {
                    if (median_line_lower_left <= median_line_y) {
                        left_hull_index = (left_size + left_hull_index - 1) % left_size;
                        median_line_y = median_line_lower_left;
                        update_median_line_values();
                    } else {
                        right_hull_index = (right_hull_index + 1) % right_size;
                        median_line_y = median_line_lower_right;
                        update_median_line_values();
                    }
                }
            }
            return {left_hull_index, right_hull_index};     // Return the line in terms of point indexes
        }
        
        // Merges given two hulls
        points merge(points& left_hull, points& right_hull) {
            std::pair<int, int> upper_tangent = find_tangent(true, left_hull, right_hull);
            std::pair<int, int> lower_tangent = find_tangent(false, left_hull, right_hull);
            points merged_hull;     // This will be our merged hull (Return value)
            int hull_index = upper_tangent.first;   // Start from the upper tangent line's left point
            merged_hull.push_back(left_hull[hull_index]);   // And push it to the hull
            while (hull_index != lower_tangent.first) {     // Continue pushing left hull's points until reaching beyond lower tangent line's left point (All points of the left hull that will be included in the merged hull)
                hull_index = (hull_index + 1) % left_hull.size();
                merged_hull.push_back(left_hull[hull_index]);
            }
            merged_hull.push_back(right_hull[lower_tangent.second]);     // Pass to the lower tangent line's right point
            hull_index = lower_tangent.second;
            while (hull_index != upper_tangent.second) {    // Continue pushing right hull's points until reaching beyond upper tangent line's right point (All points of the right hull that will be included in the merged hull)
                hull_index = (hull_index + 1) % right_hull.size();
                merged_hull.push_back(right_hull[hull_index]);
            }
            return merged_hull;
        }

        // Input vector must be sorted ascending.
        points solve(points& point_vector, int start_index, int end_index) {
            if (start_index == end_index) {     // Base case
                points hull;
                hull.push_back(point_vector[start_index]);
                return hull;
            }
            int middle_index = (start_index + end_index) / 2;
            points left_hull = solve(point_vector, start_index, middle_index);  // Left-part solution
            points right_hull = solve(point_vector, middle_index + 1, end_index);   // Right-part solution
            return merge(left_hull, right_hull);    // Merged solution
        }
    public:
        // Get input file name and construct the cities data structure.
        ConvexHull(std::string input_file_name) {
            std::ifstream input_file(input_file_name);
            int no_of_cities;
            input_file >> no_of_cities;
            cities.reserve(no_of_cities);

            std::string temp;
            std::getline(input_file, temp);  // Pass prim inputs
            std::getline(input_file, temp);

            // Read city inputs and push them to the vector
            for (int i = 0; i < no_of_cities; i++) {
                int x, y;
                input_file >> x >> y;
                std::getline(input_file, temp);
                cities.push_back({i, x, y});
            }
            std::sort(cities.begin(), cities.end(), [](point& value1, point& value2){ return value1.x < value2.x; });   // Sort points ascending on their x values (Using a lambda function)
            input_file.close();
        }

        // Solves the problem and writes the solution to given file name.
        void write_solution(std::string output_file_name) {
            std::ofstream output_file(output_file_name);
            points solution = solve(cities, 0, cities.size() - 1);
            output_file << solution.size() << std::endl;
            
            // Get the city index with minimum x
            int min_x_index = 0;
            for (int i = 0; i < (int)solution.size(); i++) {
                if (solution[i].x < solution[min_x_index].x) {
                    min_x_index = i;
                }
            }

            // Go counterclockwise and write all of the point indexes on the hull
            int index = min_x_index;
            output_file << solution[index].real_index << "->";
            index = (index + 1) % solution.size();
            while(index != min_x_index) {
                output_file << solution[index].real_index << "->";
                index = (index + 1) % solution.size();
            }
            output_file << solution[min_x_index].real_index << std::endl;
            output_file.close();
        }
};

int main(int argc, char** argv){
    ConvexHull convex_hull(argv[1]);
    convex_hull.write_solution("convex.txt");

    return 0;
}