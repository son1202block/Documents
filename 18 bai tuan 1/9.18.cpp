#include <iostream>
#include <string>
using namespace std;

int main() {
    string hoTen;
    float toan, van, diemTB;
    
    cout << "Nhap ho ten hoc sinh: ";
    getline(cin, hoTen);
    
    cout << "Nhap diem toan: ";
    cin >> toan;
    
    cout << "Nhap diem van: ";
    cin >> van;
    
    diemTB = (toan + van) / 2;
    
    cout << "Ho ten: " << hoTen << endl;
    cout << "Diem trung binh: " << diemTB << endl;
    
    return 0;
}
 