#include <iostream>
#include <string>
#include <vector>
#include <limits>
using namespace std;

// CLASS = BAN THIET KE cho may lanh co ban
class MayLanh {
public:
    string hangSX;
    string viTri;
    int congSuat;
    int nhietDo;
    int tocDoGio;
    bool trangThai;

    //CONSTRUCTOR CO THAM SO - Khoi tao may lanh voi thong tin day du
    MayLanh(string hang, string vi, int cs, int nd, int tdg) {
        hangSX = hang;
        viTri = vi;
        congSuat = cs;
        nhietDo = nd;
        tocDoGio = tdg;
        trangThai = false; //MAC DINH MAY LANH TAT
        cout << "== DA KHOI DONG MAY LANH ==" << endl;
        cout << "Hang san xuat: " << hangSX << endl;
        cout << "Vi tri: " << viTri << endl;
        cout << "Cong suat: " << congSuat << " HP" << endl;
        cout << "Nhiet do mac dinh: " << nhietDo << " do C" << endl;
        cout << "Toc do gio mac dinh: " << tocDoGio << endl;
        cout << "Trang thai: " << (trangThai ? "Bat" : "Tat") << endl;
        cout << "==============================" << endl << endl;
    }

    MayLanh() {
        hangSX = "chua xac dinh";
        viTri = "chua xac dinh";
        congSuat = 1;
        nhietDo = 25;
        tocDoGio = 2;
        trangThai = false;
        cout << "== DA KHOI DONG MAY LANH MAC DINH ==" << endl;
        cout << "Thong so mac dinh da duoc gan!" << endl;
        cout << "====================================" << endl << endl;
    }

    // PHUONG THUC PUBLIC = HANH DONG ma may lanh co the thuc hien
    // Bat may lanh
    void batMayLanh() {
        if (!trangThai) {
            trangThai = true;
            cout << "DA BAT may lanh " << hangSX << " tai " << viTri << endl;
            cout << " Nhiet do: " << nhietDo << " do C" << endl;
            cout << " Toc do gio: " << tocDoGio << endl;
        } else {
            cout << "May lanh " << hangSX << " tai " << viTri << " da bat roi!" << endl;
        }
        cout << endl;
    }

    // Tat may lanh
    void tatMayLanh() {
        if (trangThai) {
            trangThai = false;
            cout << "DA TAT may lanh " << hangSX << " tai " << viTri << endl;
        } else {
            cout << "May lanh " << hangSX << " tai " << viTri << " da tat roi!" << endl;
        }
        cout << endl;
    }

    // Tang nhiet do
    void tangNhietDo() {
        if (!trangThai) {
            cout << "Khong the thay doi nhiet do! May lanh dang tat." << endl;
            cout << " Hay bat may lanh truoc!" << endl;
        } else if (nhietDo >= 30) {
            cout << "Nhiet do da dat muc toi da (30 do C)!" << endl;
        } else {
            nhietDo++;
            cout << "Da TANG nhiet do may lanh " << hangSX << " tai " << viTri << endl;
            cout << " Nhiet do hien tai: " << nhietDo << " do C" << endl;
        }
        cout << endl;
    }

    // Giam nhiet do
    void giamNhietDo() {
        if (!trangThai) {
            cout << "Khong the thay doi nhiet do! May lanh dang tat." << endl;
            cout << " Hay bat may lanh truoc!" << endl;
        } else if (nhietDo <= 16) {
            cout << "Nhiet do da dat muc toi thieu (16 do C)!" << endl;
        } else {
            nhietDo--;
            cout << "Da GIAM nhiet do may lanh " << hangSX << " tai " << viTri << endl;
            cout << " Nhiet do hien tai: " << nhietDo << " do C" << endl;
        }
        cout << endl;
    }

    // Tang toc do gio
    void tangTocDoGio() {
        if (!trangThai) {
            cout << "Khong the thay doi toc do gio! May lanh dang tat." << endl;
        } else if (tocDoGio >= 5) {
            cout << "Toc do gio da dat muc toi da (5)!" << endl;
        } else {
            tocDoGio++;
            cout << "Da TANG toc do gio may lanh " << hangSX << " tai " << viTri << endl;
            cout << " Toc do gio hien tai: " << tocDoGio << endl;
        }
        cout << endl;
    }

    // Giam toc do gio
    void giamTocDoGio() {
        if (!trangThai) {
            cout << "Khong the thay doi toc do gio! May lanh dang tat." << endl;
        } else if (tocDoGio <= 1) {
            cout << "Toc do gio da dat muc toi thieu (1)!" << endl;
        } else {
            tocDoGio--;
            cout << "Da GIAM toc do gio may lanh " << hangSX << " tai " << viTri << endl;
            cout << " Toc do gio hien tai: " << tocDoGio << endl;
        }
        cout << endl;
    }

    // Hien thi trang thai chi tiet
    void hienThiTrangThai() {
        cout << "--- TRANG THAI MAY LANH ---" << endl;
        cout << "Hang san xuat: " << hangSX << endl;
        cout << "Vi tri: " << viTri << endl;
        cout << "Cong suat: " << congSuat << " HP" << endl;
        cout << "Trang thai: " << (trangThai ? "Bat" : "Tat") << endl;
        cout << "Nhiet do: " << nhietDo << " do C" << endl;
        cout << "Toc do gio: " << tocDoGio << "/5" << endl;
        cout << "--------------------------" << endl << endl;
    }

    // Thiet lap lai tat ca thong so
    void thietLapLai() {
        string hang, vi;
        int cs, nd, tdg;
        
        cout << "Nhap hang san xuat: ";
        cin.ignore();
        getline(cin, hang);
        
        cout << "Nhap vi tri dat may: ";
        getline(cin, vi);
        
        cout << "Nhap cong suat (HP): ";
        cin >> cs;
        
        cout << "Nhap nhiet do mac dinh (16-30): ";
        cin >> nd;
        if (nd < 16) nd = 16;
        if (nd > 30) nd = 30;
        
        cout << "Nhap toc do gio mac dinh (1-5): ";
        cin >> tdg;
        if (tdg < 1) tdg = 1;
        if (tdg > 5) tdg = 5;
        
        hangSX = hang;
        viTri = vi;
        congSuat = cs;
        nhietDo = nd;
        tocDoGio = tdg;
        trangThai = false;
        
        cout << "Da cap nhat thong tin may lanh!" << endl << endl;
    }
};

// Ham nhap thong tin may lanh moi
MayLanh nhapMayLanhMoi() {
    string hang, vi;
    int cs, nd, tdg;
    
    cout << "=== NHAP THONG TIN MAY LANH MOI ===" << endl;
    cout << "Nhap hang san xuat: ";
    cin.ignore();
    getline(cin, hang);
    
    cout << "Nhap vi tri dat may: ";
    getline(cin, vi);
    
    cout << "Nhap cong suat (HP): ";
    cin >> cs;
    
    cout << "Nhap nhiet do mac dinh (16-30): ";
    cin >> nd;
    if (nd < 16) nd = 16;
    if (nd > 30) nd = 30;
    
    cout << "Nhap toc do gio mac dinh (1-5): ";
    cin >> tdg;
    if (tdg < 1) tdg = 1;
    if (tdg > 5) tdg = 5;
    
    cout << "===================================" << endl << endl;
    
    return MayLanh(hang, vi, cs, nd, tdg);
}

// Ham hien thi menu chinh
void hienThiMenu() {
    cout << "\n========== MENU DIEU KHIEN MAY LANH ==========" << endl;
    cout << "1. Bat may lanh" << endl;
    cout << "2. Tat may lanh" << endl;
    cout << "3. Tang nhiet do" << endl;
    cout << "4. Giam nhiet do" << endl;
    cout << "5. Tang toc do gio" << endl;
    cout << "6. Giam toc do gio" << endl;
    cout << "7. Hien thi trang thai" << endl;
    cout << "8. Thiet lap lai thong tin" << endl;
    cout << "0. Thoat chuong trinh" << endl;
    cout << "=============================================" << endl;
    cout << "Nhap lua chon cua ban: ";
}

int main() {
    cout << "HE THONG DIEU KHIEN MAY LANH THONG MINH" << endl;
    cout << "=======================================" << endl << endl;

    int luaChon;
    cout << "Ban muon:" << endl;
    cout << "1. Tao may lanh moi voi thong tin tu ban" << endl;
    cout << "2. Su dung may lanh mac dinh" << endl;
    cout << "Nhap lua chon (1 hoac 2): ";
    cin >> luaChon;

    MayLanh mayLanh;
    
    if (luaChon == 1) {
        mayLanh = nhapMayLanhMoi();
    } else {
        cout << "Su dung may lanh mac dinh:" << endl;
        // May lanh mac dinh da duoc khoi tao
    }

    int chucNang;
    do {
        hienThiMenu();
        cin >> chucNang;

        switch (chucNang) {
            case 1:
                mayLanh.batMayLanh();
                break;
            case 2:
                mayLanh.tatMayLanh();
                break;
            case 3:
                mayLanh.tangNhietDo();
                break;
            case 4:
                mayLanh.giamNhietDo();
                break;
            case 5:
                mayLanh.tangTocDoGio();
                break;
            case 6:
                mayLanh.giamTocDoGio();
                break;
            case 7:
                mayLanh.hienThiTrangThai();
                break;
            case 8:
                mayLanh.thietLapLai();
                break;
            case 0:
                cout << "Cam on ban da su dung he thong!" << endl;
                cout << "Tam biet!" << endl;
                break;
            default:
                cout << "Lua chon khong hop le! Vui long chon lai." << endl << endl;
        }

        if (chucNang != 0) {
            cout << "Nhan Enter de tiep tuc...";
            cin.ignore();
            cin.get();
        }

    } while (chucNang != 0);

    return 0;
}