#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
using namespace std;

/**
 * Class CamBienNhietDo - Temperature Sensor with Getter/Setter
 * Demonstrates encapsulation, data validation in C++
 */
class CamBienNhietDo {
private:
    // PRIVATE ATTRIBUTES - Thuoc tinh rieng tu
    double nhietDo;      // Nhiet do do duoc
    double nguongCao;    // Nguong canh bao cao
    double nguongThap;   // Nguong canh bao thap
    
public:
    // CONSTRUCTOR - Ham khoi tao
    CamBienNhietDo(double cao, double thap) {
        // Kiem tra logic nguong truoc khi khoi tao
        if (cao <= thap) {
            cout << "[LOI] Nguong cao phai lon hon nguong thap!" << endl;
            this->nguongCao = 30.0;  // Gia tri mac dinh
            this->nguongThap = 10.0; // Gia tri mac dinh
            cout << "   Su dung gia tri mac dinh: cao=30C, thap=10C" << endl;
        } else {
            this->nguongCao = cao;
            this->nguongThap = thap;
        }
        this->nhietDo = 25.0;  // Nhiet do ban dau = 25C
        cout << "[OK] Cam bien duoc khoi tao voi nhiet do: " << this->nhietDo << "C" << endl;
        cout << "   Nguong: [" << this->nguongThap << "C - " << this->nguongCao << "C]" << endl;
    }
    
    // GETTER METHODS - Phuong thuc doc gia tri
    double getNhietDo() const {
        return nhietDo;
    }
    
    double getNguongCao() const {
        return nguongCao;
    }
    
    double getNguongThap() const {
        return nguongThap;
    }
    
    // SETTER METHODS - Phuong thuc thay doi gia tri co kiem tra
    void setNhietDo(double t) {
        // Validate: Kiem tra nhiet do trong khoang hop ly
        if (t <= -50 || t >= 100) {
            cout << "[LOI] Nhiet do phai trong khoang (-50, 100)C" << endl;
            cout << "   Gia tri hien tai duoc giu nguyen: " << nhietDo << "C" << endl;
        } else {
            double oldTemp = this->nhietDo;
            this->nhietDo = t;
            cout << "[CAP NHAT] Nhiet do: " << oldTemp << "C -> " << t << "C" << endl;
            // Tu dong kiem tra canh bao sau khi cap nhat
            kiemTraCanhBao();
        }
    }
    
    void setNguongCao(double cao) {
        // Validate: Nguong cao phai > nguong thap
        if (cao <= nguongThap) {
            cout << "[LOI] Nguong cao (" << cao << "C) phai lon hon nguong thap (" 
                 << nguongThap << "C)" << endl;
        } else {
            double oldValue = this->nguongCao;
            this->nguongCao = cao;
            cout << "[CAP NHAT] Nguong cao: " << oldValue << "C -> " << cao << "C" << endl;
            kiemTraCanhBao();  // Kiem tra lai sau khi thay doi nguong
        }
    }
    
    void setNguongThap(double thap) {
        // Validate: Nguong thap phai < nguong cao
        if (thap >= nguongCao) {
            cout << "[LOI] Nguong thap (" << thap << "C) phai nho hon nguong cao (" 
                 << nguongCao << "C)" << endl;
        } else {
            double oldValue = this->nguongThap;
            this->nguongThap = thap;
            cout << "[CAP NHAT] Nguong thap: " << oldValue << "C -> " << thap << "C" << endl;
            kiemTraCanhBao();  // Kiem tra lai sau khi thay doi nguong
        }
    }
    
    // BUSINESS LOGIC METHOD - Phuong thuc logic nghiep vu
    void kiemTraCanhBao() const {
        cout << "\n[KIEM TRA CANH BAO]:" << endl;
        cout << "   Nhiet do hien tai: " << nhietDo << "C" << endl;
        cout << "   Khoang an toan: [" << nguongThap << "C - " << nguongCao << "C]" << endl;
        
        if (nhietDo > nguongCao) {
            cout << "[CANH BAO] Nhiet do QUA CAO! (" << (nhietDo - nguongCao) << "C vuot nguong)" << endl;
        } else if (nhietDo < nguongThap) {
            cout << "[CANH BAO] Nhiet do QUA THAP! (" << (nguongThap - nhietDo) << "C duoi nguong)" << endl;
        } else {
            cout << "[OK] Nhiet do trong khoang AN TOAN" << endl;
        }
        cout << string(50, '-') << endl;
    }
    
    // Phuong thuc hien thi thong tin cam bien
    void hienThiThongTin() const {
        cout << "\n[THONG TIN CAM BIEN NHIET DO]:" << endl;
        cout << "   Nhiet do: " << fixed << setprecision(1) << nhietDo << "C" << endl;
        cout << "   Nguong cao: " << nguongCao << "C" << endl;
        cout << "   Nguong thap: " << nguongThap << "C" << endl;
        cout << string(40, '=') << endl;
    }
};

// DEMO FUNCTIONS - Ham demo cac chuc nang
void demoConstructor() {
    cout << "\n" << string(60, '=') << endl;
    cout << "1. DEMO CONSTRUCTOR" << endl;
    cout << string(60, '=') << endl;
    
    cout << "\n-> Tao cam bien hop le (cao=35, thap=15):" << endl;
    CamBienNhietDo sensor1(35.0, 15.0);
    
    cout << "\n-> Tao cam bien khong hop le (cao=10, thap=20):" << endl;
    CamBienNhietDo sensor2(10.0, 20.0);
}

void demoGetter(CamBienNhietDo& sensor) {
    cout << "\n" << string(60, '=') << endl;
    cout << "2. DEMO GETTER METHODS" << endl;
    cout << string(60, '=') << endl;
    
    cout << "Doc gia tri thong qua getter:" << endl;
    cout << "   getNhietDo(): " << sensor.getNhietDo() << "C" << endl;
    cout << "   getNguongCao(): " << sensor.getNguongCao() << "C" << endl;
    cout << "   getNguongThap(): " << sensor.getNguongThap() << "C" << endl;
}

void demoSetterValid(CamBienNhietDo& sensor) {
    cout << "\n" << string(60, '=') << endl;
    cout << "3. DEMO SETTER - Du lieu hop le" << endl;
    cout << string(60, '=') << endl;
    
    cout << "\n-> Cap nhat nhiet do hop le:" << endl;
    sensor.setNhietDo(22.5);
    sensor.setNhietDo(28.0);
    
    cout << "\n-> Cap nhat nguong hop le:" << endl;
    sensor.setNguongCao(40.0);
    sensor.setNguongThap(5.0);
}

void demoSetterInvalid(CamBienNhietDo& sensor) {
    cout << "\n" << string(60, '=') << endl;
    cout << "4. DEMO SETTER - Xu ly loi nhap lieu" << endl;
    cout << string(60, '=') << endl;
    
    cout << "\n-> Test nhiet do ngoai khoang cho phep:" << endl;
    sensor.setNhietDo(-60.0);  // Qua thap
    sensor.setNhietDo(120.0);  // Qua cao
    
    cout << "\n-> Test nguong khong hop le:" << endl;
    sensor.setNguongCao(3.0);  // Nho hon nguong thap
    sensor.setNguongThap(50.0); // Lon hon nguong cao
}

void demoWarningSystem(CamBienNhietDo& sensor) {
    cout << "\n" << string(60, '=') << endl;
    cout << "5. DEMO HE THONG CANH BAO" << endl;
    cout << string(60, '=') << endl;
    
    cout << "\n-> Test canh bao nhiet do cao:" << endl;
    sensor.setNhietDo(45.0);
    
    cout << "\n-> Test canh bao nhiet do thap:" << endl;
    sensor.setNhietDo(2.0);
    
    cout << "\n-> Test nhiet do an toan:" << endl;
    sensor.setNhietDo(20.0);
}

void demoInteractive(CamBienNhietDo& sensor) {
    cout << "\n" << string(60, '=') << endl;
    cout << "6. DEMO TUONG TAC NGUOI DUNG" << endl;
    cout << string(60, '=') << endl;
    
    int choice;
    double value;
    
    do {
        sensor.hienThiThongTin();
        cout << "\n[MENU CHUC NANG]:" << endl;
        cout << "   1. Cap nhat nhiet do" << endl;
        cout << "   2. Cap nhat nguong cao" << endl;
        cout << "   3. Cap nhat nguong thap" << endl;
        cout << "   4. Kiem tra canh bao" << endl;
        cout << "   0. Thoat" << endl;
        cout << "-> Nhap lua chon: ";
        cin >> choice;
        
        switch(choice) {
            case 1:
                cout << "Nhap nhiet do moi: ";
                cin >> value;
                sensor.setNhietDo(value);
                break;
            case 2:
                cout << "Nhap nguong cao moi: ";
                cin >> value;
                sensor.setNguongCao(value);
                break;
            case 3:
                cout << "Nhap nguong thap moi: ";
                cin >> value;
                sensor.setNguongThap(value);
                break;
            case 4:
                sensor.kiemTraCanhBao();
                break;
            case 0:
                cout << "Ket thuc demo!" << endl;
                break;
            default:
                cout << "[LOI] Lua chon khong hop le!" << endl;
        }
        
        if (choice != 0) {
            cout << "\nNhan Enter de tiep tuc...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
        
    } while (choice != 0);
}

// MAIN FUNCTION
int main() {
    cout << "CHUONG TRINH CAM BIEN NHIET DO VOI GETTER/SETTER" << endl;
    cout << "Minh hoa: Encapsulation, Data Validation, OOP trong C++" << endl;
    
    // 1. Demo Constructor
    demoConstructor();
    
    // Tao doi tuong cho cac demo tiep theo
    CamBienNhietDo mainSensor(30.0, 15.0);
    
    // 2. Demo Getter
    demoGetter(mainSensor);
    
    // 3. Demo Setter hop le
    demoSetterValid(mainSensor);
    
    // 4. Demo Setter xu ly loi
    demoSetterInvalid(mainSensor);
    
    // 5. Demo he thong canh bao
    demoWarningSystem(mainSensor);
    
    // 6. Demo tuong tac (tuy chon)
    char continueDemo;
    cout << "\nBan co muon thu che do tuong tac? (y/n): ";
    cin >> continueDemo;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
    if (continueDemo == 'y' || continueDemo == 'Y') {
        demoInteractive(mainSensor);
    }
    return 0;
}