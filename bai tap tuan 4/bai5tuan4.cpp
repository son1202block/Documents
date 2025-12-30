#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

class ComplexNumber {
private:
    double real;      // Phần thực (a1, b1)
    double imaginary; // Phần ảo (a2, b2)

public:
    // Constructor
    ComplexNumber(double r = 0, double i = 0) {
        real = r;
        imaginary = i;
    }
    
    // Getter methods
    double getReal() const { return real; }
    double getImaginary() const { return imaginary; }
    
    // Setter methods
    void setReal(double r) { real = r; }
    void setImaginary(double i) { imaginary = i; }
    
    // Phương thức nhập số phức
    void input() {
        cout << "Nhập phần thực: ";
        cin >> real;
        cout << "Nhập phần ảo: ";
        cin >> imaginary;
    }
    
    // Phương thức xuất số phức
    void output() const {
        cout << fixed << setprecision(2);
        if (imaginary >= 0) {
            cout << real << " + " << imaginary << "i";
        } else {
            cout << real << " - " << abs(imaginary) << "i";
        }
    }
    
    // Phép cộng: A + B = (a1+b1, a2+b2)
    ComplexNumber add(const ComplexNumber& other) const {
        return ComplexNumber(real + other.real, imaginary + other.imaginary);
    }
    
    // Phép trừ: A - B = (a1-b1, a2-b2)
    ComplexNumber subtract(const ComplexNumber& other) const {
        return ComplexNumber(real - other.real, imaginary - other.imaginary);
    }
    
    // Phép nhân: A * B = (a1*b1 - a2*b2, a1*b2 + a2*b1)
    ComplexNumber multiply(const ComplexNumber& other) const {
        double newReal = real * other.real - imaginary * other.imaginary;
        double newImaginary = real * other.imaginary + imaginary * other.real;
        return ComplexNumber(newReal, newImaginary);
    }
    
    // Phép chia: A / B = ((a1*b1 + a2*b2)/(b1² + b2²), (b1*a2 - a1*b2)/(b1² + b2²))
    ComplexNumber divide(const ComplexNumber& other) const {
        double denominator = other.real * other.real + other.imaginary * other.imaginary;
        
        if (denominator == 0) {
            cout << "Lỗi: Không thể chia cho số phức 0!" << endl;
            return ComplexNumber(0, 0);
        }
        
        double newReal = (real * other.real + imaginary * other.imaginary) / denominator;
        double newImaginary = (other.real * imaginary - real * other.imaginary) / denominator;
        return ComplexNumber(newReal, newImaginary);
    }
    
    // Tính module (độ lớn) của số phức
    double getModule() const {
        return sqrt(real * real + imaginary * imaginary);
    }
    
    // Tính số phức liên hợp
    ComplexNumber getConjugate() const {
        return ComplexNumber(real, -imaginary);
    }
    
    // Kiểm tra số phức có bằng 0 không
    bool isZero() const {
        return (real == 0 && imaginary == 0);
    }
};

// Hàm hiển thị menu
void showMenu() {
    cout << "\n=== MENU CHƯƠNG TRÌNH SỐ PHỨC ===" << endl;
    cout << "1. Cộng hai số phức (A + B)" << endl;
    cout << "2. Trừ hai số phức (A - B)" << endl;
    cout << "3. Nhân hai số phức (A * B)" << endl;
    cout << "4. Chia hai số phức (A / B)" << endl;
    cout << "5. Tính module của số phức" << endl;
    cout << "6. Tính số phức liên hợp" << endl;
    cout << "7. Nhập lại hai số phức" << endl;
    cout << "0. Thoát chương trình" << endl;
    cout << "Chọn chức năng: ";
}

int main() {
    ComplexNumber A, B, result;
    int choice;
    
    cout << "=== CHƯƠNG TRÌNH QUẢN LÝ SỐ PHỨC ===" << endl;
    
    // Nhập hai số phức ban đầu
    cout << "\n--- NHẬP SỐ PHỨC A ---" << endl;
    A.input();
    
    cout << "\n--- NHẬP SỐ PHỨC B ---" << endl;
    B.input();
    
    do {
        cout << "\n--- THÔNG TIN HIỆN TẠI ---" << endl;
        cout << "Số phức A: ";
        A.output();
        cout << "\nSố phức B: ";
        B.output();
        cout << endl;
        
        showMenu();
        cin >> choice;
        
        switch(choice) {
            case 1: // Cộng
                result = A.add(B);
                cout << "\nKết quả A + B = ";
                result.output();
                cout << endl;
                break;
                
            case 2: // Trừ
                result = A.subtract(B);
                cout << "\nKết quả A - B = ";
                result.output();
                cout << endl;
                break;
                
            case 3: // Nhân
                result = A.multiply(B);
                cout << "\nKết quả A * B = ";
                result.output();
                cout << endl;
                break;
                
            case 4: // Chia
                if (B.isZero()) {
                    cout << "\nLỗi: Không thể chia cho số phức 0!" << endl;
                } else {
                    result = A.divide(B);
                    cout << "\nKết quả A / B = ";
                    result.output();
                    cout << endl;
                }
                break;
                
            case 5: // Module
                cout << "\nModule của số phức A: |A| = " 
                     << fixed << setprecision(2) << A.getModule() << endl;
                cout << "Module của số phức B: |B| = " 
                     << fixed << setprecision(2) << B.getModule() << endl;
                break;
                
            case 6: // Số phức liên hợp
                result = A.getConjugate();
                cout << "\nSố phức liên hợp của A: ";
                result.output();
                
                result = B.getConjugate();
                cout << "\nSố phức liên hợp của B: ";
                result.output();
                cout << endl;
                break;
                
            case 7: // Nhập lại
                cout << "\n--- NHẬP LẠI SỐ PHỨC A ---" << endl;
                A.input();
                cout << "\n--- NHẬP LẠI SỐ PHỨC B ---" << endl;
                B.input();
                break;
                
            case 0: // Thoát
                cout << "\nCảm ơn bạn đã sử dụng chương trình!" << endl;
                break;
                
            default:
                cout << "\nLựa chọn không hợp lệ! Vui lòng chọn lại." << endl;
        }
        
    } while(choice != 0);
    
    return 0;
}