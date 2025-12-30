#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <iomanip>

using namespace std;

class Vertex {
public:
    string name;       
    int degree;        
    int color;         
    
    Vertex(string n) : name(n), degree(0), color(0) {}
};

bool compareByDegree(const Vertex* a, const Vertex* b) {
    if (a->degree != b->degree) {
        return a->degree > b->degree; 
    }
    return a->name < b->name; 
}

class Graph {
private:
    map<string, Vertex*> vertices;
    map<string, set<string>> adj_list;  // Đổi sang set để tránh trùng lặp
    vector<map<string, int>> history;

public:
    Graph() {}
    ~Graph() {
        for (auto& pair : vertices) delete pair.second;
    }

    void addVertex(const string& name) {
        if (vertices.find(name) == vertices.end()) {
            vertices[name] = new Vertex(name);
        }
    }

    void addEdge(const string& u, const string& v) {
        addVertex(u);
        addVertex(v);
        adj_list[u].insert(v);
        adj_list[v].insert(u);
    }
    
    void calculateInitialDegrees() {
        for (auto& pair : vertices) {
            if (adj_list.count(pair.first)) {
                pair.second->degree = (int)adj_list[pair.first].size();
            }
        }
    }

    void logState(const vector<string>& all_names) {
        map<string, int> current_state;
        for (const string& name : all_names) {
            Vertex* v = vertices[name];
            if (v->color > 0) {
                current_state[name] = 0; 
            } else {
                current_state[name] = v->degree;
            }
        }
        history.push_back(current_state);
    }

    void colorGraphAndLog() {
        calculateInitialDegrees();
        history.clear();

        vector<string> all_names;
        for (const auto& pair : vertices) all_names.push_back(pair.first);
        sort(all_names.begin(), all_names.end());
        
        // Ghi lại bậc ban đầu
        logState(all_names); 
        
        // Tạo danh sách các đỉnh chưa tô màu
        set<string> uncolored;
        for (const auto& pair : vertices) {
            uncolored.insert(pair.first);
        }

        // Vòng lặp tô màu
        while (!uncolored.empty()) {
            // Tìm đỉnh có bậc cao nhất trong các đỉnh chưa tô màu
            Vertex* current_v = nullptr;
            for (const string& name : uncolored) {
                if (current_v == nullptr || 
                    vertices[name]->degree > current_v->degree ||
                    (vertices[name]->degree == current_v->degree && name < current_v->name)) {
                    current_v = vertices[name];
                }
            }
            
            // Tìm màu nhỏ nhất hợp lệ
            set<int> neighbor_colors;
            if (adj_list.count(current_v->name)) {
                for (const string& neighbor_name : adj_list[current_v->name]) {
                    if (vertices[neighbor_name]->color > 0) {
                        neighbor_colors.insert(vertices[neighbor_name]->color);
                    }
                }
            }

            int color = 1;
            while (neighbor_colors.count(color)) {
                color++;
            }
            current_v->color = color;

            // Loại bỏ đỉnh vừa tô màu
            uncolored.erase(current_v->name);

            // Hạ bậc các đỉnh kề CHƯA TÔ MÀU
            if (adj_list.count(current_v->name)) {
                for (const string& neighbor_name : adj_list[current_v->name]) {
                    if (uncolored.count(neighbor_name)) {
                        vertices[neighbor_name]->degree--;
                    }
                }
            }
            
            // Ghi lại trạng thái
            if (!uncolored.empty()) {
                logState(all_names);
            }
        }
    }

    void printResults() const {
        vector<string> names;
        for (const auto& pair : vertices) names.push_back(pair.first);
        sort(names.begin(), names.end()); 
        
        cout << "\n=========================================================\n";
        cout << "         GIAI BAI TOAN 3: TO MAU DO THI (HA BAC)         \n";
        cout << "=========================================================\n";

        cout << setw(12) << "Tô màu:";
        for (const string& name : names) {
            cout << setw(4) << vertices.at(name)->color;
        }
        cout << endl;

        cout << setw(12) << "Đỉnh:";
        for (const string& name : names) {
            cout << setw(4) << name;
        }
        cout << endl;
        cout << string(12 + names.size() * 4, '-') << endl;

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

        cout << "\n--- LICH TRINH TO CHUC MIT-TINH ---\n";
        for (const auto& pair : schedules) {
            cout << "Buoi " << pair.first << " (Màu " << pair.first << "): ";
            cout << "[";
            for (size_t i = 0; i < pair.second.size(); ++i) {
                cout << pair.second[i] << (i < pair.second.size() - 1 ? ", " : "");
            }
             cout << "]\n";
        }
        cout << "\n=> TONG SO BUOI TOI THIEU CAN THIET: " << max_session << endl;
    }
};

int main() {
    Graph meeting_schedule;
    
    vector<string> all_meetings = {"A", "B", "C", "D", "E", "F", "G", "H"};
    for (const auto& name : all_meetings) {
        meeting_schedule.addVertex(name);
    }
    
    // Thêm các cạnh từ đồ thị trong hình
    meeting_schedule.addEdge("A", "D");
    meeting_schedule.addEdge("A", "C");
    meeting_schedule.addEdge("A", "B");
    
    meeting_schedule.addEdge("B", "C");
    meeting_schedule.addEdge("B", "E");
    
    meeting_schedule.addEdge("C", "D");
    
    meeting_schedule.addEdge("D", "F");
    
    meeting_schedule.addEdge("E", "F");
    meeting_schedule.addEdge("E", "H");
    
    meeting_schedule.addEdge("F", "G");
    meeting_schedule.addEdge("F", "H");
    
    meeting_schedule.addEdge("G", "H");

    meeting_schedule.colorGraphAndLog();
    meeting_schedule.printResults();

    return 0;
}