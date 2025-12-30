#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <map>
#include <algorithm>
#include <string>
#include <tuple>

using namespace std;

// =============================================================================
// 1. ĐỊNH NGHĨA TRẠNG THÁI & CẤU TRÚC DỮ LIỆU
// =============================================================================

// Trạng thái Đích (Goal) - Dùng 0 cho ô trống
const vector<vector<int>> GOAL_STATE = {
    {1, 2, 3},
    {5, 7, 6},
    {0, 4, 8} // Goal: Ô trống ở Hàng 3, Cột 1
};

// Vị trí đích cố định cho mỗi số (dùng cho Manhattan Distance)
// Key: Số, Value: {Hàng, Cột} đích
const map<int, pair<int, int>> GOAL_POSITIONS = {
    {1, {0, 0}}, {2, {0, 1}}, {3, {0, 2}},
    {5, {1, 0}}, {7, {1, 1}}, {6, {1, 2}},
    {0, {2, 0}}, // Ô trống ở đích (Hàng 3, Cột 1)
    {4, {2, 1}}, {8, {2, 2}} 
};

struct Node {
    vector<vector<int>> state;
    int g; // Chi phí thực tế (số bước)
    int h; // Heuristic (Manhattan Distance)
    int f; // Tổng chi phí (f = g + h)
    Node* parent;
    string action; // Hành động dẫn đến nút này

    // Constructor
    Node(vector<vector<int>> s, int current_g, Node* p = nullptr, string a = "") 
        : state(s), g(current_g), parent(p), action(a) {
        h = calculate_h(s);
        f = g + h;
    }

    // Hàm tính Heuristic: Manhattan Distance
    int calculate_h(const vector<vector<int>>& s) const {
        int h = 0;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                int val = s[i][j];
                
                if (val != 0) {
                    // Lấy tọa độ đích của giá trị val
                    pair<int, int> goal_coords = GOAL_POSITIONS.at(val);
                    int goal_r = goal_coords.first;
                    int goal_c = goal_coords.second;

                    // Tính khoảng cách Manhattan: |dr| + |dc|
                    h += abs(i - goal_r) + abs(j - goal_c);
                }
            }
        }
        return h;
    }
};

// Hàm so sánh cho Priority Queue (Min-Heap dựa trên f)
struct CompareNode {
    bool operator()(const Node* n1, const Node* n2) const {
        return n1->f > n2->f; // Trả về true nếu n1 có ưu tiên THẤP hơn n2
    }
};

// =============================================================================
// 2. CÁC HÀM HỖ TRỢ
// =============================================================================

pair<int, int> find_zero(const vector<vector<int>>& state) {
    /** Tìm vị trí (row, col) của ô trống (0). */
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (state[i][j] == 0) {
                return {i, j};
            }
        }
    }
    return {-1, -1};
}

void print_state(const vector<vector<int>>& state) {
    /** In trạng thái bàn cờ ra console. */
    for (const auto& row : state) {
        for (int val : row) {
            if (val == 0) {
                cout << "  " << " "; // In ô trống
            } else {
                cout << val << " ";
            }
        }
        cout << endl;
    }
}

void reconstruct_path(Node* goal_node) {
    vector<Node*> path;
    Node* current = goal_node;
    while (current != nullptr) {
        path.push_back(current);
        current = current->parent;
    }
    reverse(path.begin(), path.end());

    cout << "\n=== ĐƯỜNG ĐI NGẮN NHẤT (" << path.size() - 1 << " bước) ===" << endl;

    for (size_t i = 0; i < path.size(); ++i) {
        cout << "\n--- Bước " << i << " ---" << endl;
        cout << "Trạng thái:\n";
        print_state(path[i]->state);
        cout << "Chi phí (g): " << path[i]->g << endl;
        cout << "Heuristic (h): " << path[i]->h << endl;
        cout << "Tổng (f): " << path[i]->f << endl;
        cout << "Hành động: " << (path[i]->action.empty() ? "Bắt đầu" : path[i]->action) << endl;
    }
}

void a_star_search(const vector<vector<int>>& start_state) {
    
    // Khởi tạo nút Bắt đầu
    Node* start_node = new Node(start_state, 0);

    // Open List (Hàng đợi Ưu tiên)
    priority_queue<Node*, vector<Node*>, CompareNode> open_list;
    open_list.push(start_node);

    // Closed List: map<Trạng thái, g_value> (Kiểm tra trạng thái đã thăm và tìm đường đi tốt hơn)
    map<vector<vector<int>>, int> closed_list;
    closed_list[start_state] = 0;

    int expanded_count = 0;

    // Các hướng di chuyển: {dr, dc, action_name}
    const vector<tuple<int, int, string>> moves = {
        {-1, 0, "Lên"}, {1, 0, "Xuống"}, {0, -1, "Trái"}, {0, 1, "Phải"}
    };

    while (!open_list.empty()) {
        // Lấy nút có f nhỏ nhất (ưu tiên cao nhất)
        Node* current_node = open_list.top();
        open_list.pop();

        expanded_count++;

        // 1. KIỂM TRA ĐÍCH
        if (current_node->state == GOAL_STATE) {
            cout << "🎉 Đã tìm thấy Đích sau " << expanded_count << " lần mở rộng nút!" << endl;
            reconstruct_path(current_node);
            return;
        }

        // 2. MỞ RỘNG NÚT (Tạo các nút con)
        pair<int, int> zero_pos = find_zero(current_node->state);
        int r = zero_pos.first;
        int c = zero_pos.second;

        for (const auto& move : moves) {
            int dr = get<0>(move);
            int dc = get<1>(move);
            string action_name = get<2>(move);

            int nr = r + dr;
            int nc = c + dc;

            // Kiểm tra tính hợp lệ của di chuyển
            if (nr >= 0 && nr < 3 && nc >= 0 && nc < 3) {
                // Tạo trạng thái mới bằng cách hoán đổi
                vector<vector<int>> new_state = current_node->state;
                swap(new_state[r][c], new_state[nr][nc]);

                int new_g = current_node->g + 1;
                
                // 3. XỬ LÝ TRẠNG THÁI CON
                bool should_expand = true;

                // Nếu trạng thái đã có trong Closed List VÀ g_mới KHÔNG tốt hơn g_cũ, bỏ qua
                if (closed_list.count(new_state) && closed_list.at(new_state) <= new_g) {
                    should_expand = false;
                }
                
                if (should_expand) {
                    // Tạo nút con và thêm vào Open List
                    Node* new_node = new Node(new_state, new_g, current_node, action_name);
                    open_list.push(new_node);
                    closed_list[new_state] = new_g;
                }
            }
        }
    }

    cout << "Không tìm thấy đường đi." << endl;
}

// =============================================================================
// 4. HÀM MAIN
// =============================================================================

int main() {
    // START: 1 2 3, 4 5 6, 7 0 8 (Ô trống ở Hàng 3, Cột 2)
    const vector<vector<int>> START_STATE_IMAGE = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 0, 8} 
    };
    
    cout << "Bắt đầu Thuật toán TACI..." << endl;
    a_star_search(START_STATE_IMAGE);

    // Lưu ý: Trong C++, cần thêm cơ chế dọn dẹp bộ nhớ (delete) cho các con trỏ Node* đã cấp phát (new Node(...)) 
    // để tránh rò rỉ bộ nhớ, nhưng được bỏ qua ở đây để giữ mã tập trung vào logic thuật toán.

    return 0;
}