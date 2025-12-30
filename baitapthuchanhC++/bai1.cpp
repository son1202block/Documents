#include <iostream>
#include <vector>
#include <limits>
#include <string>
#include <numeric>
#include <algorithm>

const int INF = std::numeric_limits<int>::max();

const int N_CITIES = 6;

const std::vector<std::vector<int>> COST_MATRIX = {
    {INF, 20, 42, 30, 6, 25},
    {12, INF, 16, 7, 33, 19},
    {23, 5, INF, 28, 14, 9},
    {12, 9, 24, INF, 31, 15},
    {14, 7, 21, 15, INF, 45},
    {36, 15, 16, 5, 205, INF}
};

int calculate_cost(const std::vector<int>& route) {
    long long total_cost = 0;
    int num_steps = route.size();
    if (num_steps == 0) return INF;

    for (int i = 0; i < num_steps; ++i) {
        int start_city = route[i];
        int end_city = route[(i + 1) % num_steps];
        
        int start_index = start_city - 1;
        int end_index = end_city - 1;
        
        if (start_index < 0 || start_index >= N_CITIES || end_index < 0 || end_index >= N_CITIES) {
            return INF;
        }

        int cost = COST_MATRIX[start_index][end_index];
        if (cost == INF) {
            return INF;
        }
        total_cost += cost;
        if (total_cost > INF) return INF;
    }
    return (int)total_cost;
}

void print_route(const std::vector<int>& route) {
    for (size_t i = 0; i < route.size(); ++i) {
        std::cout << route[i];
        if (i < route.size() - 1) {
            std::cout << " -> ";
        }
    }
    if (!route.empty()) {
        std::cout << " -> " << route[0];
    }
}

std::vector<int> GTS1_Greedy(int start_city) {
    std::vector<int> route;
    std::vector<bool> visited(N_CITIES + 1, false);

    int current_city = start_city;
    route.push_back(current_city);
    visited[current_city] = true;

    while (route.size() < N_CITIES) {
        int next_city = -1;
        int min_cost = INF;

        for (int neighbor = 1; neighbor <= N_CITIES; ++neighbor) {
            if (!visited[neighbor]) {
                int start_index = current_city - 1;
                int neighbor_index = neighbor - 1;
                int cost = COST_MATRIX[start_index][neighbor_index];
                
                if (cost < min_cost) {
                    min_cost = cost;
                    next_city = neighbor;
                }
            }
        }

        if (next_city == -1) {
            return {}; // Không tìm thấy đường đi hợp lệ
        }

        current_city = next_city;
        route.push_back(current_city);
        visited[current_city] = true;
    }

    return route;
}

void gts2_solver(int num_trials) {
    int best_cost = INF;
    std::vector<int> best_route;
    
    std::cout << "--- QUA TRINH TIM KIEM THEO THUAT TOAN GTS2 ---" << std::endl;
    
    for (int k = 1; k <= num_trials; ++k) {
    
        std::vector<int> current_route = GTS1_Greedy(k);
        
        if (current_route.empty()) {
            std::cout << "\nBuoc " << k << ": Khong the tao hanh trinh tu thanh pho " << k << std::endl;
            continue;
        }

        int current_cost = calculate_cost(current_route);
        
        std::cout << "\nBuoc " << k << ": Hanh trinh duoc tao: ";
        print_route(current_route);
        std::cout << "\nChi phi: " << current_cost << std::endl;
        
        if (current_cost < best_cost) {
            best_cost = current_cost;
            best_route = current_route;
            std::cout << "==> Cap nhat: Chi phi Tot nhat moi = " << best_cost << std::endl;
        } else {
            std::cout << "Chi phi hien tai (" << current_cost << ") khong tot hon chi phi tot nhat (" << best_cost << ")." << std::endl;
        }
    }

    std::cout << "\n--- KET LUAN ---" << std::endl;
    if (!best_route.empty()) {
        std::cout << "Hanh trinh Tot nhat: ";
        print_route(best_route);
        std::cout << "\nChi phi: " << best_cost << std::endl;
    } else {
        std::cout << "Khong tim thay hanh trinh hop le." << std::endl;
    }
}

int main() {
    int p;
    std::cout << "Nhap so lan lap (p): ";
    std::cin >> p;
    gts2_solver(p);
    return 0;
}