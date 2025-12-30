#include <iostream>
#include <cmath>
using namespace std;

class PhanSo {
private:
    int tuSo;
    int mauSo;
    
    // Hàm tìm ước chung lớn nhất
    int ucln(int a, int b) {
        a = abs(a);
        b = abs(b);
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }
    
public:
    // Constructor mặc định
    PhanSo() {
        tuSo = 0;
        mauSo = 1;
    }
    
    // Constructor có tham số
    PhanSo(int tu, int mau) {
        tuSo = tu;
        mauSo = (mau != 0) ? mau : 1;
        rutGon();
    }
    
    // Phương thức nhập phân số
    void nhap() {
        cout << "Nhap tu so: ";
        cin >> tuSo;
        
        do {
            cout << "Nhap mau so (khac 0): ";
            cin >> mauSo;
            if (mauSo == 0) {
                cout << "Loi: Mau so phai khac 0! Vui long nhap lai." << endl;
            }
        } while (mauSo == 0);
        
        rutGon();
    }
    
    // Phương thức xuất phân số
    void xuat() const {
        if (mauSo == 1) {
            cout << tuSo;
        } else if (tuSo == 0) {
            cout << "0";
        } else {
            cout << tuSo << "/" << mauSo;
        }
    }
    
    // Phương thức rút gọn phân số
    void rutGon() {
        if (mauSo < 0) {
            tuSo = -tuSo;
            mauSo = -mauSo;
        }
        
        int uc = ucln(tuSo, mauSo);
        if (uc > 1) {
            tuSo /= uc;
            mauSo /= uc;
        }
    }
    
    // Phương thức cộng phân số
    PhanSo cong(const PhanSo& ps) const {
        int tu = tuSo * ps.mauSo + ps.tuSo * mauSo;
        int mau = mauSo * ps.mauSo;
        return PhanSo(tu, mau);
    }
    
    // Phương thức trừ phân số
    PhanSo tru(const PhanSo& ps) const {
        int tu = tuSo * ps.mauSo - ps.tuSo * mauSo;
        int mau = mauSo * ps.mauSo;
        return PhanSo(tu, mau);
    }
    
    // Phương thức nhân phân số
    PhanSo nhan(const PhanSo& ps) const {
        int tu = tuSo * ps.tuSo;
        int mau = mauSo * ps.mauSo;
        return PhanSo(tu, mau);
    }
    
    // Phương thức chia phân số
    PhanSo chia(const PhanSo& ps) const {
        if (ps.tuSo == 0) {
            cout << "Loi: Khong the chia cho 0!" << endl;
            return PhanSo();
        }
        int tu = tuSo * ps.mauSo;
        int mau = mauSo * ps.tuSo;
        return PhanSo(tu, mau);
    }
};

int main() {
    PhanSo ps1, ps2;
    
    cout << "Nhap phan so thu nhat:" << endl;
    ps1.nhap();
    
    cout << "Nhap phan so thu hai:" << endl;
    ps2.nhap();
    
    cout << "Phan so 1: ";
    ps1.xuat();
    cout << endl;
    
    cout << "Phan so 2: ";
    ps2.xuat();
    cout << endl;
    
    PhanSo ketQua = ps1.cong(ps2);
    cout << "Tong: ";
    ketQua.xuat();
    cout << endl;
    
    ketQua = ps1.tru(ps2);
    cout << "Hieu: ";
    ketQua.xuat();
    cout << endl;
    
    ketQua = ps1.nhan(ps2);
    cout << "Tich: ";
    ketQua.xuat();
    cout << endl;
    
    ketQua = ps1.chia(ps2);
    cout << "Thuong: ";
    ketQua.xuat();
    cout << endl;
    
    return 0;
}