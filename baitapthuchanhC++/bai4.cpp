#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <iomanip>

using namespace std;

// =========================================================
// LỚP 1: Match (Trận đấu)
// =========================================================
class Match {
public:
    string team1;
    string team2;
    string name;  // Tên trận (VD: "AB", "AC")
    int week;     // Tuần được xếp (0: chưa xếp)
    int degree;   // Bậc (số trận xung đột)
    
    Match(string t1, string t2) : team1(t1), team2(t2), week(0), degree(0) {
        name = t1 + t2;
    }
    
    // Kiểm tra xem trận này có xung đột với trận khác không
    bool conflictsWith(const Match& other) const {
        return (team1 == other.team1 || team1 == other.team2 ||
                team2 == other.team1 || team2 == other.team2);
    }
};

bool compareMatchByDegree(const Match* a, const Match* b) {
    if (a->degree != b->degree) {
        return a->degree > b->degree;
    }
    return a->name < b->name;
}

// =========================================================
// LỚP 2: MatchScheduler (Xếp lịch trận đấu)
// =========================================================
class MatchScheduler {
private:
    vector<Match*> matches;
    map<string, int> match_index;  // Map tên trận -> index
    vector<map<string, int>> history;  // Lịch sử hạ bậc

public:
    MatchScheduler() {}
    ~MatchScheduler() {
        for (auto m : matches) delete m;
    }

    void addMatch(const string& team1, const string& team2) {
        Match* m = new Match(team1, team2);
        match_index[m->name] = matches.size();
        matches.push_back(m);
    }

    // Tính bậc (degree) cho mỗi trận = số trận xung đột với nó
    void calculateDegrees() {
        for (size_t i = 0; i < matches.size(); i++) {
            matches[i]->degree = 0;
            for (size_t j = 0; j < matches.size(); j++) {
                if (i != j && matches[i]->conflictsWith(*matches[j])) {
                    matches[i]->degree++;
                }
            }
        }
    }

    // Ghi lại trạng thái hiện tại
    void logState() {
        map<string, int> current_state;
        for (const auto& m : matches) {
            current_state[m->name] = (m->week > 0) ? 0 : m->degree;
        }
        history.push_back(current_state);
    }

    // Thuật toán xếp lịch (tương tự tô màu đồ thị)
    void scheduleMatches() {
        calculateDegrees();
        history.clear();

        // Ghi lại bậc ban đầu
        logState();

        // Danh sách các trận chưa xếp lịch
        set<string> unscheduled;
        for (const auto& m : matches) {
            unscheduled.insert(m->name);
        }

        // Vòng lặp xếp lịch
        while (!unscheduled.empty()) {
            // Tìm trận có bậc cao nhất
            Match* current_match = nullptr;
            for (const string& name : unscheduled) {
                Match* m = matches[match_index[name]];
                if (current_match == nullptr || 
                    m->degree > current_match->degree ||
                    (m->degree == current_match->degree && name < current_match->name)) {
                    current_match = m;
                }
            }

            // Tìm tuần nhỏ nhất hợp lệ
            set<int> conflict_weeks;
            for (const auto& other : matches) {
                if (other->week > 0 && current_match->conflictsWith(*other)) {
                    conflict_weeks.insert(other->week);
                }
            }

            int week = 1;
            while (conflict_weeks.count(week)) {
                week++;
            }
            current_match->week = week;

            // Loại bỏ trận vừa xếp
            unscheduled.erase(current_match->name);

            // Hạ bậc các trận xung đột chưa xếp lịch
            for (const string& name : unscheduled) {
                Match* m = matches[match_index[name]];
                if (current_match->conflictsWith(*m)) {
                    m->degree--;
                }
            }

            // Ghi lại trạng thái
            if (!unscheduled.empty()) {
                logState();
            }
        }
    }

    // In kết quả
    void printResults() const {
        // Sắp xếp tên trận theo thứ tự
        vector<string> names;
        for (const auto& m : matches) {
            names.push_back(m->name);
        }
        sort(names.begin(), names.end());

        cout << "\n================================================================\n";
        cout << "         GIAI BAI TOAN 4: XEP LICH THI DAU                     \n";
        cout << "================================================================\n";

        // In bảng kết quả xếp lịch
        cout << "Ta có bảng các trận đấu:\n";
        
        // Tạo bảng ma trận
        set<char> teams;
        for (const auto& m : matches) {
            teams.insert(m->team1[0]);
            teams.insert(m->team2[0]);
        }
        
        vector<char> team_list(teams.begin(), teams.end());
        
        cout << setw(8) << " ";
        for (char t : team_list) {
            cout << setw(4) << t;
        }
        cout << endl;
        
        for (char t1 : team_list) {
            cout << setw(8) << t1;
            for (char t2 : team_list) {
                if (t1 == t2) {
                    cout << setw(4) << " ";
                } else {
                    string name1 = string(1, t1) + string(1, t2);
                    string name2 = string(1, t2) + string(1, t1);
                    
                    if (match_index.count(name1)) {
                        cout << setw(4) << name1;
                    } else if (match_index.count(name2)) {
                        cout << setw(4) << name2;
                    } else {
                        cout << setw(4) << " ";
                    }
                }
            }
            cout << endl;
        }
        
        cout << "\nCác trận đấu còn lại là đã xây ra.\n";
        cout << "Bài toán xếp lịch thi đấu sao cho số trận diễn ra còn lại là ít nhất. ";
        cout << "Một đội không thể tham gia\nthì đấu 2 trận cùng lúc.\n";
        
        cout << "\nCác trận đấu còn lại có thể xảy ra: ";
        for (size_t i = 0; i < names.size(); i++) {
            cout << names[i];
            if (i < names.size() - 1) cout << ", ";
        }
        cout << endl;
        
        cout << "\nKết luận:\n";

        // In bảng Định (tuần) và Bậc/Hạ bậc
        cout << "\n" << string(60, '=') << endl;
        cout << setw(12) << "Mẫu tô";
        for (const string& name : names) {
            cout << setw(4) << name;
        }
        cout << endl;
        
        cout << setw(12) << "Định";
        for (const string& name : names) {
            cout << setw(4) << matches[match_index.at(name)]->week;
        }
        cout << endl;
        cout << string(12 + names.size() * 4, '-') << endl;

        // In lịch sử bậc/hạ bậc
        for (size_t i = 0; i < history.size(); i++) {
            if (i == 0) {
                cout << setw(12) << "Bậc:";
            } else {
                cout << setw(12) << ("Hạ bậc " + to_string(i) + ":");
            }
            
            for (const string& name : names) {
                cout << setw(4) << history[i].at(name);
            }
            cout << endl;
        }
        cout << string(60, '=') << endl;

        printSchedule();
    }

    void printSchedule() const {
        map<int, vector<string>> schedule;
        int max_week = 0;

        for (const auto& m : matches) {
            schedule[m->week].push_back(m->name);
            if (m->week > max_week) {
                max_week = m->week;
            }
        }

        cout << "\n--- LICH TRINH XEP LICH THI DAU ---\n";
        for (const auto& pair : schedule) {
            cout << "+ Tuần " << pair.first << " : cho các trận đấu   ";
            for (size_t i = 0; i < pair.second.size(); i++) {
                cout << pair.second[i];
                if (i < pair.second.size() - 1) cout << ", ";
            }
            cout << endl;
        }
        cout << "\n=> TONG SO TUAN TOI THIEU CAN THIET: " << max_week << endl;
    }
};

// =========================================================
// HÀM MAIN
// =========================================================
int main() {
    MatchScheduler scheduler;

    // Thêm các trận đấu từ bảng (các trận còn lại chưa thi đấu)
    scheduler.addMatch("A", "C");
    scheduler.addMatch("A", "E");
    scheduler.addMatch("A", "F");
    scheduler.addMatch("B", "C");
    scheduler.addMatch("B", "D");
    scheduler.addMatch("C", "F");
    scheduler.addMatch("D", "E");
    scheduler.addMatch("E", "F");

    // Chạy thuật toán xếp lịch
    scheduler.scheduleMatches();

    // In kết quả
    scheduler.printResults();

    return 0;
}