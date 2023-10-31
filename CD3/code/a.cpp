#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

struct Node {
    int id;
    float cost;
};

struct Edge {
    int target;
    float weight;
};

using Graph = std::unordered_map<int, std::vector<Edge>>;

Node a_star(Graph& graph, int start, int goal) {
    std::unordered_map<int, float> cost_so_far;
    std::priority_queue<Node> frontier;
    frontier.push({start, 0});

    cost_so_far[start] = 0;

    while (!frontier.empty()) {
        Node current = frontier.top();
        frontier.pop();

        if (current.id == goal) {
            return current;
        }

        for (Edge& next : graph[current.id]) {
            float new_cost = cost_so_far[current.id] + next.weight;
            if (!cost_so_far.count(next.target) || new_cost < cost_so_far[next.target]) {
                cost_so_far[next.target] = new_cost;
                float priority = new_cost; // Thêm heuristic vào đây để tạo thành A* thực sự
                frontier.push({next.target, priority});
            }
        }
    }

    return {-1, -1}; // Không tìm thấy đường đi
}

int main() {
    Graph graph;
    
    // Thêm các nút và cạnh vào đồ thị
    // graph[0].push_back({1, 1.0f});
    // graph[0].push_back({2, 1.0f});
    
    Node result = a_star(graph, 0, 2);
    
    if (result.id != -1) {
        std::cout << "Đã tìm thấy đường đi từ nút 0 đến nút 2 với chi phí: " << result.cost << std::endl;
    } else {
        std::cout << "Không tìm thấy đường đi từ nút 0 đến nút 2." << std::endl;
    }
    
    return 0;
}
