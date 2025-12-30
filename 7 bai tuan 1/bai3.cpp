#include <iostream> 
using namespace std;

struct PhanSo {
    int tu;
    int mau;
};

int UCLN(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
 void rutGon(PhanSo &ps) {
    int ucln = UCLN(ps.tu, ps.mau);
    ps.tu /= ucln;
    ps.mau /= ucln;
    if (ps.mau < 0) {
        ps.tu = -ps.tu;
        ps.mau = -ps.mau;
    }
 }
 
 void nhap(PhanSo &ps) {
    cout << "nhap tu so: ";
    cin >> ps.tu;
    cout << "nhap mau so: ";
    cin >> ps.mau;
 }

 PhanSo cong(PhanSo ps1, PhanSo ps2) {
    PhanSo kq;
    kq.tu = ps1.tu * ps2.mau + ps1.mau * ps2.tu;
    kq.mau = ps1.mau * ps2.mau;
    rutGon(kq);
    return kq;
}

PhanSo tru(PhanSo ps1, PhanSo ps2) {
    PhanSo kq;
    kq.tu = ps1.tu * ps2.mau - ps1.mau * ps2.tu;
    kq.mau = ps1.mau * ps2.mau;
    rutGon(kq);
    return kq;
}

PhanSo nhan(PhanSo ps1, PhanSo ps2) {
    PhanSo kq;
    kq.tu = ps1.tu * ps2.tu;
    kq.mau = ps1.mau * ps2.mau;
    rutGon(kq);
    return kq;
}
PhanSo chia(PhanSo ps1, PhanSo ps2) {
    PhanSo kq;
    kq.tu = ps1.tu * ps2.mau;
    kq.mau = ps1.mau * ps2.tu;
    rutGon(kq);
    return kq; 
}

void xuat(PhanSo ps) {
    if (ps.mau == 1) {
        cout << ps.tu << endl;
    } else {
        cout << ps.tu << "/" << ps.mau << endl;
    }
}

int main() {
    PhanSo ps1, ps2;
    nhap(ps1);
    nhap(ps2);
    cout << "Phan so 1: ";
    xuat(ps1);
    cout << "Phan so 2: ";
    xuat(ps2);
    cout << "Tong: ";
    xuat(cong(ps1, ps2));
    cout << "Hieu: ";
    xuat(tru(ps1, ps2));
    cout << "Tich: ";
    xuat(nhan(ps1, ps2));
    cout << "Thuong: ";
    xuat(chia(ps1, ps2));
    
    
    return 0;
}