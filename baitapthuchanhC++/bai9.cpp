#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
using namespace std;

// Lớp biểu diễn một Mệnh đề (Clause)
class Clause {
private:
    set<string> literals;  // Tập các literal trong mệnh đề
    string name;           // Tên mệnh đề
    
public:
    // Constructor
    Clause(string n, set<string> lit) : name(n), literals(lit) {}
    
    // Getter
    set<string> getLiterals() const { return literals; }
    string getName() const { return name; }
    
    // Kiểm tra mệnh đề rỗng
    bool isEmpty() const {
        return literals.empty();
    }
    
    // In mệnh đề
    void print() const {
        cout << name << ": {";
        int idx = 0;
        for(const string& lit : literals) {
            cout << lit;
            if(++idx < literals.size()) cout << ", ";
        }
        cout << "}";
    }
};

// Lớp thực hiện thuật toán Robinson
class RobinsonResolver {
private:
    vector<Clause*> clauses;  // Tập mệnh đề
    int stepCount;
    
    // Tìm literal phủ định của một literal
    string negate(const string& literal) {
        if(literal[0] == '~') {
            return literal.substr(1);  // Bỏ dấu ~
        } else {
            return "~" + literal;       // Thêm dấu ~
        }
    }
    
    // Hợp giải hai mệnh đề
    Clause* resolve(Clause* c1, Clause* c2, string& resolvedLiteral) {
        set<string> lit1 = c1->getLiterals();
        set<string> lit2 = c2->getLiterals();
        
        // Tìm cặp literal đối ngẫu
        for(const string& l1 : lit1) {
            string negL1 = negate(l1);
            if(lit2.find(negL1) != lit2.end()) {
                // Tìm thấy cặp đối ngẫu
                resolvedLiteral = l1;
                
                // Tạo mệnh đề mới
                set<string> newLiterals;
                
                // Thêm các literal từ c1 (trừ l1)
                for(const string& lit : lit1) {
                    if(lit != l1) {
                        newLiterals.insert(lit);
                    }
                }
                
                // Thêm các literal từ c2 (trừ ~l1)
                for(const string& lit : lit2) {
                    if(lit != negL1) {
                        newLiterals.insert(lit);
                    }
                }
                
                // Tạo tên mệnh đề mới
                string newName = "R" + to_string(clauses.size() + 1);
                return new Clause(newName, newLiterals);
            }
        }
        
        resolvedLiteral = "";
        return nullptr;
    }
    
public:
    // Constructor
    RobinsonResolver() : stepCount(0) {}
    
    // Destructor
    ~RobinsonResolver() {
        for(Clause* clause : clauses) {
            delete clause;
        }
    }
    
    // Thêm mệnh đề
    void addClause(Clause* clause) {
        clauses.push_back(clause);
    }
    
    // In tập mệnh đề
    void printClauses() const {
        cout << "\nTập mệnh đề ban đầu:" << endl;
        for(const Clause* clause : clauses) {
            cout << "  ";
            clause->print();
            cout << endl;
        }
    }
    
    // Kiểm tra xem mệnh đề đã tồn tại chưa
    bool clauseExists(const set<string>& literals) {
        for(const Clause* clause : clauses) {
            if(clause->getLiterals() == literals) {
                return true;
            }
        }
        return false;
    }
    
    // Thuật toán Robinson
    bool resolve() {
        cout << "\n========================================" << endl;
        cout << "   THUẬT TOÁN ROBINSON - SUY DIỄN NGƯỢC" << endl;
        cout << "========================================" << endl;
        
        printClauses();
        
        cout << "\n--- BẮT ĐẦU HỢP GIẢI ---\n" << endl;
        
        vector<Clause*> newClauses;
        bool foundEmpty = false;
        
        while(true) {
            newClauses.clear();
            bool addedNew = false;
            
            // Thử hợp giải mọi cặp mệnh đề
            for(size_t i = 0; i < clauses.size(); i++) {
                for(size_t j = i + 1; j < clauses.size(); j++) {
                    string resolvedLit;
                    Clause* resolvent = resolve(clauses[i], clauses[j], resolvedLit);
                    
                    if(resolvent != nullptr) {
                        // Kiểm tra mệnh đề rỗng
                        if(resolvent->isEmpty()) {
                            cout << "Bước " << ++stepCount << ": Hợp giải ";
                            clauses[i]->print();
                            cout << " và ";
                            clauses[j]->print();
                            cout << endl;
                            cout << "  -> Khử cặp đối ngẫu: " << resolvedLit << " và " << negate(resolvedLit) << endl;
                            cout << "  -> Kết quả: {} (MỆNH ĐỀ RỖNG)" << endl;
                            cout << "\n==> TÌM THẤY MỆNH ĐỀ RỖNG!" << endl;
                            cout << "\nKẾT LUẬN: Mệnh đề cần chứng minh là ĐÚNG (hợp lý)!" << endl;
                            delete resolvent;
                            return true;
                        }
                        
                        // Kiểm tra mệnh đề mới đã tồn tại chưa
                        if(!clauseExists(resolvent->getLiterals())) {
                            cout << "Bước " << ++stepCount << ": Hợp giải ";
                            clauses[i]->print();
                            cout << " và ";
                            clauses[j]->print();
                            cout << endl;
                            cout << "  -> Khử cặp đối ngẫu: " << resolvedLit << " và " << negate(resolvedLit) << endl;
                            cout << "  -> Kết quả: ";
                            resolvent->print();
                            cout << endl << endl;
                            
                            newClauses.push_back(resolvent);
                            addedNew = true;
                        } else {
                            delete resolvent;
                        }
                    }
                }
            }
            
            // Thêm các mệnh đề mới vào tập mệnh đề
            if(addedNew) {
                for(Clause* clause : newClauses) {
                    clauses.push_back(clause);
                }
            } else {
                // Không thể hợp giải thêm được nữa
                cout << "==> KHÔNG THỂ HỢP GIẢI THÊM!" << endl;
                cout << "\nKẾT LUẬN: Không thể chứng minh được mệnh đề!" << endl;
                return false;
            }
        }
        
        return false;
    }
};

int main() {
    cout << "\n***** BÀI 9a: THUẬT TOÁN ROBINSON *****\n" << endl;
    cout << "Bài toán: Cho {p→q, q→r, r→s, p}. Hỏi p∧s?" << endl;
    cout << "\nChuyển về dạng mệnh đề đối ngẫu:" << endl;
    cout << "  p→q  ≡  ~p ∨ q" << endl;
    cout << "  q→r  ≡  ~q ∨ r" << endl;
    cout << "  r→s  ≡  ~r ∨ s" << endl;
    cout << "  p    ≡  p" << endl;
    cout << "  ~(p∧s) ≡ ~p ∨ ~s  (phủ định mục tiêu để chứng minh mâu thuẫn)" << endl;
    
    // Tạo bộ giải Robinson
    RobinsonResolver* resolver = new RobinsonResolver();
    
    // Thêm các mệnh đề (dạng CNF - Conjunctive Normal Form)
    resolver->addClause(new Clause("C1", {"~p", "q"}));   // p→q
    resolver->addClause(new Clause("C2", {"~q", "r"}));   // q→r
    resolver->addClause(new Clause("C3", {"~r", "s"}));   // r→s
    resolver->addClause(new Clause("C4", {"p"}));         // p
    resolver->addClause(new Clause("C5", {"~p", "~s"}));  // ~(p∧s) - phủ định kết luận
    
    // Chạy thuật toán
    bool result = resolver->resolve();
    
    // Giải phóng bộ nhớ
    delete resolver;
    
    cout << "\n========================================\n" << endl;
    
    return 0;
}