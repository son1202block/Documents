#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

struct diem {
    double a;   // hoanh do
    double b;   // tung do
};

double khoang_cach(diem A, diem B) {
    return sqrt(pow(A.a - B.a, 2) + pow(A.b - B.b, 2)); 
}

int main () {
    diem A, B;
    cout << "nhap toa do diem A: ";
    cin >> A.a >> A.b;
    cout << "nhap toa do diem B: ";
    cin >> B.a >> B.b;
    cout << fixed << setprecision(2) << "khoang cach giua 2 diem A va B la: " << khoang_cach(A, B) << endl;

    return 0;
}