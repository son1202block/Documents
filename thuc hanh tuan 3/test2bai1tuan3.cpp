#include <iostream> 
using namespace std;
 
class robot {
    private:
    int x;
    int y;
    
public:
 robot(int startX=0, int startY=0) {
    x = startX;
    y = startY;
 }

 void diLen() {y++; cout << "Robot di len. Vi tri moi la: " << x << "," << y << endl; }
 void diXuong() {y--; cout << "Robot di xuong. Vi tri moi la: " << x << "," << y << endl; }
 void diSangPhai() {x++; cout << "Robot di sang phai. Vi tri moi la: " << x << "," << y << endl; }
 void diSangTrai() {x--; cout << "Robot di sang trai. Vi tri moi la: " << x << "," << y << endl; }
 void hienThiViTri() {cout << "Robot dang o vi tri: " << x << "," << y << endl; }
 void diChuyenToiViTri(int dichX, int dichY) {
    while (x < dichX) diSangPhai();
    while (x > dichX) diSangTrai();
    while (y < dichY) diLen();
    while (y > dichY) diXuong();
    
    cout << "Da den vi tri dich!\n";
 }
};

int main() {
    robot r(0, 0); 
    r.hienThiViTri();

    int targetX, targetY;
    cout << " Nhap vi tri dich (x; y): ";
    cin >> targetX >> targetY;

    r.diChuyenToiViTri(targetX, targetY);
    r.hienThiViTri();

    return 0;
}