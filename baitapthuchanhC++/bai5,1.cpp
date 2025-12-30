#include <iostream>
#include <string>
#include <vector>
using namespace std;

// ========== LỚP TUYẾN ĐƯỜNG ==========
class Tuyen {
private:
    string ten;
    int mau;
    int bac;
    
public:
    // Constructor
    Tuyen(string t) : ten(t), mau(0), bac(0) {}
    
    // Getter
    string getTen() const { return ten; }
    int getMau() const { return mau; }
    int getBac() const { return bac; }
    
    // Setter
    void setMau(int m) { mau = m; }
    void setBac(int b) { bac = b; }
    
    // Hiển thị thông tin
    void hienThi() const {
        cout << ten << ": mau " << mau << ", bac " << bac << "\n";
    }
};

// ========== LỚP BẢN ĐỒ GIAO THÔNG ==========
class BanDoGiaoThong {
private:
    vector<Tuyen*> dsTuyen;
    int maTranKe[13][13];
    int soTuyen;
    
public:
    // Constructor
    BanDoGiaoThong() : soTuyen(13) {
        // Khởi tạo 13 tuyến
        string tenTuyen[13] = {"AB", "AC", "AD", "BA", "BC", "BD", "DA", "DB", "DC", "EA", "EB", "EC", "ED"};
        for (int i = 0; i < 13; i++) {
            dsTuyen.push_back(new Tuyen(tenTuyen[i]));
        }
        
        // Khởi tạo ma trận kề
        int temp[13][13] = {
            {0,0,0,0,1,1,1,0,0,1,0,0,0},
            {0,0,0,0,0,1,1,1,0,1,1,0,0},
            {0,0,0,0,0,0,0,0,0,1,1,1,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0},
            {1,0,0,0,0,0,0,1,0,0,1,0,0},
            {1,1,0,0,0,0,1,0,0,0,1,1,0},
            {1,1,0,0,0,1,0,0,0,0,1,1,0},
            {0,1,0,0,1,0,0,0,0,0,0,1,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0},
            {1,1,1,0,0,0,0,0,0,0,0,0,0},
            {0,1,1,0,1,1,1,0,0,0,0,0,0},
            {0,0,1,0,0,1,1,1,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0}
        };
        
        for (int i = 0; i < 13; i++) {
            for (int j = 0; j < 13; j++) {
                maTranKe[i][j] = temp[i][j];
            }
        }
    }
    
    // Destructor
    ~BanDoGiaoThong() {
        for (auto tuyen : dsTuyen) {
            delete tuyen;
        }
    }
    
    // Gán màu cho tuyến
    void ganMau(int viTri, int mau) {
        if (viTri >= 0 && viTri < soTuyen) {
            dsTuyen[viTri]->setMau(mau);
        }
    }
    
    // Tính bậc cho tất cả tuyến
    void tinhBac() {
        for (int i = 0; i < soTuyen; i++) {
            int dem = 0;
            for (int j = 0; j < soTuyen; j++) {
                dem += maTranKe[i][j];
            }
            dsTuyen[i]->setBac(dem);
        }
    }
    
    // Hiển thị kết quả tô màu
    void hienThiKetQua() {
        cout << "\n===== KẾT QUẢ TÔ MÀU 13 TUYẾN =====\n\n";
        
        for (int m = 1; m <= 4; m++) {
            cout << "MÀU " << m << ": ";
            bool dau = true;
            for (int i = 0; i < soTuyen; i++) {
                if (dsTuyen[i]->getMau() == m) {
                    if (!dau) cout << ", ";
                    cout << dsTuyen[i]->getTen();
                    dau = false;
                }
            }
            cout << "\n";
        }
        cout << "\n=> TỔNG SỐ MÀU: 4\n";
    }
    
    // Hiển thị ma trận kề
    void hienThiMaTran() {
        cout << "\n--- MA TRẬN ---\n";
        cout << "    ";
        for (int j = 0; j < soTuyen; j++) {
            cout << dsTuyen[j]->getTen() << " ";
        }
        cout << "\n";
        
        for (int i = 0; i < soTuyen; i++) {
            cout << dsTuyen[i]->getTen();
            if (dsTuyen[i]->getTen().length() == 2) cout << " ";
            cout << "  ";
            for (int j = 0; j < soTuyen; j++) {
                cout << maTranKe[i][j] << "  ";
            }
            cout << "\n";
        }
    }
    
    // Hiển thị bậc
    void hienThiBac() {
        cout << "\n--- BẬC CỦA TỪNG TUYẾN ---\n";
        for (int i = 0; i < soTuyen; i++) {
            cout << dsTuyen[i]->getTen() << ": " << dsTuyen[i]->getBac() << "\n";
        }
    }
    
    // Kiểm tra tính hợp lệ
    bool kiemTraHopLe() {
        for (int i = 0; i < soTuyen; i++) {
            for (int j = i+1; j < soTuyen; j++) {
                if (maTranKe[i][j] == 1 && dsTuyen[i]->getMau() == dsTuyen[j]->getMau()) {
                    cout << "LOI: " << dsTuyen[i]->getTen() << " va " << dsTuyen[j]->getTen() 
                         << " xung dot nhung cung mau!\n";
                    return false;
                }
            }
        }
        return true;
    }
};

int main() {
    // Tạo bản đồ giao thông
    BanDoGiaoThong* banDo = new BanDoGiaoThong();
    
    // Gán màu theo đáp án (Màu 1: vị trí 0,1,2,3,8,12)
    int mau1[] = {0, 1, 2, 3, 8, 12};  // AB, AC, AD, BA, DC, ED
    int mau2[] = {4, 5, 9};            // BC, BD, EA
    int mau3[] = {6, 7};               // DA, DB
    int mau4[] = {10, 11};             // EB, EC
    
    for (int i : mau1) banDo->ganMau(i, 1);
    for (int i : mau2) banDo->ganMau(i, 2);
    for (int i : mau3) banDo->ganMau(i, 3);
    for (int i : mau4) banDo->ganMau(i, 4);
    
    // Tính bậc
    banDo->tinhBac();
    
    // Hiển thị kết quả
    banDo->hienThiKetQua();
    banDo->hienThiMaTran();
    banDo->hienThiBac();
    
    // Kiểm tra
    cout << "\n--- KIỂM TRA ---\n";
    if (banDo->kiemTraHopLe()) {
        cout << "đáp án ĐÚNG!\n";
    }
    
    // Giải phóng bộ nhớ
    delete banDo;
    
    return 0;
}