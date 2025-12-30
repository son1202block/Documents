#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
using namespace std;

// Khai báo cấu trúc nhân viên
struct NhanVien {
    string ten;
    string maNV;
    float luongThang;
};

// Khai báo cấu trúc quản lý danh sách nhân viên
struct DanhSachNhanVien {
    NhanVien ds[5];
    int soLuong;
};

// Hàm nhập thông tin một nhân viên
void nhapNhanVien(NhanVien &nv) {
    cout << "Nhap ten nhan vien: ";
    getline(cin, nv.ten);
    cout << "Nhap ma nhan vien: ";
    getline(cin, nv.maNV);
    cout << "Nhap luong thang: ";
    cin >> nv.luongThang;
    cin.ignore(); // Xóa ký tự xuống dòng sau khi nhập số
}

// Hàm nhập danh sách nhân viên
void nhapDanhSach(DanhSachNhanVien &dsnv) {
    cout << "Nhap so luong nhan vien (toi da 5): ";
    cin >> dsnv.soLuong;
    cin.ignore(); // Xóa ký tự xuống dòng sau khi nhập số
    
    if (dsnv.soLuong > 5) {
        cout << "So luong vuot qua gioi han, chi nhan 5 nhan vien!\n";
        dsnv.soLuong = 5;
    }
    
    for (int i = 0; i < dsnv.soLuong; i++) {
        cout << "\nNhap thong tin nhan vien thu " << (i + 1) << ":\n";
        nhapNhanVien(dsnv.ds[i]);
    }
}

// Hàm xuất thông tin một nhân viên
void xuatNhanVien(const NhanVien &nv) {
    cout << left << setw(25) << nv.ten 
         << setw(15) << nv.maNV 
         << setw(15) << fixed << setprecision(2) << nv.luongThang << " VND\n";
}

// Hàm xuất danh sách nhân viên
void xuatDanhSach(const DanhSachNhanVien &dsnv) {
    cout << "\n=== DANH SACH NHAN VIEN ===\n";
    cout << left << setw(25) << "Ten nhan vien" 
         << setw(15) << "Ma nhan vien" 
         << setw(15) << "Luong thang" << endl;
    cout << string(55, '-') << endl;
    
    for (int i = 0; i < dsnv.soLuong; i++) {
        xuatNhanVien(dsnv.ds[i]);
    }
}

// Hàm tìm lương cao nhất
float timLuongCaoNhat(const DanhSachNhanVien &dsnv) {
    if (dsnv.soLuong == 0) return 0;
    
    float max = dsnv.ds[0].luongThang;
    for (int i = 1; i < dsnv.soLuong; i++) {
        if (dsnv.ds[i].luongThang > max) {
            max = dsnv.ds[i].luongThang;
        }
    }
    return max;
}

// Hàm tìm lương thấp nhất
float timLuongThapNhat(const DanhSachNhanVien &dsnv) {
    if (dsnv.soLuong == 0) return 0;
    
    float min = dsnv.ds[0].luongThang;
    for (int i = 1; i < dsnv.soLuong; i++) {
        if (dsnv.ds[i].luongThang < min) {
            min = dsnv.ds[i].luongThang;
        }
    }
    return min;
}

// Hàm liệt kê nhân viên có lương cao nhất
void lietKeNhanVienLuongCaoNhat(const DanhSachNhanVien &dsnv) {
    float luongMax = timLuongCaoNhat(dsnv);
    cout << "\nNhan vien co luong cao nhat (" << fixed << setprecision(2) << luongMax << " VND):\n";
    
    for (int i = 0; i < dsnv.soLuong; i++) {
        if (dsnv.ds[i].luongThang == luongMax) {
            cout << "- " << dsnv.ds[i].ten << ": " << dsnv.ds[i].luongThang << " VND\n";
        }
    }
}

// Hàm tìm nhân viên theo mã số
int timNhanVienTheoMa(const DanhSachNhanVien &dsnv, const string &maNV) {
    for (int i = 0; i < dsnv.soLuong; i++) {
        if (dsnv.ds[i].maNV == maNV) {
            return i;
        }
    }
    return -1; // Không tìm thấy
}

// Hàm tìm nhân viên theo tên
void timNhanVienTheoTen(const DanhSachNhanVien &dsnv, const string &ten) {
    bool timThay = false;
    cout << "\nKet qua tim kiem theo ten '" << ten << "':\n";
    
    for (int i = 0; i < dsnv.soLuong; i++) {
        if (dsnv.ds[i].ten.find(ten) != string::npos) {
            xuatNhanVien(dsnv.ds[i]);
            timThay = true;
        }
    }
    
    if (!timThay) {
        cout << "Khong tim thay nhan vien nao!\n";
    }
}

// Hàm đếm nhân viên có lương >= 5 triệu
int demNhanVienLuongCao(const DanhSachNhanVien &dsnv) {
    int dem = 0;
    for (int i = 0; i < dsnv.soLuong; i++) {
        if (dsnv.ds[i].luongThang >= 5000000) {
            dem++;
        }
    }
    return dem;
}

// Hàm xóa nhân viên theo mã số
bool xoaNhanVienTheoMa(DanhSachNhanVien &dsnv, const string &maNV) {
    int viTri = timNhanVienTheoMa(dsnv, maNV);
    if (viTri == -1) {
        return false; // Không tìm thấy
    }
    
    // Dịch chuyển các phần tử về phía trước
    for (int i = viTri; i < dsnv.soLuong - 1; i++) {
        dsnv.ds[i] = dsnv.ds[i + 1];
    }
    dsnv.soLuong--;
    return true;
}

// Hàm sắp xếp danh sách theo lương tăng dần
void sapXepTheoLuong(DanhSachNhanVien &dsnv) {
    for (int i = 0; i < dsnv.soLuong - 1; i++) {
        for (int j = 0; j < dsnv.soLuong - i - 1; j++) {
            if (dsnv.ds[j].luongThang > dsnv.ds[j + 1].luongThang) {
                NhanVien temp = dsnv.ds[j];
                dsnv.ds[j] = dsnv.ds[j + 1];
                dsnv.ds[j + 1] = temp;
            }
        }
    }
}

// Hàm hiển thị menu
void hienThiMenu() {
    cout << "\n=== MENU QUAN LY NHAN VIEN ===\n";
    cout << "1. Nhap danh sach nhan vien\n";
    cout << "2. Xuat danh sach nhan vien\n";
    cout << "3. Tim luong cao nhat\n";
    cout << "4. Tim luong thap nhat\n";
    cout << "5. Liet ke nhan vien co luong cao nhat\n";
    cout << "6. Tim nhan vien theo ma so\n";
    cout << "7. Tim nhan vien theo ten\n";
    cout << "8. Dem nhan vien co luong >= 5 trieu\n";
    cout << "9. Xoa nhan vien theo ma so\n";
    cout << "10. Sap xep theo luong tang dan\n";
    cout << "0. Thoat\n";
    cout << "Chon chuc nang: ";
}

int main() {
    DanhSachNhanVien dsnv;
    dsnv.soLuong = 0;
    int luaChon;
    string maTim, tenTim;
    int viTri;
    
    do {
        hienThiMenu();
        cin >> luaChon;
        
        switch (luaChon) {
            case 1:
                nhapDanhSach(dsnv);
                break;
                
            case 2:
                if (dsnv.soLuong == 0) {
                    cout << "Danh sach rong!\n";
                } else {
                    xuatDanhSach(dsnv);
                }
                break;
                
            case 3:
                if (dsnv.soLuong == 0) {
                    cout << "Danh sach rong!\n";
                } else {
                    cout << "Luong cao nhat: " << fixed << setprecision(2) 
                         << timLuongCaoNhat(dsnv) << " VND\n";
                }
                break;
                
            case 4:
                if (dsnv.soLuong == 0) {
                    cout << "Danh sach rong!\n";
                } else {
                    cout << "Luong thap nhat: " << fixed << setprecision(2) 
                         << timLuongThapNhat(dsnv) << " VND\n";
                }
                break;
                
            case 5:
                if (dsnv.soLuong == 0) {
                    cout << "Danh sach rong!\n";
                } else {
                    lietKeNhanVienLuongCaoNhat(dsnv);
                }
                break;
                
            case 6:
                cout << "Nhap ma nhan vien can tim: ";
                cin.ignore();
                getline(cin, maTim);
                viTri = timNhanVienTheoMa(dsnv, maTim);
                if (viTri != -1) {
                    cout << "Tim thay nhan vien:\n";
                    cout << left << setw(25) << "Ten nhan vien" 
                         << setw(15) << "Ma nhan vien" 
                         << setw(15) << "Luong thang" << endl;
                    cout << string(55, '-') << endl;
                    xuatNhanVien(dsnv.ds[viTri]);
                } else {
                    cout << "Khong tim thay nhan vien co ma " << maTim << "\n";
                }
                break;
                
            case 7:
                cout << "Nhap ten nhan vien can tim: ";
                cin.ignore();
                getline(cin, tenTim);
                timNhanVienTheoTen(dsnv, tenTim);
                break;
                
            case 8:
                cout << "So nhan vien co luong >= 5 trieu: " 
                     << demNhanVienLuongCao(dsnv) << " nguoi\n";
                break;
                
            case 9:
                cout << "Nhap ma nhan vien can xoa: ";
                cin.ignore();
                getline(cin, maTim);
                if (xoaNhanVienTheoMa(dsnv, maTim)) {
                    cout << "Da xoa nhan vien co ma " << maTim << "\n";
                } else {
                    cout << "Khong tim thay nhan vien co ma " << maTim << "\n";
                }
                break;
                
            case 10:
                if (dsnv.soLuong == 0) {
                    cout << "Danh sach rong!\n";
                } else {
                    sapXepTheoLuong(dsnv);
                    cout << "Da sap xep danh sach theo luong tang dan!\n";
                }
                break;
                
            case 0:
                cout << "Cam on ban da su dung chuong trinh!\n";
                break;
                
            default:
                cout << "Lua chon khong hop le!\n";
        }
        
        if (luaChon != 0) {
            cout << "\nNhan Enter de tiep tuc...";
            cin.ignore();
            cin.get();
        }
        
    } while (luaChon != 0);
    
    return 0;
}