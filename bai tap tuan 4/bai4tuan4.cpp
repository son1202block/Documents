#include <iostream>
#include <iomanip>
using namespace std;

class Date {
private:
    int day;
    int month;
    int year;
    
    // Mảng tên tháng
    string monthNames[12] = {
        "Tháng 1", "Tháng 2", "Tháng 3", "Tháng 4", 
        "Tháng 5", "Tháng 6", "Tháng 7", "Tháng 8",
        "Tháng 9", "Tháng 10", "Tháng 11", "Tháng 12"
    };
    
    // Mảng tên thứ
    string dayNames[7] = {
        "Chủ nhật", "Thứ hai", "Thứ ba", "Thứ tư",
        "Thứ năm", "Thứ sáu", "Thứ bảy"
    };

public:
    // Constructor
    Date(int d, int m, int y) {
        day = d;
        month = m;
        year = y;
    }
    
    // Kiểm tra năm nhuận
    bool isLeapYear(int y) {
        return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
    }
    
    // Kiểm tra tính hợp lệ của ngày
    bool isValidDate() {
        if (year < 1 || month < 1 || month > 12 || day < 1) {
            return false;
        }
        
        int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        
        // Kiểm tra năm nhuận cho tháng 2
        if (month == 2 && isLeapYear(year)) {
            daysInMonth[1] = 29;
        }
        
        return day <= daysInMonth[month - 1];
    }
    
    // Tính thứ trong tuần sử dụng công thức Zeller's Congruence
    string getDayOfWeek() {
        int d = day;
        int m = month;
        int y = year;
        
        // Công thức Zeller yêu cầu tháng 1,2 được tính là tháng 13,14 của năm trước
        if (m < 3) {
            m += 12;
            y--;
        }
        
        // Công thức Zeller's Congruence
        int k = y % 100;
        int j = y / 100;
        
        int h = (d + ((13 * (m + 1)) / 5) + k + (k / 4) + (j / 4) - 2 * j) % 7;
        
        // Chuyển đổi từ Zeller (0=Saturday) sang định dạng thông thường (0=Sunday)
        int dayIndex = (h + 5) % 7;
        
        return dayNames[dayIndex];
    }
    
    // Phương thức xuất thông tin ngày
    void displayDate() {
        cout << "Ngày: " << day << "/" << month << "/" << year << endl;
        cout << "Tháng: " << monthNames[month - 1] << endl;
        cout << "Năm: " << year << endl;
        cout << "Thứ: " << getDayOfWeek() << endl;
    }
    
    // Getter methods
    int getDay() { return day; }
    int getMonth() { return month; }
    int getYear() { return year; }
};

int main() {
    int day, month, year;
    
    cout << "=== CHƯƠNG TRÌNH QUẢN LÝ NGÀY THÁNG NĂM ===" << endl;
    cout << "Nhập ngày: ";
    cin >> day;
    cout << "Nhập tháng: ";
    cin >> month;
    cout << "Nhập năm: ";
    cin >> year;
    
    // Tạo đối tượng Date
    Date date(day, month, year);
    
    // Kiểm tra tính hợp lệ
    if (!date.isValidDate()) {
        cout << "Lỗi: Ngày tháng năm không hợp lệ!" << endl;
        cout << "Vui lòng kiểm tra lại:" << endl;
        cout << "- Ngày phải từ 1-31 (tùy thuộc vào tháng)" << endl;
        cout << "- Tháng phải từ 1-12" << endl;
        cout << "- Năm phải là số dương" << endl;
        return 1;
    }
    
    cout << "\n=== THÔNG TIN NGÀY THÁNG ===" << endl;
    date.displayDate();
    
    // Thông tin bổ sung
    cout << "\n=== THÔNG TIN BỔ SUNG ===" << endl;
    if (date.isLeapYear(year)) {
        cout << "Năm " << year << " là năm nhuận" << endl;
    } else {
        cout << "Năm " << year << " không phải là năm nhuận" << endl;
    }
    
    return 0;
}