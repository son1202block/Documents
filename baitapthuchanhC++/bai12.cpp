#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cmath>
#include <iomanip>
using namespace std;

struct Item {
    string kichCo;      // Trung bình, Lớn, Nhỏ
    string mauSac;      // Đỏ, Vàng, Xanh
    string hinhDang;    // Chữ, Hộp, Tròn, Nón
    string quyetDinh;   // Mua, Không mua
};

class EntropyCalculator {
public:
    static double calculateEntropy(const vector<Item>& data) {
        if(data.empty()) return 0.0;
        
        map<string, int> counts;
        for(const Item& item : data) {
            counts[item.quyetDinh]++;
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
    
    static double calculateWeightedEntropy(const vector<Item>& data, 
                                          const string& attribute,
                                          map<string, vector<Item>>& splits) {
        splits.clear();
        
        for(const Item& item : data) {
            string value;
            if(attribute == "Kích cỡ") value = item.kichCo;
            else if(attribute == "Màu sắc") value = item.mauSac;
            else if(attribute == "Hình dạng") value = item.hinhDang;
            
            splits[value].push_back(item);
        }
        
        double weightedEntropy = 0.0;
        int totalSize = data.size();
        
        for(auto& pair : splits) {
            double weight = (double)pair.second.size() / totalSize;
            double entropy = calculateEntropy(pair.second);
            weightedEntropy += weight * entropy;
        }
        
        return weightedEntropy;
    }
};

class DecisionTreeBuilder {
private:
    vector<Item> dataset;
    vector<string> attributes;
    
    void displayBranch(const string& branchName, const vector<Item>& data, int total) {
        map<string, int> counts;
        for(const Item& item : data) {
            counts[item.quyetDinh]++;
        }
        
        int nb = data.size();
        double entropy = 0.0;
        for(auto& pair : counts) {
            if(pair.second > 0) {
                double p = (double)pair.second / nb;
                entropy -= p * log2(p);
            }
        }
        
        cout << "  [" << branchName << "]: " << nb << " mẫu (";
        for(auto& pair : counts) {
            cout << pair.first << "=" << pair.second << " ";
        }
        cout << ") → E=" << fixed << setprecision(3) << entropy << endl;
    }
    
public:
    DecisionTreeBuilder() {
        dataset = {
            {"Trung bình", "Đỏ", "Chữ", "Mua"},
            {"Lớn", "Vàng", "Hộp", "Mua"},
            {"Trung bình", "Xanh", "Tròn", "Không mua"},
            {"Nhỏ", "Xanh", "Chữ", "Mua"},
            {"Trung bình", "Xanh", "Nón", "Không mua"},
            {"Nhỏ", "Xanh", "Nón", "Không mua"},
            {"Trung bình", "Đỏ", "Tròn", "Mua"}
        };
        
        attributes = {"Kích cỡ", "Màu sắc", "Hình dạng"};
    }
    
    void showData() {
        cout << "\n========================================" << endl;
        cout << "          DỮ LIỆU HUẤN LUYỆN" << endl;
        cout << "========================================\n" << endl;
        
        cout << "STT | Kích cỡ     | Màu sắc | Hình dạng | Quyết định" << endl;
        cout << "----|--------------|---------|-----------|------------" << endl;
        
        for(size_t i = 0; i < dataset.size(); i++) {
            cout << setw(2) << (i+1) << "  | " 
                 << setw(12) << dataset[i].kichCo << " | "
                 << setw(7) << dataset[i].mauSac << " | "
                 << setw(9) << dataset[i].hinhDang << " | "
                 << dataset[i].quyetDinh << endl;
        }
    }
    
    void buildTree() {
        cout << "\n========================================" << endl;
        cout << "    XÂY DỰNG CÂY QUYẾT ĐỊNH" << endl;
        cout << "========================================\n" << endl;
        
        // Tính entropy ban đầu
        double initialEntropy = EntropyCalculator::calculateEntropy(dataset);
        map<string, int> totalCounts;
        for(const Item& item : dataset) {
            totalCounts[item.quyetDinh]++;
        }
        
        cout << "Entropy ban đầu: (";
        for(auto& pair : totalCounts) {
            cout << pair.first << "=" << pair.second << " ";
        }
        cout << ") → E₀ = " << fixed << setprecision(3) << initialEntropy << "\n" << endl;
        
        // Tính toán cho từng thuộc tính
        map<string, double> entropies;
        
        for(const string& attr : attributes) {
            cout << "• " << attr << ":" << endl;
            
            map<string, vector<Item>> splits;
            double weightedEntropy = EntropyCalculator::calculateWeightedEntropy(
                dataset, attr, splits);
            
            for(auto& split : splits) {
                displayBranch(split.first, split.second, dataset.size());
            }
            
            entropies[attr] = weightedEntropy;
            cout << "  → Độ hỗn loạn TB = " << fixed << setprecision(3) 
                 << weightedEntropy << "\n" << endl;
        }
        
        // Kết quả
        cout << "========================================" << endl;
        cout << "            KẾT QUẢ" << endl;
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
        
        cout << "\n→ Gốc cây: " << bestAttr << " (độ hỗn loạn nhỏ nhất)" << endl;
        
        // Xây dựng tiếp nhánh
        buildSubTree();
    }
    
    void buildSubTree() {
        cout << "\n========================================" << endl;
        cout << "      XÂY DỰNG CÁC NHÁNH CON" << endl;
        cout << "========================================\n" << endl;
        
        // Nhánh Hình dạng = Chữ (Nhánh = 0)
        cout << "NHÁNH: Hình dạng = Chữ" << endl;
        vector<Item> branch1;
        for(const Item& item : dataset) {
            if(item.hinhDang == "Chữ") branch1.push_back(item);
        }
        
        map<string, int> counts1;
        for(const Item& item : branch1) {
            counts1[item.quyetDinh]++;
        }
        
        cout << "  " << branch1.size() << " mẫu (";
        for(auto& p : counts1) {
            cout << p.first << "=" << p.second << " ";
        }
        cout << ")" << endl;
        
        if(counts1.size() == 1) {
            cout << "  → NÚT LÁ: " << counts1.begin()->first << " (thuần khiết)\n" << endl;
        }
        
        // Nhánh Hình dạng = Hộp
        cout << "NHÁNH: Hình dạng = Hộp" << endl;
        vector<Item> branch2;
        for(const Item& item : dataset) {
            if(item.hinhDang == "Hộp") branch2.push_back(item);
        }
        
        map<string, int> counts2;
        for(const Item& item : branch2) {
            counts2[item.quyetDinh]++;
        }
        
        cout << "  " << branch2.size() << " mẫu (";
        for(auto& p : counts2) {
            cout << p.first << "=" << p.second << " ";
        }
        cout << ")" << endl;
        
        if(counts2.size() == 1) {
            cout << "  → NÚT LÁ: " << counts2.begin()->first << " (thuần khiết)\n" << endl;
        }
        
        // Nhánh Hình dạng = Tròn/Nón (cần phân tách tiếp)
        cout << "NHÁNH: Hình dạng = Tròn hoặc Nón" << endl;
        vector<Item> branch3;
        for(const Item& item : dataset) {
            if(item.hinhDang == "Tròn" || item.hinhDang == "Nón") {
                branch3.push_back(item);
            }
        }
        
        cout << "  " << branch3.size() << " mẫu (còn hỗn hợp)" << endl;
        cout << "  → Tiếp tục phân tách bằng thuộc tính khác\n" << endl;
        
        // Phân tích thuộc tính cho nhánh này
        vector<string> remainingAttrs = {"Kích cỡ", "Màu sắc"};
        
        cout << "  Tính độ hỗn loạn cho nhánh này:" << endl;
        for(const string& attr : remainingAttrs) {
            map<string, vector<Item>> splits;
            double entropy = EntropyCalculator::calculateWeightedEntropy(branch3, attr, splits);
            cout << "    " << attr << ": " << fixed << setprecision(3) << entropy << endl;
        }
        
        cout << "\n  → Chọn Màu sắc (độ hỗn loạn = 0)" << endl;
        cout << "    • Màu sắc = Đỏ → Mua" << endl;
        cout << "    • Màu sắc = Xanh → Không mua" << endl;
    }
};

int main() {
    cout << "\n***** ĐỘ HỖN LOẠN - QUYẾT ĐỊNH MUA HÀNG *****" << endl;
    
    DecisionTreeBuilder builder;
    
    builder.showData();
    builder.buildTree();
    
    cout << "\n========================================\n" << endl;
    
    return 0;
}