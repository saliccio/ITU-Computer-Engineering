#include <vector>
#include <string>
#include <unordered_set>
#include <fstream>
#include <cmath>

#define GRAPH_SIZE (int)m_adjacency_matrix.size()

class Graph {
    private:
        std::vector<std::vector<bool>> m_adjacency_matrix;  // N * N boolean matrix which indicates the edges
        int m_source_idx;  // Starting node
        int m_target_idx;  // Ending node

        std::vector<int> bfs() const;  // Bfs traversal algorithm, returns the path as an integer vector
        bool dfs(std::vector<int>& path, std::unordered_set<int>& visited_nodes, int node_idx, int target_idx, int pass_count) const;  // Dfs traversal algorithm, returns the path using the 'path' reference parameter
    public:
        Graph(const std::string& input_file_path);  // Constructor, which reads the input file and forms the adjacency matrix

        void write_graph(const std::string& output_path) const;  // Writes the adjacency matrix into a file
        void write_bfs(const std::string& output_path) const;  // Writes the bfs output into a file
        void write_dfs(const std::string& output_path) const;  // Writes the dfs output into a file
};

Graph::Graph(const std::string &input_file_path) {
    std::ifstream input_file_stream(input_file_path);
    int no_of_kids;
    input_file_stream >> no_of_kids >> m_source_idx >> m_target_idx;
    int kids[no_of_kids][3];
    for (int i = 0; i < no_of_kids; i++) {
        int x, y, p;
        input_file_stream >> x >> y >> p;
        kids[i][0] = x;
        kids[i][1] = y;
        kids[i][2] = p;
    }

    m_adjacency_matrix = std::vector<std::vector<bool>>(no_of_kids);
    for (int i = 0; i < no_of_kids; i++) {
        for (int j = 0; j < no_of_kids; j++) {
            m_adjacency_matrix[i].push_back(false);
        }
    }
    for (int i = 0; i < no_of_kids - 1; i++) {
        for (int j = i + 1; j < no_of_kids; j++) {
            double distance = std::pow(kids[i][0] - kids[j][0], 2) + std::pow(kids[i][1] - kids[j][1], 2);
            if (distance <= kids[i][2] && distance <= kids[j][2]) {
                m_adjacency_matrix[i][j] = true;
                m_adjacency_matrix[j][i] = true;
            }
        }
    }
    input_file_stream.close();
}

std::vector<int> Graph::bfs() const {
    std::unordered_set<int> visited_kids;
    visited_kids.insert(m_source_idx);
    std::vector<std::vector<int>> visit_lists(GRAPH_SIZE);  // Stores the nodes to traverse at each layer
    visit_lists[0] = {m_source_idx};  // Initial node
    std::vector<int> node_paths(GRAPH_SIZE, -1);  // Stores the previous node for each node
    for (int step = 0; step < GRAPH_SIZE - 1; step++) {  // Layer iteration
        for (int node_id : visit_lists[step]) {  // Node iteration
            for (int neighbor_id = 0; neighbor_id < GRAPH_SIZE; neighbor_id++) {  // Neighbor iteration
                if (!m_adjacency_matrix[node_id][neighbor_id] || visited_kids.find(neighbor_id) != visited_kids.end()) {
                    continue;
                }

                node_paths[neighbor_id] = node_id;  // Point this node as the previous node of neighbor node

                if (neighbor_id == m_target_idx) {
                    goto loop_end;  // If target is found, break the loop
                }

                visit_lists[step + 1].push_back(neighbor_id);  // Add the neighbor to the visit list for the next layer
                visited_kids.insert(neighbor_id);  // Consider the neighbor as visited
            }
        }
    }
    loop_end:

    std::vector<int> path;
    path.push_back(m_target_idx);
    while (node_paths[path.back()] != -1) {
        path.push_back(node_paths[path.back()]);
    }
    return path;
}

bool Graph::dfs(std::vector<int> &path, std::unordered_set<int> &visited_nodes, int node_idx, int target_idx, int pass_count) const {
    visited_nodes.insert(node_idx);  // Consider the node as visited
    if (pass_count > 1 && m_adjacency_matrix[node_idx][target_idx]) {  // If the target can be visited from the current node, and also the edge count is greater than 1 (to prevent using the same edge twice), push the final nodes and return true to indicate success.
        path.push_back(target_idx);
        path.push_back(node_idx);
        return true;
    }
    for (int i = 0; i < GRAPH_SIZE; i++) {
        if (!m_adjacency_matrix[node_idx][i] || visited_nodes.find(i) != visited_nodes.end()) {  // If there is no connection or the node has already been visited, skip
            continue;
        }

        bool is_cycle_found = dfs(path, visited_nodes, i, target_idx, pass_count + 1);  // Continue traversing to see if there is a cycle
        if (is_cycle_found) {  // If there is a cycle, push the current node to the path (the path vector will be reversed since the deepest nodes are added first, since dfs is used)
            path.push_back(node_idx);
            return true;
        }
    }
    return false;
}

void Graph::write_graph(const std::string &output_path) const {
    std::ofstream graph_file_stream(output_path);
    graph_file_stream << "Graph:" << std::endl;
    for (int i = 0; i < GRAPH_SIZE; i++) {
        for (int j = 0; j < GRAPH_SIZE; j++) {
            graph_file_stream << m_adjacency_matrix[i][j] << " ";  // Write the graph adjacency matrix elements into the file
        }
        graph_file_stream << std::endl;
    }
    graph_file_stream.close();
}

void Graph::write_bfs(const std::string &output_path) const {
    std::vector<int> path = bfs();

    std::ofstream bfs_file_stream(output_path);
    bfs_file_stream << "BFS:" << std::endl
                    << path.size() - 1 << " ";

    for (auto i = path.rbegin(); i < path.rend(); i++) {  // Reversely iterate since the path vector is reversed
        bfs_file_stream << *i;
        if (i != path.rend() - 1) {
            bfs_file_stream << "->";
        }
    }
    bfs_file_stream << std::endl;
    bfs_file_stream.close();
}

void Graph::write_dfs(const std::string &output_path) const {
    std::vector<int> path;
    std::unordered_set<int> visited_nodes;
    bool is_path_found = dfs(path, visited_nodes, m_source_idx, m_source_idx, 0);
    std::ofstream dfs_file_stream(output_path);
    dfs_file_stream << "DFS:" << std::endl;
    if (is_path_found) {
        dfs_file_stream << path.size() - 1 << " ";
        for (unsigned int i = path.size() - 1; i > 0; i--)  // The path vector is reversely output, since the vector is reversed
        {
            dfs_file_stream << path[i] << "->";
        }
        dfs_file_stream << path[0];
    } else {
        dfs_file_stream << "-1";
    }
    dfs_file_stream << std::endl;
    dfs_file_stream.close();
}

int main(int argc, char** argv){
    Graph graph(argv[1]);
    graph.write_graph("graph.txt");
    graph.write_bfs("bfs.txt");
    graph.write_dfs("dfs.txt");

    exit(0);
}