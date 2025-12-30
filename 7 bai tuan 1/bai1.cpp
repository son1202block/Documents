#include <iostream>
#include <cstdlib>
using namespace std;

// dinh nghia struct phan so
struct PhanSo {
    int tu;
    int mau;
};

// ham tim UCLN bang thuat toan Euclid
int UCLN(int a, int b) {
    // Chuyen ve so duong de tinh UCLN
    a = abs(a);
    b = abs(b);
    
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

//ham rut gon phan so
void rutGon(PhanSo &ps) {
    // Kiem tra mau so khac 0
    if (ps.mau == 0) {
        cout << "Loi: Mau so khong the bang 0!" << endl;
        return;
    }
    
    // Neu tu so bang 0, phan so = 0
    if (ps.tu == 0) {
        ps.mau = 1;
        return;
    }
    
    int ucln = UCLN(ps.tu, ps.mau);
    ps.tu /= ucln;
    ps.mau /= ucln;
    
    // Xu ly dau cua phan so
    if (ps.mau < 0) {
        ps.tu = -ps.tu;
        ps.mau = -ps.mau;
    }
}

int main() {
    PhanSo ps;
    
    cout << "Nhap phan so:" << endl;
    cout << "Tu so: ";
    cin >> ps.tu;
    cout << "Mau so: ";
    cin >> ps.mau;
    
    // Kiem tra mau so
    if (ps.mau == 0) {
        cout << "Loi: Mau so khong the bang 0!" << endl;
        return 1;
    }
    
    cout << "Phan so ban dau: " << ps.tu << "/" << ps.mau << endl;
    
    rutGon(ps);
    
    if (ps.tu == 0) {
        cout << "Phan so sau khi rut gon: 0" << endl;
    } else {
        cout << "Phan so sau khi rut gon: " << ps.tu << "/" << ps.mau << endl;
    }
    
    return 0;
}