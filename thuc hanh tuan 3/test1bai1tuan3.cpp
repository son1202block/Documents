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
};

int main() {
    robot myRobot(0, 0);
    myRobot.hienThiViTri();
    myRobot.diLen();
    myRobot.diXuong();
    myRobot.diSangPhai();
    myRobot.diSangTrai();
    myRobot.hienThiViTri();
    return 0;
}