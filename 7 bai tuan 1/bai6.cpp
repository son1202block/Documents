#include <iostream>
#include <cmath>
using namespace std;

struct Point {
    double x, y;
};

// ham nhap 1 diem
void nhapDiem(Point &p, char ten) {
    cout << "Nhap toa do diem " << ten << " (x y): ";
    cin >> p.x >> p.y;
}

// ham tinh khoang cach giua 2 diem
double khoangCach(Point P, Point Q) {
    double dx = P.x - Q.x;
    double dy = P.y - Q.y;
    return sqrt(dx * dx + dy * dy);
}

// ham tinh chu vi tam giac
double tinhChuVi(Point A, Point B, Point C) {
    double AB = khoangCach(A, B);
    double BC = khoangCach(B, C);
    double CA = khoangCach(C, A);
    return AB + BC + CA;
}

// ham tinh dien tich tam giac (dung cong thuc vector)
double tinhDienTich(Point A, Point B, Point C) {
    return 0.5 * fabs((B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x));
}

// ham tinh trong tam tam giac
Point tinhTrongTam(Point A, Point B, Point C) {
    Point G;
    G.x = (A.x + B.x + C.x) / 3.0;
    G.y = (A.y + B.y + C.y) / 3.0;
    return G;
}

int main() {
    Point A, B, C;
    nhapDiem(A, 'A');
    nhapDiem(B, 'B');
    nhapDiem(C, 'C');

    double chuVi = tinhChuVi(A, B, C);
    double dienTich = tinhDienTich(A, B, C);
    Point G = tinhTrongTam(A, B, C);

    cout << "\n--- Ket qua ---\n";
    cout << "Chu vi tam giac: " << chuVi << endl;
    cout << "Dien tich tam giac: " << dienTich << endl;
    cout << "Trong tam: (" << G.x << ", " << G.y << ")\n";

    return 0;
}
