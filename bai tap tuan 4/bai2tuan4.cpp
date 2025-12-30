#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class TaiKhoan {
private:
    string tenTK;      // Tên tài khoản
    string soTK;       // Số tài khoản  
    double soDu;       // Số dư tài khoản
    static constexpr double PHI_RUT = 2000; // Phí rút tiền

public:
    // Constructor mặc định
    TaiKhoan() {
        tenTK = "";
        soTK = "";
        soDu = 0.0;
    }
    
    // Constructor có tham số
    TaiKhoan(string ten, string so, double du) {
        tenTK = ten;
        soTK = so;
        soDu = (du >= 0) ? du : 0.0;
    }
    
    // Phương thức nhập thông tin tài khoản
    void nhapThongTin() {
        cin.ignore(); // Xóa bộ đệm
        cout << "Nhap ten tai khoan: ";
        getline(cin, tenTK);
        
        cout << "Nhap so tai khoan: ";
        getline(cin, soTK);
        
        do {
            cout << "Nhap so du ban dau: ";
            cin >> soDu;
            if (soDu < 0) {
                cout << "Loi: So du phai >= 0! Vui long nhap lai." << endl;
            }
        } while (soDu < 0);
    }
    
    // Phương thức hiển thị thông tin tài khoản
    void hienThiThongTin() const {
        cout << "Ten TK: " << tenTK << endl;
        cout << "So TK: " << soTK << endl;
        cout << "So du: " << fixed << setprecision(0) << soDu << " VND" << endl;
    }
    
    // Getter cho số dư
    double getSoDu() const {
        return soDu;
    }
    
    // Getter cho tên tài khoản
    string getTenTK() const {
        return tenTK;
    }
    
    // Phương thức nạp tiền
    bool napTien(double soTien) {
        if (soTien <= 0) {
            cout << "Loi: So tien nap phai > 0!" << endl;
            return false;
        }
        
        soDu += soTien;
        cout << "Nap tien thanh cong! So tien nap: " << fixed << setprecision(0) << soTien << " VND" << endl;
        cout << "So du moi: " << fixed << setprecision(0) << soDu << " VND" << endl;
        return true;
    }
    
    // Phương thức rút tiền (có phí)
    bool rutTien(double soTien) {
        if (soTien <= 0) {
            cout << "Loi: So tien rut phai > 0!" << endl;
            return false;
        }
        
        double tongTien = soTien + PHI_RUT;
        if (soDu < tongTien) {
            cout << "Loi: So du khong du! Can: " << fixed << setprecision(0) << tongTien 
                 << " VND (bao gom phi " << PHI_RUT << " VND)" << endl;
            return false;
        }
        
        soDu -= tongTien;
        cout << "Rut tien thanh cong! So tien rut: " << fixed << setprecision(0) << soTien 
             << " VND (phi: " << PHI_RUT << " VND)" << endl;
        cout << "So du moi: " << fixed << setprecision(0) << soDu << " VND" << endl;
        return true;
    }
    
    // Phương thức chuyển khoản
    bool chuyenKhoan(TaiKhoan& tkNhan, double soTien) {
        if (soTien <= 0) {
            cout << "Loi: So tien chuyen phai > 0!" << endl;
            return false;
        }
        
        if (soDu < soTien) {
            cout << "Loi: So du khong du de chuyen khoan!" << endl;
            return false;
        }
        
        soDu -= soTien;
        tkNhan.soDu += soTien;
        
        cout << "Chuyen khoan thanh cong!" << endl;
        cout << "Tu TK: " << tenTK << " -> Den TK: " << tkNhan.tenTK << endl;
        cout << "So tien: " << fixed << setprecision(0) << soTien << " VND" << endl;
        cout << "So du con lai: " << fixed << setprecision(0) << soDu << " VND" << endl;
        return true;
    }
};

int main() {
    cout << "=== CHUONG TRINH QUAN LY TAI KHOAN NGAN HANG ===" << endl << endl;
    
    TaiKhoan tk1, tk2;
    
    cout << "Nhap thong tin tai khoan thu nhat:" << endl;
    tk1.nhapThongTin();
    
    cout << "\nNhap thong tin tai khoan thu hai:" << endl;
    tk2.nhapThongTin();
    
    cout << "\n=== THONG TIN TAI KHOAN BAN DAU ===" << endl;
    cout << "\nTai khoan 1:" << endl;
    tk1.hienThiThongTin();
    
    cout << "\nTai khoan 2:" << endl;
    tk2.hienThiThongTin();
    
    cout << "\n=== THUC HIEN GIAO DICH ===" << endl;
    
    // Giao dịch nạp tiền
    double soTien;
    cout << "\n1. Nap tien vao tai khoan 1:" << endl;
    cout << "Nhap so tien muon nap: ";
    cin >> soTien;
    tk1.napTien(soTien);
    
    // Giao dịch rút tiền  
    cout << "\n2. Rut tien tu tai khoan 1:" << endl;
    cout << "Nhap so tien muon rut: ";
    cin >> soTien;
    tk1.rutTien(soTien);
    
    // Giao dịch chuyển khoản
    cout << "\n3. Chuyen khoan tu tai khoan 1 sang tai khoan 2:" << endl;
    cout << "Nhap so tien muon chuyen: ";
    cin >> soTien;
    tk1.chuyenKhoan(tk2, soTien);
    
    cout << "\n=== THONG TIN TAI KHOAN SAU GIAO DICH ===" << endl;
    cout << "\nTai khoan 1:" << endl;
    tk1.hienThiThongTin();
    
    cout << "\nTai khoan 2:" << endl;
    tk2.hienThiThongTin();
    
    return 0;
}
