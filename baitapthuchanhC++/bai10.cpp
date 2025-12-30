#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <cmath>
#include <iomanip>
using namespace std;

// Cấu trúc dữ liệu người
struct Person {
    string dang;        // Tô / Nhoû
    string chieuCao;    // Trung bình / Thấp / Cao
    string gioiTinh;    // Nam / Nữ
    string thuocChau;   // Châu ÁÚ / Châu Áà
};

// Lớp nút cây quyết định
class DecisionNode {
public:
    string attribute;                          // Thuộc tính phân chia
    string classification;                     // Kết quả phân loại (nếu là lá)
    map<string, DecisionNode*> children;       // Con của nút
    bool isLeaf;                              // Có phải nút lá không
    
    DecisionNode() : isLeaf(false) {}
    
    ~DecisionNode() {
        for(auto& child : children) {
            delete child.second;
        }
    }
};

// Lớp xây dựng cây quyết định theo thuật toán ID3 (QuinLan)
class ID3Algorithm {
private:
    vector<Person> dataset;
    vector<string> attributes;
    
    // Tính Entropy của tập dữ liệu
    double calculateEntropy(const vector<Person>& data) {
        if(data.empty()) return 0.0;
        
        map<string, int> counts;
        for(const Person& p : data) {
            counts[p.thuocChau]++;
        }
        
        double entropy = 0.0;
        int total = data.size();
        
        for(auto& pair : counts) {
            double probability = (double)pair.second / total;
            if(probability > 0) {
                entropy -= probability * log2(probability);
            }
        }
        
        return entropy;
    }
    
    // Lấy giá trị của thuộc tính
    string getAttributeValue(const Person& p, const string& attr) {
        if(attr == "Dạng") return p.dang;
        if(attr == "Chiều cao") return p.chieuCao;
        if(attr == "Giới tính") return p.gioiTinh;
        return "";
    }
    
    // Phân tách dữ liệu theo thuộc tính
    map<string, vector<Person>> splitByAttribute(const vector<Person>& data, const string& attr) {
        map<string, vector<Person>> splits;
        
        for(const Person& p : data) {
            string value = getAttributeValue(p, attr);
            splits[value].push_back(p);
        }
        
        return splits;
    }
    
    // Tính Information Gain
    double calculateGain(const vector<Person>& data, const string& attr) {
        double parentEntropy = calculateEntropy(data);
        
        map<string, vector<Person>> splits = splitByAttribute(data, attr);
        
        double weightedEntropy = 0.0;
        int totalSize = data.size();
        
        for(auto& pair : splits) {
            double weight = (double)pair.second.size() / totalSize;
            weightedEntropy += weight * calculateEntropy(pair.second);
        }
        
        return parentEntropy - weightedEntropy;
    }
    
    // Tìm thuộc tính tốt nhất để phân chia
    string findBestAttribute(const vector<Person>& data, const vector<string>& availableAttrs) {
        string bestAttr;
        double maxGain = -1.0;
        
        cout << "\n  Tính Information Gain cho các thuộc tính:" << endl;
        
        for(const string& attr : availableAttrs) {
            double gain = calculateGain(data, attr);
            cout << "    " << attr << ": Gain = " << fixed << setprecision(4) << gain << endl;
            
            if(gain > maxGain) {
                maxGain = gain;
                bestAttr = attr;
            }
        }
        
        cout << "  → Chọn thuộc tính: " << bestAttr << " (Gain cao nhất = " 
             << fixed << setprecision(4) << maxGain << ")\n" << endl;
        
        return bestAttr;
    }
    
    // Kiểm tra xem tất cả dữ liệu có cùng lớp không
    bool allSameClass(const vector<Person>& data) {
        if(data.empty()) return true;
        
        string firstClass = data[0].thuocChau;
        for(const Person& p : data) {
            if(p.thuocChau != firstClass) return false;
        }
        return true;
    }
    
    // Lấy lớp phổ biến nhất
    string getMajorityClass(const vector<Person>& data) {
        map<string, int> counts;
        for(const Person& p : data) {
            counts[p.thuocChau]++;
        }
        
        string majorityClass;
        int maxCount = 0;
        for(auto& pair : counts) {
            if(pair.second > maxCount) {
                maxCount = pair.second;
                majorityClass = pair.first;
            }
        }
        
        return majorityClass;
    }
    
    // Xây dựng cây đệ quy
    DecisionNode* buildTree(const vector<Person>& data, vector<string> availableAttrs, int depth) {
        DecisionNode* node = new DecisionNode();
        
        // Trường hợp dừng 1: Tất cả cùng lớp
        if(allSameClass(data)) {
            node->isLeaf = true;
            node->classification = data[0].thuocChau;
            cout << string(depth * 2, ' ') << "→ Nút lá: " << node->classification << endl;
            return node;
        }
        
        // Trường hợp dừng 2: Hết thuộc tính
        if(availableAttrs.empty()) {
            node->isLeaf = true;
            node->classification = getMajorityClass(data);
            cout << string(depth * 2, ' ') << "→ Nút lá (đa số): " << node->classification << endl;
            return node;
        }
        
        // Chọn thuộc tính tốt nhất
        cout << string(depth * 2, ' ') << "Độ sâu " << depth << " - Xét " << data.size() << " mẫu:" << endl;
        string bestAttr = findBestAttribute(data, availableAttrs);
        node->attribute = bestAttr;
        
        // Xóa thuộc tính đã chọn
        vector<string> remainingAttrs;
        for(const string& attr : availableAttrs) {
            if(attr != bestAttr) remainingAttrs.push_back(attr);
        }
        
        // Phân nhánh theo các giá trị của thuộc tính
        map<string, vector<Person>> splits = splitByAttribute(data, bestAttr);
        
        for(auto& pair : splits) {
            cout << string(depth * 2, ' ') << "Nhánh " << bestAttr << " = " << pair.first << ":" << endl;
            node->children[pair.first] = buildTree(pair.second, remainingAttrs, depth + 1);
        }
        
        return node;
    }
    
    // In cây quyết định
    void printTree(DecisionNode* node, string prefix, string value) {
        if(node->isLeaf) {
            cout << prefix << "└─ " << value << " → " << node->classification << endl;
        } else {
            cout << prefix << "└─ " << value << " [" << node->attribute << "]" << endl;
            
            int count = 0;
            for(auto& child : node->children) {
                count++;
                string newPrefix = prefix;
                if(value != "") {
                    newPrefix += (count < node->children.size()) ? "│  " : "   ";
                }
                printTree(child.second, newPrefix, child.first);
            }
        }
    }
    
public:
    // Constructor
    ID3Algorithm() {
        // Khởi tạo dữ liệu từ bảng
        dataset = {
            {"Tô", "Trung bình", "Nam", "Châu ÁU"},      // 1
            {"Nhoû", "Thấp", "Nam", "Châu ÁU"},           // 2
            {"Nhoû", "Trung bình", "Nam", "Châu ÁU"},     // 3
            {"Tô", "Cao", "Nam", "Châu Áà"},              // 4
            {"Nhoû", "Thấp", "Nữ", "Châu Áà"},            // 5
            {"Nhoû", "Cao", "Nam", "Châu Áà"},            // 6
            {"Nhoû", "Cao", "Nữ", "Châu Áà"},             // 7
            {"Tô", "Trung bình", "Nữ", "Châu Áà"}         // 8
        };
        
        attributes = {"Dạng", "Chiều cao", "Giới tính"};
    }
    
    // Hiển thị dữ liệu
    void showData() {
        cout << "\n========================================" << endl;
        cout << "   DỮ LIỆU HUẤN LUYỆN" << endl;
        cout << "========================================\n" << endl;
        
        cout << "STT | Dạng  | Chiều cao   | Giới tính | Thuộc châu" << endl;
        cout << "----|-------|-------------|-----------|------------" << endl;
        
        for(size_t i = 0; i < dataset.size(); i++) {
            cout << setw(2) << (i+1) << "  | " 
                 << setw(5) << dataset[i].dang << " | "
                 << setw(11) << dataset[i].chieuCao << " | "
                 << setw(9) << dataset[i].gioiTinh << " | "
                 << dataset[i].thuocChau << endl;
        }
    }
    
    // Xây dựng cây
    DecisionNode* train() {
        cout << "\n========================================" << endl;
        cout << "   XÂY DỰNG CÂY QUYẾT ĐỊNH (ID3)" << endl;
        cout << "========================================\n" << endl;
        
        double initialEntropy = calculateEntropy(dataset);
        cout << "Entropy ban đầu: " << fixed << setprecision(4) << initialEntropy << "\n" << endl;
        
        return buildTree(dataset, attributes, 0);
    }
    
    // Hiển thị cây
    void displayTree(DecisionNode* root) {
        cout << "\n========================================" << endl;
        cout << "   CÂY QUYẾT ĐỊNH" << endl;
        cout << "========================================\n" << endl;
        
        printTree(root, "", "Root");
    }
    
    // Phân loại người mới
    string classify(DecisionNode* root, const Person& person) {
        DecisionNode* current = root;
        
        cout << "\nQuá trình phân loại:" << endl;
        
        while(!current->isLeaf) {
            string attrValue = getAttributeValue(person, current->attribute);
            cout << "  " << current->attribute << " = " << attrValue;
            
            if(current->children.find(attrValue) == current->children.end()) {
                cout << " → Không tìm thấy nhánh!" << endl;
                return "Không xác định";
            }
            
            current = current->children[attrValue];
            cout << endl;
        }
        
        cout << "  → Kết quả: " << current->classification << endl;
        return current->classification;
    }
};

int main() {
    cout << "\n***** BÀI 10: THUẬT TOÁN QUINLAN (ID3) *****\n" << endl;
    
    ID3Algorithm id3;
    
    // Hiển thị dữ liệu
    id3.showData();
    
    // Xây dựng cây
    DecisionNode* tree = id3.train();
    
    // Hiển thị cây
    id3.displayTree(tree);
    
    // Test với người mới
    cout << "\n========================================" << endl;
    cout << "   PHÂN LOẠI NGƯỜI MỚI" << endl;
    cout << "========================================" << endl;
    
    Person test1 = {"Tô", "Cao", "Nữ", ""};
    cout << "\nNgười 1: Dạng=Tô, Chiều cao=Cao, Giới tính=Nữ" << endl;
    string result1 = id3.classify(tree, test1);
    
    Person test2 = {"Nhoû", "Thấp", "Nam", ""};
    cout << "\nNgười 2: Dạng=Nhoû, Chiều cao=Thấp, Giới tính=Nam" << endl;
    string result2 = id3.classify(tree, test2);
    
    // Giải phóng bộ nhớ
    delete tree;
    
    return 0;
}