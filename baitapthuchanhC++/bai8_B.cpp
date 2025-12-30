#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
using namespace std;

// Lớp biểu diễn một Luật
class Rule {
private:
    vector<string> premises;  // Điều kiện (vế trái)
    string conclusion;         // Kết luận (vế phải)
    string name;              // Tên luật (R1, R2,...)
    
public:
    // Constructor
    Rule(string n, vector<string> p, string c) 
        : name(n), premises(p), conclusion(c) {}
    
    // Getter
    vector<string> getPremises() const { return premises; }
    string getConclusion() const { return conclusion; }
    string getName() const { return name; }
    
    // Kiểm tra xem luật có thể áp dụng với tập sự kiện cho trước không
    bool canApply(const set<string>& facts) const {
        for(const string& premise : premises) {
            if(facts.find(premise) == facts.end()) {
                return false;
            }
        }
        return true;
    }
    
    // In luật ra màn hình
    void print() const {
        cout << name << ": {";
        for(size_t i = 0; i < premises.size(); i++) {
            cout << premises[i];
            if(i < premises.size() - 1) cout << ", ";
        }
        cout << "} -> " << conclusion;
    }
};

// Lớp quản lý tập sự kiện
class FactBase {
private:
    set<string> facts;
    
public:
    // Constructor
    FactBase() {}
    FactBase(set<string> f) : facts(f) {}
    
    // Thêm một sự kiện
    bool addFact(const string& fact) {
        if(facts.find(fact) != facts.end()) {
            return false; // Đã tồn tại
        }
        facts.insert(fact);
        return true; // Thêm thành công
    }
    
    // Kiểm tra sự kiện có tồn tại không
    bool contains(const string& fact) const {
        return facts.find(fact) != facts.end();
    }
    
    // Lấy tập sự kiện
    set<string> getFacts() const {
        return facts;
    }
    
    // In tập sự kiện
    void print() const {
        cout << "{";
        int idx = 0;
        for(const string& f : facts) {
            cout << f;
            if(++idx < facts.size()) cout << ", ";
        }
        cout << "}";
    }
};

// Lớp hệ thống suy diễn Vương Hạo
class InferenceEngine {
private:
    vector<Rule*> rules;      // Tập luật
    FactBase* factBase;       // Cơ sở sự kiện
    string goal;              // Mục tiêu cần đạt
    set<string> usedRules;    // Các luật đã sử dụng
    int stepCount;            // Đếm số bước
    
public:
    // Constructor
    InferenceEngine() : factBase(nullptr), stepCount(0) {}
    
    // Destructor
    ~InferenceEngine() {
        for(Rule* rule : rules) {
            delete rule;
        }
        if(factBase) delete factBase;
    }
    
    // Thêm luật
    void addRule(Rule* rule) {
        rules.push_back(rule);
    }
    
    // Thiết lập cơ sở sự kiện
    void setFactBase(FactBase* fb) {
        if(factBase) delete factBase;
        factBase = fb;
    }
    
    // Thiết lập mục tiêu
    void setGoal(const string& g) {
        goal = g;
    }
    
    // In thông tin hệ thống
    void printSystem() const {
        cout << "\n========================================" << endl;
        cout << "   HỆ THỐNG SUY DIỄN VƯƠNG HẠO" << endl;
        cout << "========================================\n" << endl;
        
        cout << "Tập sự kiện ban đầu: ";
        factBase->print();
        cout << endl;
        
        cout << "Mục tiêu: " << goal << endl;
        
        cout << "\nTập luật:" << endl;
        for(const Rule* rule : rules) {
            cout << "  ";
            rule->print();
            cout << endl;
        }
    }
    
    // Tìm luật có thể áp dụng
    Rule* findApplicableRule() {
        for(Rule* rule : rules) {
            // Bỏ qua luật đã sử dụng
            if(usedRules.find(rule->getName()) != usedRules.end()) {
                continue;
            }
            
            // Kiểm tra luật có thể áp dụng không
            if(rule->canApply(factBase->getFacts())) {
                // Kiểm tra kết luận chưa có trong factBase
                if(!factBase->contains(rule->getConclusion())) {
                    return rule;
                }
            }
        }
        return nullptr;
    }
    
    // Áp dụng một luật
    bool applyRule(Rule* rule) {
        cout << "Bước " << ++stepCount << ": Áp dụng luật ";
        rule->print();
        cout << endl;
        
        string conclusion = rule->getConclusion();
        factBase->addFact(conclusion);
        usedRules.insert(rule->getName());
        
        cout << "  -> Thêm '" << conclusion << "' vào tập sự kiện" << endl;
        cout << "  -> Tập sự kiện hiện tại: ";
        factBase->print();
        cout << endl << endl;
        
        return true;
    }
    
    // Thuật toán suy diễn tiến (Forward Chaining)
    bool forwardChaining() {
        printSystem();
        
        cout << "\n--- BẮT ĐẦU SUY DIỄN ---\n" << endl;
        
        // Kiểm tra mục tiêu ban đầu
        if(factBase->contains(goal)) {
            cout << "Mục tiêu '" << goal << "' đã có sẵn trong tập sự kiện ban đầu!" << endl;
            return true;
        }
        
        // Lặp cho đến khi không còn luật nào có thể áp dụng
        while(true) {
            Rule* applicableRule = findApplicableRule();
            
            // Không còn luật nào có thể áp dụng
            if(applicableRule == nullptr) {
                break;
            }
            
            // Áp dụng luật
            applyRule(applicableRule);
            
            // Kiểm tra đã đạt mục tiêu chưa
            if(applicableRule->getConclusion() == goal) {
                cout << "==> ĐÃ ĐẠT ĐƯỢC MỤC TIÊU: " << goal << endl;
                cout << "\nKẾT LUẬN: {" << goal << "} ĐƯỢC SUY DIỄN THÀNH CÔNG!" << endl;
                return true;
            }
        }
        
        // Không tìm được mục tiêu
        cout << "==> KHÔNG THỂ SUY DIỄN ĐƯỢC MỤC TIÊU: " << goal << endl;
        cout << "\nKẾT LUẬN: KHÔNG THỂ SUY DIỄN {" << goal << "}" << endl;
        return false;
    }
    
    // Reset hệ thống
    void reset() {
        usedRules.clear();
        stepCount = 0;
    }
};

// Hàm main
int main() {
    cout << "\n========================================" << endl;
    cout << "   BÀI 8b: THUẬT TOÁN VƯƠNG HẠO" << endl;
    cout << "========================================\n" << endl;
    
    cout << "Bài toán: Cho {(a∧b)→c, (b∧c)→d, ¬d}. CM: a→b\n" << endl;
    
    // Tạo hệ thống suy diễn
    InferenceEngine* engine = new InferenceEngine();
    
    // Thêm các luật
    engine->addRule(new Rule("R1", {"a", "b"}, "c"));  // (a∧b)→c
    engine->addRule(new Rule("R2", {"b", "c"}, "d"));  // (b∧c)→d
    
    cout << "TRƯỜNG HỢP 1: Giả sử có {a, b}" << endl;
    cout << "-------------------------------" << endl;
    
    FactBase* factBase1 = new FactBase({"a", "b"});
    engine->setFactBase(factBase1);
    engine->setGoal("d");
    
    bool result1 = engine->forwardChaining();
    
    if(result1) {
        cout << "\n⚠️  MÂU THUẪN: Có (a,b) → d, nhưng đề cho ¬d!" << endl;
        cout << "→ Không thể có đồng thời a và b\n" << endl;
    }
    
    cout << "\n========================================\n" << endl;
    cout << "TRƯỜNG HỢP 2: Giả sử có {a}" << endl;
    cout << "-------------------------------" << endl;
    
    engine->reset();
    FactBase* factBase2 = new FactBase({"a"});
    engine->setFactBase(factBase2);
    engine->setGoal("d");
    
    bool result2 = engine->forwardChaining();
    
    if(!result2) {
        cout << "\n✓ KHÔNG MÂU THUẪN: Có a (không có b) → không dẫn đến d" << endl;
        cout << "→ Phù hợp với ¬d\n" << endl;
    }
    
    cout << "\n========================================" << endl;
    cout << "KẾT LUẬN" << endl;
    cout << "========================================" << endl;
    cout << "Từ ¬d và các luật:\n" << endl;
    cout << "• Nếu có (a∧b) → dẫn đến d (mâu thuẫn với ¬d)" << endl;
    cout << "• Nếu có a → KHÔNG thể có b (để tránh mâu thuẫn)" << endl;
    cout << "\n→ Kết quả: a → ¬b (không phải a → b)" << endl;
    cout << "→ KHÔNG thể chứng minh a → b\n" << endl;
    
    delete engine;
    return 0;
}