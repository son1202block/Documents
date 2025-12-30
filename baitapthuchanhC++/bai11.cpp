#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cmath>
#include <iomanip>
using namespace std;

// Cấu trúc dữ liệu người
struct Person {
    string ten;
    string mauToc;      // Vàng, Nâu, Nâu
    string chieuCao;    // Trung bình, Cao, Lùn
    string canNang;     // Nhẹ, Trung bình, Nặng
    string dungKem;     // Không, Có
    string ketQua;      // Chạy nắng, Không chạy nắng
};

// Lớp tính toán độ hỗn loạn (Entropy) và Information Gain
class EntropyCalculator {
public:
    // Tính Entropy của một tập dữ liệu
    static double calculateEntropy(const vector<Person>& data) {
        if(data.empty()) return 0.0;
        
        map<string, int> counts;
        for(const Person& p : data) {
            counts[p.ketQua]++;
        }
        
        double entropy = 0.0;
        int total = data.size();
        
        for(auto& pair : counts) {
            if(pair.second > 0) {
                double p = (double)pair.second / total;
                entropy -= p * log2(p);
            }
        }
        
        return entropy;
    }
    
    // Tính độ hỗn loạn trung bình của một thuộc tính
    static double calculateWeightedEntropy(const vector<Person>& data, 
                                          const string& attribute,
                                          map<string, vector<Person>>& splits) {
        splits.clear();
        
        // Phân tách dữ liệu theo thuộc tính
        for(const Person& p : data) {
            string value;
            if(attribute == "Màu tóc") value = p.mauToc;
            else if(attribute == "Chiều cao") value = p.chieuCao;
            else if(attribute == "Cân nặng") value = p.canNang;
            else if(attribute == "Dùng kem") value = p.dungKem;
            
            splits[value].push_back(p);
        }
        
        // Tính entropy có trọng số
        double weightedEntropy = 0.0;
        int totalSize = data.size();
        
        for(auto& pair : splits) {
            double weight = (double)pair.second.size() / totalSize;
            double entropy = calculateEntropy(pair.second);
            weightedEntropy += weight * entropy;
        }
        
        return weightedEntropy;
    }
    
    // Tính Information Gain
    static double calculateGain(const vector<Person>& data, const string& attribute) {
        double parentEntropy = calculateEntropy(data);
        map<string, vector<Person>> splits;
        double weightedEntropy = calculateWeightedEntropy(data, attribute, splits);
        
        return parentEntropy - weightedEntropy;
    }
};

// Lớp phân tích và xây dựng cây quyết định
class DecisionTreeAnalyzer {
private:
    vector<Person> dataset;
    vector<string> attributes;
    
    // Hiển thị công thức tính toán
    void displayFormula() {
        cout << "\nCông thức tính độ hỗn loạn trung bình:" << endl;
        cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
        cout << "              n_b     n_bc      n_bc" << endl;
        cout << "NHĐ_b = Σ ( ────── ) × ( - ──── log₂ ──── )" << endl;
        cout << "           j  n_j        n_b       n_b" << endl;
        cout << "\nTrong đó:" << endl;
        cout << "  • n_b: Số mẫu trong nhánh b" << endl;
        cout << "  • n_j: Tổng số mẫu trong tất cả các nhánh" << endl;
        cout << "  • n_bc: Tổng số mẫu trong nhánh b thuộc lớp c" << endl;
        cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n" << endl;
    }
    
    // Hiển thị chi tiết tính toán cho một nhánh
    void displayBranchCalculation(const string& branchName, 
                                  const vector<Person>& data,
                                  int totalSamples) {
        map<string, int> counts;
        for(const Person& p : data) {
            counts[p.ketQua]++;
        }
        
        int nb = data.size();
        double weight = (double)nb / totalSamples;
        
        cout << "  [" << branchName << "]: " << nb << " mẫu (";
        for(auto& pair : counts) {
            cout << pair.first << "=" << pair.second << " ";
        }
        
        // Tính entropy cho nhánh này
        double entropy = 0.0;
        for(auto& pair : counts) {
            if(pair.second > 0) {
                double p = (double)pair.second / nb;
                entropy -= p * log2(p);
            }
        }
        cout << ") → E=" << fixed << setprecision(3) << entropy 
             << ", W=" << fixed << setprecision(3) << weight 
             << ", Đóng góp=" << fixed << setprecision(3) << weight * entropy << endl;
    }
    
public:
    DecisionTreeAnalyzer() {
        // Khởi tạo dữ liệu từ bảng
        dataset = {
            {"Sarah", "Vàng", "Trung bình", "Nhẹ", "Khong", "Cháy nắng"},
            {"Dana", "Vàng", "Cao", "Trung bình", "Có", "Không cháy nắng"},
            {"Alex", "Nâu", "Lùn", "Trung bình", "Có", "Không cháy nắng"},
            {"Annie", "Vàng", "Lùn", "Trung bình", "Khong", "Cháy nắng"},
            {"Emily", "Nâu", "Trung bình", "Nặng", "Khong", "Không cháy nắng"},
            {"Pete", "Nâu", "Cao", "Nặng", "Khong", "Không cháy nắng"},
            {"John", "Nâu", "Trung bình", "Nặng", "Khong", "Không cháy nắng"},
            {"Katie", "Vàng", "Lùn", "Nhẹ", "Có", "Không cháy nắng"}
        };
        
        attributes = {"Màu tóc", "Chiều cao", "Cân nặng", "Dùng kem"};
    }
    
    // Hiển thị dữ liệu
    void showData() {
        cout << "\n========================================" << endl;
        cout << "        DỮ LIỆU HUẤN LUYỆN" << endl;
        cout << "========================================\n" << endl;
        
        cout << "STT | Tên    |    Màu      |       Cao      |      Nặng   |        Kem  | Kết quả" << endl;
        cout << "----|--------|-------------|----------------|-------------|-------------|------------------" << endl;
        
        for(size_t i = 0; i < dataset.size(); i++) {
            cout << setw(2) << (i+1) << "     | " 
                 << setw(6) << dataset[i].ten << "     | "
                 << setw(3) << dataset[i].mauToc.substr(0,3) << "      | "
                 << setw(11) << dataset[i].chieuCao << "    | "
                 << setw(11) << dataset[i].canNang << "     | "
                 << setw(6) << dataset[i].dungKem.substr(0,3) << "     | "
                 << dataset[i].ketQua << endl;
        }
    }
    
    // Phân tích và tính toán
    void analyze() {
        cout << "\n========================================" << endl;
        cout << "     PHÂN TÍCH UY TÍN HỎA ĐỘ" << endl;
        cout << "========================================\n" << endl;
        
        // Tính Entropy ban đầu
        double initialEntropy = EntropyCalculator::calculateEntropy(dataset);
        
        map<string, int> totalCounts;
        for(const Person& p : dataset) {
            totalCounts[p.ketQua]++;
        }
        
        cout << "Entropy ban đầu: " << dataset.size() << " mẫu (";
        for(auto& pair : totalCounts) {
            cout << pair.first << "=" << pair.second << " ";
        }
        cout << ") → E₀ = " << fixed << setprecision(3) << initialEntropy << "\n" << endl;
        
        // Tính toán cho mỗi thuộc tính
        map<string, double> entropies;
        map<string, map<string, vector<Person>>> allSplits;
        
        for(const string& attr : attributes) {
            cout << "• " << attr << ":" << endl;
            
            map<string, vector<Person>> splits;
            double weightedEntropy = EntropyCalculator::calculateWeightedEntropy(
                dataset, attr, splits);
            
            allSplits[attr] = splits;
            
            // Hiển thị chi tiết từng nhánh
            for(auto& split : splits) {
                displayBranchCalculation(split.first, split.second, dataset.size());
            }
            
            entropies[attr] = weightedEntropy;
            cout << "  → NHĐ = " << fixed << setprecision(3) << weightedEntropy << "\n" << endl;
        }
        
        // Tổng kết
        cout << "========================================" << endl;
        cout << "          KẾT QUẢ TỔNG KẾT" << endl;
        cout << "========================================\n" << endl;
        
        string bestAttr;
        double minEntropy = 999999;
        
        for(const string& attr : attributes) {
            cout << attr << ": " << fixed << setprecision(3) << entropies[attr];
            if(entropies[attr] < minEntropy) {
                minEntropy = entropies[attr];
                bestAttr = attr;
                cout << " ★";
            }
            cout << endl;
        }
        
        cout << "\n→ Chọn: " << bestAttr << " (NHĐ nhỏ nhất = " 
             << fixed << setprecision(3) << minEntropy << ")" << endl;
        
        // Hiển thị chi tiết phân nhánh theo màu tóc với số liệu tính toán
        cout << "\n========================================" << endl;
        cout << "   CHI TIẾT TÍNH TOÁN MÀU TÓC" << endl;
        cout << "========================================\n" << endl;
        
        if(allSplits.find("Màu tóc") != allSplits.end()) {
            for(auto& split : allSplits["Màu tóc"]) {
                cout << "• Nhánh Màu tóc = [" << split.first << "]:" << endl;
                
                // Đếm phân loại
                map<string, int> counts;
                for(const Person& p : split.second) {
                    counts[p.ketQua]++;
                }
                
                // Hiển thị danh sách người
                for(const Person& p : split.second) {
                    cout << "  - " << p.ten << " → " << p.ketQua << endl;
                }
                
                // Tính toán
                int total = split.second.size();
                cout << "\n  Tổng: " << total << " người (";
                for(auto& c : counts) {
                    cout << c.first << "=" << c.second << " ";
                }
                cout << ")" << endl;
                
                // Tính entropy
                double entropy = 0.0;
                for(auto& c : counts) {
                    if(c.second > 0) {
                        double p = (double)c.second / total;
                        entropy -= p * log2(p);
                    }
                }
                
                cout << "  Entropy = " << fixed << setprecision(3) << entropy << endl;
                cout << "  Trọng số = " << total << "/" << dataset.size() 
                     << " = " << fixed << setprecision(3) << (double)total/dataset.size() << endl;
                cout << "  Đóng góp vào NHĐ = " << fixed << setprecision(3) 
                     << (double)total/dataset.size() * entropy << "\n" << endl;
            }
            
            cout << "→ NHĐ(Màu tóc) = " << fixed << setprecision(3) 
                 << entropies["Màu tóc"] << " (tổng các đóng góp)" << endl;
        }
    }
};

int main() {
    cout << "\n***** BÀI 11: PHƯƠNG PHÁP UY TÍN HỎA ĐỘ *****" << endl;
    cout << "Xác định hiệu quả của việc sử dụng kem chống nắng\n" << endl;
    
    DecisionTreeAnalyzer analyzer;
    
    // Hiển thị dữ liệu
    analyzer.showData();
    
    // Phân tích
    analyzer.analyze();
    
    cout << "\n========================================\n" << endl;
    
    return 0;
}