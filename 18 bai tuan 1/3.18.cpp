#include <iostream>
#include <cstdlib>
using namespace std;

struct PhanSo {
    int tu;
    int mau;
};

int UCLN(int a, int b) {
    a = abs(a);
    b = abs(b);
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// ham rut gon phan so
void rutGon(PhanSo &ps) {
    int ucln = UCLN(ps.tu, ps.mau);
    ps.tu /= ucln;
    ps.mau /= ucln;
    if (ps.mau < 0) {
        ps.tu = -ps.tu;
        ps.mau = -ps.mau;
    }
}

// ham cong hai phan so
PhanSo cong(PhanSo a, PhanSo b) {
    PhanSo c;
    c.tu = a.tu * b.mau + b.tu * a.mau;
    c.mau = a.mau * b.mau;
    rutGon(c);
    return c;
}

// ham tru hai phan so 
PhanSo tru(PhanSo a, PhanSo b) {
    PhanSo c;
    c.tu = a.tu * b.mau - b.tu * a.mau;
    c.mau = a.mau * b.mau;
    rutGon(c);
    return c;
}

// ham nhan hai phan so
PhanSo nhan(PhanSo a, PhanSo b) {
    PhanSo c;
    c.tu = a.tu * b.tu;
    c.mau = a.mau * b.mau;
    rutGon(c);
    return c;
}

// ham chia hai phan so
PhanSo chia(PhanSo a, PhanSo b) {
    PhanSo c;
    c.tu = a.tu * b.mau;
    c.mau = a.mau * b.tu;
    rutGon(c);
    return c;
}

// ham nhap phan so
void nhapPhanSo(PhanSo &ps) {
    cout << "Nhap tu so: ";
    cin >> ps.tu; 
    cout << "Nhap mau so: ";
    cin >> ps.mau;
}

// ham in phan so
void inPhanSo(PhanSo ps) {
    cout << ps.tu << "/" << ps.mau;
}

int main() {
    PhanSo a, b;
    
    cout << "Nhap phan so thu nhat:\n";
    nhapPhanSo(a);
    
    cout << "Nhap phan so thu hai:\n";
    nhapPhanSo(b);
    
    cout << "Tong: ";
    inPhanSo(cong(a,b));
    cout << endl;
    
    cout << "Hieu: ";
    inPhanSo(tru(a,b));
    cout << endl;
    
    cout << "Tich: ";
    inPhanSo(nhan(a,b));
    cout << endl;
    
    cout << "Thuong: ";
    inPhanSo(chia(a,b));
    cout << endl;
    
    return 0;
}