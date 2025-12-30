#include <iostream>
using namespace std;

struct PhanSo {
    int tu, mau;
};

// ham nhap 1 phan so 
void nhapPhanSo(PhanSo &ps, int soThuTu) {
    cout << "nhap phan so " << soThuTu << " (tu mau): ";
    cin >> ps.tu >> ps.mau;
    while (ps.mau == 0) {
        cout << "Mau so phai khac 0. Nhap lai: ";
        cin >> ps.tu >> ps.mau;
    }
}

// ham so sanh phan so (tra ve true neu ps1 > ps2)
bool lonHon(PhanSo ps1, PhanSo ps2)  {
    // so sanh cheo: ps1.tu/ps1.mau > ps2.tu/ps2.mau
    return (ps1.tu * ps2.mau > ps2.tu * ps1.mau);
}

int main() {
    PhanSo ps1, ps2;

    nhapPhanSo(ps1, 1);
    nhapPhanSo(ps2, 2);

    cout << "\n--- Ket qua ---\n";
    if (lonHon(ps1, ps2)) {
        cout << "Phan so lon nhat la: " << ps1.tu << "/" << ps1.mau << endl;
    } else if (lonHon(ps2, ps1)) {
        cout << "Phan so lon nhat la: " << ps2.tu << "/" << ps2.mau << endl;
    } else {
        cout << "Hai phan so bang nhau!\n";
    }

    return 0;
}