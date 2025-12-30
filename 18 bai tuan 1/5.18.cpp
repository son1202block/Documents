#include <iostream>
using namespace std;

// ham kiem tra nam nhuan
bool namNhuan(int nam) {
    return (nam % 4 == 0 && nam % 100 != 0) || (nam % 400 == 0);
}

// ham cho biet so ngay trong thang
int soNgayTrongThang(int thang, int nam) {
    switch (thang) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            return namNhuan(nam) ? 29 : 28;
        default:
            return 0;
    }
}

// ham tim ngay ke tiep
void ngayKeTiep(int &ngay, int &thang, int &nam) {
    ngay++;
    if (ngay > soNgayTrongThang(thang, nam)) {
        ngay = 1;
        thang++;
        if (thang > 12) {
            thang = 1;
            nam++;
        }
    }
}

int main() {
    int ngay, thang, nam;
    
    cout << "Nhap ngay: ";
    cin >> ngay;
    cout << "Nhap thang: ";
    cin >> thang;
    cout << "Nhap nam: ";
    cin >> nam;
    
    // Kiem tra tinh hop le cua ngay thang
    if (thang < 1 || thang > 12 || ngay < 1 || ngay > soNgayTrongThang(thang, nam)) {
        cout << "Ngay thang khong hop le" << endl;
        return 0;
    }
    
    // Tim ngay ke tiep
    ngayKeTiep(ngay, thang, nam);
    
    // Hien thi ket qua
    cout << "Ngay ke tiep: " << ngay << "/" << thang << "/" << nam << endl;
    
    return 0;
}