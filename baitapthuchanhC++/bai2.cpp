#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <iomanip> // Dùng để định dạng in ấn

using namespace std;

class Vertex {
public:
    string name;       
    int degree;        
    int color;         
    
    Vertex(string n) : name(n), degree(0), color(0) {}
};
bool compareByDegree(const Vertex* a, const Vertex* b) {
    // Nếu bậc bằng nhau, sắp xếp theo tên để đảm bảo thứ tự ổn định (tùy chọn)
    if (a->degree != b->degree) {
        return a->degree > b->degree; 
    }
    return a->name < b->name;
}

class Graph {
private:
    map<string, Vertex*> vertices;
    map<string, vector<string>> adj_list;
    // Lịch sử tô màu và bậc sau mỗi bước
    vector<map<string, int>> history;

public:
    Graph() {}
    ~Graph() {
        for (auto& pair : vertices) delete pair.second;
    }

    void addVertex(const string& name) {
        if (vertices.find(name) == vertices.end()) {
            vertices[name] = new Vertex(name);
            // Khởi tạo danh sách kề rỗng nếu chưa có
            if (adj_list.count(name) == 0) adj_list[name] = vector<string>();
        }
    }

    void addEdge(const string& u, const string& v) {
        // Đảm bảo các đỉnh tồn tại trước
        addVertex(u);
        addVertex(v);
        // Thêm cạnh ở cả hai chiều (vô hướng)
        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }
    
    // Tính bậc ban đầu
    void calculateInitialDegrees() {
        for (const auto& pair : adj_list) {
            if (vertices.count(pair.first)) {
                vertices[pair.first]->degree = (int)pair.second.size();
            }
        }
    }

    // Ghi lại trạng thái tô màu và bậc hiện tại
    map<string, int> logState(const vector<string>& all_names, const string& last_colored = "") {
        map<string, int> current_state;
        for (const string& name : all_names) {
            Vertex* v = vertices[name];
            // Đánh dấu đỉnh vừa được tô màu là 0 (hoặc màu của nó)
            if (v->color > 0) {
                 // Gán giá trị 0 cho đỉnh đã tô màu (như trong bảng Hạ Bậc)
                current_state[name] = 0; 
            } else {
                current_state[name] = v->degree;
            }
        }
        history.push_back(current_state);
        return current_state;
    }

    // Thuật toán Tô màu Tham Lam (Có theo dõi Hạ bậc)
    void colorGraphAndLog() {
        calculateInitialDegrees();
        history.clear();

        vector<string> all_names;
        for (const auto& pair : vertices) all_names.push_back(pair.first);
        sort(all_names.begin(), all_names.end()); // Sắp xếp theo tên để in bảng ổn định

        // 1. Tạo danh sách làm việc từ các đối tượng Vertex
        vector<Vertex*> remaining_nodes;
        for (const auto& pair : vertices) remaining_nodes.push_back(pair.second);

        // --- GHI LẠI BẬC BAN ĐẦU ---
        map<string, int> initial_degrees;
        for(Vertex* v : remaining_nodes) initial_degrees[v->name] = v->degree;
        history.push_back(initial_degrees); 
        
        // Vòng lặp chính tiếp diễn cho đến khi không còn đỉnh nào
        int step = 1;
        while (!remaining_nodes.empty()) {
            // Sắp xếp theo Bậc giảm dần
            sort(remaining_nodes.begin(), remaining_nodes.end(), compareByDegree);

            // 2. Chọn đỉnh đầu tiên (Bậc cao nhất)
            Vertex* current_v = remaining_nodes[0];
            
            // 3. Tô màu Tham Lam
            set<int> neighbor_colors;
            for (const string& neighbor_name : adj_list.at(current_v->name)) {
                // Chỉ kiểm tra các đỉnh kề đã được tô màu
                if (vertices.count(neighbor_name) && vertices[neighbor_name]->color > 0) {
                    neighbor_colors.insert(vertices[neighbor_name]->color);
                }
            }

            int color = 1;
            while (neighbor_colors.count(color)) {
                color++;
            }
            current_v->color = color;
            
            // 4. Cập nhật trạng thái và Hạ Bậc (Chuẩn bị cho bước tiếp theo)
            
            // Loại bỏ đỉnh vừa tô màu
            remaining_nodes.erase(remaining_nodes.begin());

            // Hạ bậc các đỉnh kề CHƯA TÔ MÀU
            for (const string& neighbor_name : adj_list.at(current_v->name)) {
                 if (vertices.count(neighbor_name) && vertices[neighbor_name]->color == 0) {
                    vertices[neighbor_name]->degree -= 1;
                 }
            }
            
            // Ghi lại trạng thái bậc sau khi hạ bậc
            logState(all_names, current_v->name);
            step++;
        }
    }

    // Hàm in kết quả lịch trình và bảng Hạ bậc
    void printResults() const {
        vector<string> names;
        for (const auto& pair : vertices) names.push_back(pair.first);
        sort(names.begin(), names.end()); 
        
        cout << "\n=======================================================\n";
        cout << "              BAO CAO TO MAU DO THI (HA BAC)             \n";
        cout << "=======================================================\n";

        // In hàng Tô Màu
        cout << setw(12) << "Tô màu:";
        for (const string& name : names) {
            cout << setw(4) << vertices.at(name)->color;
        }
        cout << endl;

        // In tiêu đề cột (a, b, c...)
        cout << setw(12) << "Đỉnh:";
        for (const string& name : names) {
            cout << setw(4) << name;
        }
        cout << endl;
        cout << string(12 + names.size() * 4, '-') << endl;


        // In các hàng Bậc và Hạ bậc
        for (size_t i = 0; i < history.size(); ++i) {
            if (i == 0) {
                cout << setw(12) << "Bậc:";
            } else {
                cout << setw(12) << "Hạ bậc " + to_string(i) + ":";
            }
            
            for (const string& name : names) {
                cout << setw(4) << history[i].at(name);
            }
            cout << endl;
        }
        cout << string(12 + names.size() * 4, '-') << endl;

        // In lịch trình tổng hợp
        printSchedule();
    }
    
    void printSchedule() const {
        map<int, vector<string>> schedules; 
        int max_session = 0;

        for (const auto& pair : vertices) {
            schedules[pair.second->color].push_back(pair.first);
            if (pair.second->color > max_session) {
                max_session = pair.second->color;
            }
        }

        cout << "\n--- LICH TRINH TONG HOP ---\n";
        for (const auto& pair : schedules) {
            cout << "Buoi " << pair.first << ": ";
            cout << "[" << pair.second[0];
            for (size_t i = 1; i < pair.second.size(); ++i) {
                cout << ", " << pair.second[i];
            }
             cout << "]\n";
        }
        cout << "\n=> TONG SO BUOI TOI THIEU CAN THIET: " << max_session << endl;
    }
};

int main() {
    Graph meeting_schedule;
    
    // KHAI BÁO DỮ LIỆU ĐỒ THỊ (Dựa trên Ma trận Kề M[i][j]=1 trong hình 2)
    
    vector<string> all_meetings = {"a", "b", "c", "d", "e", "f", "g", "h", "i"};
    for (const auto& name : all_meetings) {
        meeting_schedule.addVertex(name);
    }
    
    meeting_schedule.addEdge("a", "b"); meeting_schedule.addEdge("a", "d"); 
    meeting_schedule.addEdge("a", "e"); meeting_schedule.addEdge("a", "h"); 
    meeting_schedule.addEdge("a", "i");
    
    // b xung đột với: c, d, e, i (xung đột a đã thêm)
    meeting_schedule.addEdge("b", "c"); meeting_schedule.addEdge("b", "d"); 
    meeting_schedule.addEdge("b", "e"); meeting_schedule.addEdge("b", "i");
    
    // c xung đột với: d (xung đột b đã thêm)
    meeting_schedule.addEdge("c", "d");
    
    // d xung đột với: f, h, i (xung đột a, b, c, e đã thêm)
    meeting_schedule.addEdge("d", "f"); meeting_schedule.addEdge("d", "h"); 
    meeting_schedule.addEdge("d", "i");
    
    // e xung đột với: (xung đột a, b, d đã thêm)
    
    // f xung đột với: g, h, i (xung đột d đã thêm)
    meeting_schedule.addEdge("f", "g"); meeting_schedule.addEdge("f", "h"); 
    meeting_schedule.addEdge("f", "i");
    
    // g xung đột với: h (xung đột f đã thêm)
    meeting_schedule.addEdge("g", "h");
    
    // h xung đột với: i (xung đột a, d, f, g đã thêm)
    meeting_schedule.addEdge("h", "i");
    
    // I (xung đột a, b, d, f, h đã thêm)

    meeting_schedule.colorGraphAndLog();

    meeting_schedule.printResults();

    return 0;
}