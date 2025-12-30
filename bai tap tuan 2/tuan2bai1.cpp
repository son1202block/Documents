#include <iostream>
#include <string>
using namespace std;
// class = BAN THIET KE cho den led co ban
class DenLED {
public:
    // THUOC TINH PUBLIC = DAC DIEM cua den
    string viTri;
    string mauSac;
    int doSang;
    // Constructor - khoi tao den voi thong tin co ban
    DenLED(string vt, string ms) {
        viTri = vt;
        mauSac = ms;
        doSang = 0; // mac dinh den tat (do sang = 0)
        cout << "Vi tri: " << viTri << endl;
        cout << "Mau sac: " << mauSac << endl;
        cout << "Trang thai: Tat (do sang: " << doSang << "%)" << endl;
        cout << "=============================" << endl << endl;
    }
    // PHUONG THUC PUBLIC = HANH DONG ma den co the thuc hien

    // Bat den
    void batDen() {
        if (doSang == 0) {
            doSang = 50; // Bat voi do sang mac dinh 50%
            cout << "DA BAT den " << mauSac << " tai " << viTri << endl;
            cout << "   Do sang hien tai: " << doSang << "%" << endl;
        } else {
            cout << "Den " << mauSac << " tai " << viTri << " da duoc bat roi!" << endl;
            cout << "   Do sang hien tai: " << doSang << "%" << endl;
        }
        cout << endl;
    }
    // Tat den
    void tatDen() {
        if (doSang > 0) {
            doSang = 0;
            cout << "DA TAT den " << mauSac << " tai " << viTri << endl;
            cout << "   Do sang hien tai: " << doSang << "%" << endl;
        } else {
            cout << "Den " << mauSac << " tai " << viTri << " da tat roi!" << endl;
        }
        cout << endl;
    }

    // Tang do sang them 10%
    void tangDoSang() {
        if (doSang == 0) {
            cout << "Khong the tang do sang! Den " << mauSac << " tai " << viTri << " dang tat." << endl;
            cout << "   Hay bat den truoc!" << endl;
        } else if (doSang >= 100) {
            cout << "Den " << mauSac << " tai " << viTri << " da o do sang toi da (100%)!" << endl;
        } else {
            doSang += 10;
            if (doSang > 100) doSang = 100; // Gioi han toi da 100%
            cout << "Da TANG do sang den " << mauSac << " tai " << viTri << endl;
            cout << "   Do sang hien tai: " << doSang << "%" << endl;
        }
        cout << endl;
    }

    // Giam do sang di 10%
    void giamDoSang() {
        if (doSang == 0) {
            cout << "Khong the giam do sang! Den " << mauSac << " tai " << viTri << " dang tat." << endl;
        } else if (doSang <= 10) {
            doSang = 0; // Tu dong tat khi do sang <= 10%
            cout << "Den " << mauSac << " tai " << viTri << " da TU DONG TAT (do sang qua thap)" << endl;
            cout << "   Do sang hien tai: " << doSang << "%" << endl;
        } else {
            doSang -= 10;
            cout << "Da GIAM do sang den " << mauSac << " tai " << viTri << endl;
            cout << "   Do sang hien tai: " << doSang << "%" << endl;
        }
        cout << endl;
    }

    // Phuong thuc hien thi trang thai den
    void hienThiTrangThai() {
        cout << "--- TRANG THAI DEN ---" << endl;
        cout << "Vi tri: " << viTri << endl;
        cout << "Mau sac: " << mauSac << endl;
        cout << "Do sang: " << doSang << "%" << endl;
        cout << "Trang thai: " << (doSang > 0 ? "Bat" : "Tat") << endl;
        cout << "---------------------" << endl << endl;
    }
};

// Ham main de demo he thong
int main() {
    cout << "HE THONG DIEU KHIEN DEN LED THONG MINH" << endl;
    cout << "=======================================" << endl << endl;

    // OBJECT = SAN PHAM THUC te duoc tao tu class DenLED

    // Tao den cho phong khach
    cout << "Tao den phong khach..." << endl;
    DenLED denPhongKhach("Phong khach", "Trang am");

    // Tao den cho phong ngu
    cout << "Tao den phong ngu..." << endl;
    DenLED denPhongNgu("Phong ngu", "Vang");

    // Demo dieu khien den phong khach
    cout << "DEMO DIEU KHIEN DEN PHONG KHACH:" << endl;
    cout << "================================" << endl;
    denPhongKhach.batDen();
    denPhongKhach.tangDoSang();
    denPhongKhach.tangDoSang();
    denPhongKhach.tangDoSang();
    denPhongKhach.hienThiTrangThai();

    // Demo dieu khien den phong ngu
    cout << "DEMO DIEU KHIEN DEN PHONG NGU:" << endl;
    cout << "==============================" << endl;
    denPhongNgu.batDen();
    denPhongNgu.giamDoSang();
    denPhongNgu.giamDoSang();
    denPhongNgu.giamDoSang();
    denPhongNgu.giamDoSang();
    denPhongNgu.giamDoSang(); // Se tu dong tat
    denPhongNgu.hienThiTrangThai();

    // Demo them tinh nang
    cout << "DEMO THEM TINH NANG:" << endl;
    cout << "===================" << endl;
    denPhongKhach.tangDoSang(); // Thu tang khi da max
    denPhongNgu.tangDoSang();   // Thu tang khi den tat
    denPhongKhach.tatDen();
    denPhongKhach.tatDen();     // Thu tat khi da tat

    return 0;
}