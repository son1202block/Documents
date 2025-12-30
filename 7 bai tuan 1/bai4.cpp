#include <iostream>
using namespace std;

struct SoPhuc {
    int thuc;
    int ao;
};

void nhap(SoPhuc &a) {
    cout << "nhap phan thuc: ";
    cin >> a.thuc;
    cout << "nhap phan ao: ";
    cin >> a.ao;
}

SoPhuc cong(SoPhuc a, SoPhuc b) {
    SoPhuc c;
    c.thuc = a.thuc + b.thuc;
    c.ao = a.ao + b.ao;
    return c;
}
SoPhuc tru(SoPhuc a, SoPhuc b) {
    SoPhuc c;
    c.thuc = a.thuc - b.thuc;
    c.ao = a.ao - b.ao;
    return c;
}
SoPhuc nhan(SoPhuc a, SoPhuc b) {
    SoPhuc c;
    c.thuc = a.thuc * b.thuc - a.ao * b.ao;
    c.ao = a.thuc * b.ao + a.ao * b.thuc;
    return c;
}

void xuat(SoPhuc a) {
    if (a.ao >= 0) {
        cout << a.thuc << " + " << a.ao << "i" << endl;
    } else {
        cout << a.thuc << " - " << -a.ao << "i" << endl;
    }
}

int main() {
    SoPhuc a, b;
    cout << "Nhap so phuc thu nhat:" << endl;
    nhap(a);
    cout << "Nhap so phuc thu hai:" << endl;
    nhap(b);
    
    cout << "\nSo phuc thu nhat: ";
    xuat(a);
    cout << "So phuc thu hai: ";
    xuat(b);
    
    cout << "\nTong hai so phuc: ";
    xuat(cong(a, b));
    
    cout << "Hieu hai so phuc: ";
    xuat(tru(a, b));
    
    cout << "Tich hai so phuc: ";
    xuat(nhan(a, b));
    
    return 0;
}