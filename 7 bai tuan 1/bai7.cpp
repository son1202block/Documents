#include <iostream>
#include <cmath>

using namespace std;

int main() {
    float x, y, r;
    cout << "Nhap toa do tam duong tron (x,y): ";
    cin >> x >> y;
    cout << "Nhap ban kinh r: ";
    cin >> r;

    if (r <= 0) {
        cout << "Ban kinh phai lon hon 0." << endl;
        return 0;
    }

    float chuVi = 2 * M_PI * r;
    float dienTich = M_PI * r * r;

    cout << "Chu vi duong tron: " << chuVi << endl;
    cout << "Dien tich duong tron: " << dienTich << endl;

    return 0;
}   