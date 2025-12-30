#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <map>
#include <iomanip>
using namespace std;

// Lớp biểu diễn trạng thái trong đồ thị And-Or
class State {
public:
    string name;
    string formula;
    vector<vector<State*>> andChildren;  // Mỗi vector con là một nhóm AND
    bool isSolved;
    bool isGoal;
    
    State(string n, string f = "") : name(n), formula(f), isSolved(false), isGoal(false) {}
    
    void addAndGroup(vector<State*> group) {
        andChildren.push_back(group);
    }
};

// Lớp giải bài toán And-Or Graph
class AndOrGraphSolver {
private:
    map<string, State*> states;
    set<string> facts;  // Tập sự kiện đã biết
    vector<string> solutionPath;
    
    // Tạo đồ thị And-Or cho bài toán tam giác
    void buildGraph() {
        // Các trạng thái
        State* R1 = new State("R1", "a + b + γ = π - θ");
        State* R2 = new State("R2", "a + b + c = π - 0");
        State* R3 = new State("R3", "S - 1/2 bc = 0");
        
        State* H1 = new State("H1", "a/(sin α) = b/(sin β)");
        State* H2 = new State("H2", "b - b sin π = 0");
        State* H3 = new State("H3", "sin γ/(sin γ) = c/(sin γ)");
        
        State* a = new State("a", "a");
        State* b = new State("b", "b");
        State* c = new State("c", "c");
        State* s = new State("s", "s");
        State* alpha = new State("α", "α");
        State* beta = new State("β", "β");
        State* gamma = new State("γ", "γ");
        
        // Thiết lập quan hệ And-Or
        // R1 cần (a, b, γ)
        R1->addAndGroup({a, b, gamma});
        
        // R2 cần (a, b, c)
        R2->addAndGroup({a, b, c});
        
        // R3 cần (s, b, c)
        R3->addAndGroup({s, b, c});
        
        // H1 cần (a, α, b, β)
        H1->addAndGroup({a, alpha, b, beta});
        
        // H2 cần (b, β)
        H2->addAndGroup({b, beta});
        
        // H3 cần (α, γ, c, γ) - đơn giản hóa
        H3->addAndGroup({alpha, gamma, c});
        
        // Đánh dấu các sự kiện gốc
        a->isGoal = true;
        b->isGoal = true;
        c->isGoal = true;
        s->isGoal = true;
        alpha->isGoal = true;
        beta->isGoal = true;
        gamma->isGoal = true;
        
        // Lưu vào map
        states["R1"] = R1;
        states["R2"] = R2;
        states["R3"] = R3;
        states["H1"] = H1;
        states["H2"] = H2;
        states["H3"] = H3;
        states["a"] = a;
        states["b"] = b;
        states["c"] = c;
        states["s"] = s;
        states["α"] = alpha;
        states["β"] = beta;
        states["γ"] = gamma;
    }
    
    // Kiểm tra trạng thái có thể giải được không
    bool canSolve(State* state, int depth, string prefix) {
        // Nếu là sự kiện có sẵn
        if(state->isGoal) {
            if(facts.find(state->name) != facts.end()) {
                cout << prefix << "✓ " << state->name << " (đã biết)" << endl;
                state->isSolved = true;
                return true;
            } else {
                cout << prefix << "✗ " << state->name << " (chưa biết)" << endl;
                return false;
            }
        }
        
        // Nếu đã giải rồi
        if(state->isSolved) {
            cout << prefix << "✓ " << state->name << " (đã giải)" << endl;
            return true;
        }
        
        cout << prefix << "? " << state->name << ": " << state->formula << endl;
        
        // Thử từng nhóm AND
        for(size_t i = 0; i < state->andChildren.size(); i++) {
            cout << prefix << "  Thử phương án " << (i+1) << ":" << endl;
            
            bool allSolved = true;
            for(State* child : state->andChildren[i]) {
                if(!canSolve(child, depth + 1, prefix + "    ")) {
                    allSolved = false;
                    break;
                }
            }
            
            if(allSolved) {
                cout << prefix << "  → Phương án " << (i+1) << " thành công!" << endl;
                state->isSolved = true;
                solutionPath.push_back(state->name);
                return true;
            }
        }
        
        cout << prefix << "  → Không có phương án nào khả thi!" << endl;
        return false;
    }
    
public:
    AndOrGraphSolver() {
        buildGraph();
    }
    
    ~AndOrGraphSolver() {
        for(auto& pair : states) {
            delete pair.second;
        }
    }
    
    // Thiết lập tập sự kiện ban đầu
    void setFacts(set<string> f) {
        facts = f;
    }
    
    // Hiển thị tập sự kiện
    void showFacts() {
        cout << "\n========================================" << endl;
        cout << "        TẬP SỰ KIỆN BAN ĐẦU" << endl;
        cout << "========================================\n" << endl;
        
        cout << "Các giá trị đã biết: {";
        int idx = 0;
        for(const string& f : facts) {
            cout << f;
            if(++idx < facts.size()) cout << ", ";
        }
        cout << "}" << endl;
    }
    
    // Giải bài toán
    bool solve(const string& goalName) {
        cout << "\n========================================" << endl;
        cout << "      BẮT ĐẦU SUY DIỄN (AND-OR)" << endl;
        cout << "========================================\n" << endl;
        
        cout << "Mục tiêu: Tính " << goalName << "\n" << endl;
        
        if(states.find(goalName) == states.end()) {
            cout << "Không tìm thấy trạng thái: " << goalName << endl;
            return false;
        }
        
        State* goal = states[goalName];
        bool result = canSolve(goal, 0, "");
        
        cout << "\n========================================" << endl;
        cout << "            KẾT QUẢ" << endl;
        cout << "========================================\n" << endl;
        
        if(result) {
            cout << "✓ CÓ THỂ tính được " << goalName << endl;
            cout << "\nĐường đi giải:" << endl;
            for(const string& step : solutionPath) {
                cout << "  → " << step << endl;
            }
        } else {
            cout << "✗ KHÔNG THỂ tính được " << goalName << endl;
            cout << "  (Thiếu dữ liệu đầu vào)" << endl;
        }
        
        return result;
    }
    
    // Hiển thị đồ thị
    void showGraph() {
        cout << "\n========================================" << endl;
        cout << "        CẤU TRÚC ĐỒ THỊ AND-OR" << endl;
        cout << "========================================\n" << endl;
        
        cout << "Các luật suy diễn:" << endl;
        cout << "  R1: a + b + γ = π - θ  ← (a, b, γ)" << endl;
        cout << "  R2: a + b + c = π - 0  ← (a, b, c)" << endl;
        cout << "  R3: S - 1/2·bc = 0     ← (s, b, c)" << endl;
        cout << "  H1: a/sinα = b/sinβ    ← (a, α, b, β)" << endl;
        cout << "  H2: b - b·sinπ = 0     ← (b, β)" << endl;
        cout << "  H3: sinγ/sinγ = c/sinγ ← (α, γ, c)" << endl;
    }
};

int main() {
    cout << "\n***** BÀI 13: CƠ CHẾ SUY DIỄN - TAM GIÁC *****" << endl;
    cout << "Áp dụng đồ thị And-Or để giải bài toán tam giác\n" << endl;
    
    AndOrGraphSolver solver;
    
    // Hiển thị cấu trúc
    solver.showGraph();
    
    // Test case 1: Có đủ dữ liệu
    cout << "\n\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
    cout << "TEST CASE 1: Tính S (diện tích)" << endl;
    cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
    
    solver.setFacts({"s", "b", "c"});
    solver.showFacts();
    solver.solve("R3");
    
    // Test case 2: Thiếu dữ liệu
    cout << "\n\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
    cout << "TEST CASE 2: Tính với dữ liệu thiếu" << endl;
    cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
    
    AndOrGraphSolver solver2;
    solver2.setFacts({"a", "b"});  // Thiếu c hoặc γ
    solver2.showFacts();
    solver2.solve("R2");
    
    cout << "\n========================================\n" << endl;
    
    return 0;
}