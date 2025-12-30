#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;

int N; // số đĩa (người dùng nhập)

struct State {
    vector<vector<int>> towers; // 3 cột A, B, C
    int g; // chi phí từ đầu đến nút hiện tại
    int h; // heuristic - số đĩa chưa đúng vị trí
    int f; // f = g + h
    vector<string> path; // đường đi
    
    State(vector<vector<int>> t, int _g, vector<string> p) : towers(t), g(_g), path(p) {
        h = calculateH();
        f = g + h;
    }
    
    // Tính heuristic: số đĩa không ở cột đích (cột C)
    int calculateH() {
        int count = 0;
        for(int i = 0; i < 3; i++) {
            if(i != 2) { // không phải cột C
                count += towers[i].size();
            }
        }
        return count;
    }
    
    // Kiểm tra trạng thái đích
    bool isGoal() {
        return towers[0].empty() && towers[1].empty() && towers[2].size() == N;
    }
    
    // Chuyển state thành string để so sánh
    string toString() {
        string s;
        for(int i = 0; i < 3; i++) {
            for(int disk : towers[i]) {
                s += to_string(disk) + ",";
            }
            s += "|";
        }
        return s;
    }
};

// So sánh để priority queue chọn f nhỏ nhất
struct CompareState {
    bool operator()(State* a, State* b) {
        return a->f > b->f; // min heap
    }
};

void printState(State* s) {
    cout << "g=" << s->g << " h=" << s->h << " f=" << s->f << endl;
    char names[] = {'A', 'B', 'C'};
    for(int i = 0; i < 3; i++) {
        cout << names[i] << ": ";
        for(int disk : s->towers[i]) {
            cout << disk << " ";
        }
        cout << endl;
    }
    cout << "--------------------" << endl;
}

vector<State*> getSuccessors(State* current) {
    vector<State*> successors;
    char names[] = {'A', 'B', 'C'};
    
    // Thử di chuyển đĩa từ mỗi cột
    for(int from = 0; from < 3; from++) {
        if(current->towers[from].empty()) continue;
        
        int disk = current->towers[from].back();
        
        // Thử chuyển đến cột khác
        for(int to = 0; to < 3; to++) {
            if(from == to) continue;
            
            // Kiểm tra luật: chỉ đặt đĩa nhỏ lên đĩa lớn
            if(current->towers[to].empty() || disk < current->towers[to].back()) {
                // Tạo trạng thái mới
                vector<vector<int>> newTowers = current->towers;
                newTowers[from].pop_back();
                newTowers[to].push_back(disk);
                
                vector<string> newPath = current->path;
                string move = "Di chuyen dia " + to_string(disk) + " tu " + names[from] + " sang " + names[to];
                newPath.push_back(move);
                
                State* newState = new State(newTowers, current->g + 1, newPath);
                successors.push_back(newState);
            }
        }
    }
    
    return successors;
}

void solveHanoiAKT(int startCol, int endCol) {
    // Khởi tạo trạng thái ban đầu
    vector<vector<int>> initial(3);
    
    // Đặt N đĩa vào cột bắt đầu (đĩa lớn ở dưới, nhỏ ở trên)
    for(int i = N; i >= 1; i--) {
        initial[startCol].push_back(i);
    }
    
    State* start = new State(initial, 0, {});
    
    priority_queue<State*, vector<State*>, CompareState> openList;
    map<string, bool> visited;
    
    openList.push(start);
    
    char names[] = {'A', 'B', 'C'};
    cout << "\n=== BAT DAU TIM KIEM BANG GIAI THUAT A* (AKT) ===" << endl;
    cout << "So dia: " << N << endl;
    cout << "Tu cot: " << names[startCol] << " -> Sang cot: " << names[endCol] << endl;
    cout << "\nTrang thai ban dau:" << endl;
    printState(start);
    
    int statesExplored = 0;
    
    while(!openList.empty()) {
        State* current = openList.top();
        openList.pop();
        
        string stateStr = current->toString();
        
        // Nếu đã thăm, bỏ qua
        if(visited[stateStr]) {
            delete current;
            continue;
        }
        
        visited[stateStr] = true;
        statesExplored++;
        
        // Kiểm tra đích (tất cả đĩa ở cột đích)
        bool isGoalState = true;
        for(int i = 0; i < 3; i++) {
            if(i == endCol) {
                if(current->towers[i].size() != N) {
                    isGoalState = false;
                    break;
                }
            } else {
                if(!current->towers[i].empty()) {
                    isGoalState = false;
                    break;
                }
            }
        }
        
        if(isGoalState) {
            cout << "\n=== TIM THAY LOI GIAI ===" << endl;
            cout << "Tong so buoc: " << current->g << endl;
            cout << "So trang thai da kham pha: " << statesExplored << endl;
            cout << "\nCac buoc di chuyen:" << endl;
            for(int i = 0; i < current->path.size(); i++) {
                cout << "Buoc " << (i+1) << ": " << current->path[i] << endl;
            }
            cout << "\nTrang thai cuoi:" << endl;
            printState(current);
            delete current;
            return;
        }
        
        // Sinh các trạng thái kế tiếp
        vector<State*> successors = getSuccessors(current);
        
        for(State* succ : successors) {
            if(!visited[succ->toString()]) {
                openList.push(succ);
            } else {
                delete succ;
            }
        }
        
        delete current;
    }
    
    cout << "Khong tim thay loi giai!" << endl;
}

int main() {
    cout << "========================================" << endl;
    cout << "   GIAI BAI TOAN THAP HA NOI BANG A*   " << endl;
    cout << "========================================" << endl;
    
    // Nhập số đĩa
    cout << "\nNhap so dia (n >= 1): ";
    cin >> N;
    
    while(N < 1) {
        cout << "So dia phai >= 1. Vui long nhap lai: ";
        cin >> N;
    }
    
    // Nhập cột bắt đầu
    char startChar;
    cout << "Nhap cot bat dau (A/B/C): ";
    cin >> startChar;
    startChar = toupper(startChar);
    
    while(startChar != 'A' && startChar != 'B' && startChar != 'C') {
        cout << "Cot khong hop le. Nhap lai (A/B/C): ";
        cin >> startChar;
        startChar = toupper(startChar);
    }
    
    // Nhập cột kết thúc
    char endChar;
    cout << "Nhap cot ket thuc (A/B/C): ";
    cin >> endChar;
    endChar = toupper(endChar);
    
    while(endChar != 'A' && endChar != 'B' && endChar != 'C') {
        cout << "Cot khong hop le. Nhap lai (A/B/C): ";
        cin >> endChar;
        endChar = toupper(endChar);
    }
    
    while(startChar == endChar) {
        cout << "Cot bat dau va ket thuc phai khac nhau!" << endl;
        cout << "Nhap cot ket thuc (A/B/C): ";
        cin >> endChar;
        endChar = toupper(endChar);
    }
    
    int startCol = startChar - 'A';
    int endCol = endChar - 'A';
    
    solveHanoiAKT(startCol, endCol);
    
    return 0;
}