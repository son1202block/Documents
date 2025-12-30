#include <iostream>
using namespace std;

//ham kiem tra nam nhuan
bool namNhuan(int nam) {
    return (nam % 4 == 0 && nam % 100 != 0) || (nam % 400 == 0);
}

//so ngay trong thang
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

// tinh so ngay tu 1/1/1979 den ngay cho truoc
long demSoNgay(int ngay, int thang, int nam) {
    long soNgay = 0;
    for (int i = 1979; i < nam; i++) {
        soNgay += namNhuan(i) ? 366 : 365;
    }
    for (int i = 1; i < thang; i++) {
        soNgay += soNgayTrongThang(i, nam);
    }
    return soNgay + ngay - 1;
}

int main() {
    int ngay, thang, nam;
    
    cout << "Nhap ngay: ";
    cin >> ngay;
    cout << "Nhap thang: ";
    cin >> thang;
    cout << "Nhap nam: ";
    cin >> nam;
    
    if (thang < 1 || thang > 12 || ngay < 1 || ngay > soNgayTrongThang(thang, nam)) {
        cout << "Ngay thang khong hop le" << endl;
        return 0;
    }
    
    long soNgay = demSoNgay(ngay, thang, nam);
    int thu = (soNgay + 4) % 7;
    
    cout << "Ngay " << ngay << "/" << thang << "/" << nam << " la thu " << thu << endl;
    
    return 0;
}