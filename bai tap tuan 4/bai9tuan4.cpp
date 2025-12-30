#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>

class Student {
private:
    std::string name;
    std::string studentId;
    double gpa;

public:
    // Constructor mặc định
    Student() {
        name = "";
        studentId = "";
        gpa = 0.0;
    }

    // Constructor có đối số
    Student(const std::string& n, const std::string& id, double g) {
        name = n;
        studentId = id;
        gpa = g;
    }

    // Phương thức nhập thông tin sinh viên
    void input() {
        std::cout << "Nhập tên sinh viên: ";
        std::cin.ignore(); // Xóa ký tự newline còn lại
        std::getline(std::cin, name);
        
        std::cout << "Nhập mã sinh viên: ";
        std::getline(std::cin, studentId);
        
        std::cout << "Nhập điểm trung bình: ";
        std::cin >> gpa;
        
        // Kiểm tra tính hợp lệ của GPA
        while (gpa < 0.0 || gpa > 10.0) {
            std::cout << "GPA phải từ 0.0 đến 10.0. Nhập lại: ";
            std::cin >> gpa;
        }
    }

    // Phương thức xuất thông tin sinh viên
    void output() const {
        std::cout << std::left << std::setw(8) << studentId 
                  << "| " << std::setw(20) << name 
                  << "| GPA: " << std::fixed << std::setprecision(2) << gpa;
    }

    // Getter methods
    std::string getName() const {
        return name;
    }

    std::string getStudentId() const {
        return studentId;
    }

    double getGpa() const {
        return gpa;
    }

    // Setter methods
    void setName(const std::string& n) {
        name = n;
    }

    void setStudentId(const std::string& id) {
        studentId = id;
    }

    void setGpa(double g) {
        if (g >= 0.0 && g <= 10.0) {
            gpa = g;
        }
    }

    // Phương thức so sánh để sắp xếp
    bool operator<(const Student& other) const {
        return gpa < other.gpa;
    }

    // Phương thức kiểm tra xếp loại học lực
    std::string getGrade() const {
        if (gpa >= 9.0) return "Xuất sắc";
        else if (gpa >= 8.0) return "Giỏi";
        else if (gpa >= 6.5) return "Khá";
        else if (gpa >= 5.0) return "Trung bình";
        else return "Yếu";
    }
};

// Hàm xuất tiêu đề bảng
void printHeader() {
    std::cout << std::string(55, '-') << std::endl;
    std::cout << std::left << std::setw(8) << "Mã SV" 
              << "| " << std::setw(20) << "Tên sinh viên" 
              << "| " << std::setw(8) << "GPA" 
              << "| Xếp loại" << std::endl;
    std::cout << std::string(55, '-') << std::endl;
}

// Hàm xuất danh sách sinh viên
void printStudentList(Student students[], int n, const std::string& title) {
    std::cout << "\n" << title << std::endl;
    printHeader();
    
    for (int i = 0; i < n; i++) {
        students[i].output();
        std::cout << " | " << students[i].getGrade() << std::endl;
    }
    std::cout << std::string(55, '-') << std::endl;
    std::cout << "Tổng số sinh viên: " << n << std::endl;
}

// Hàm tìm điểm trung bình cao nhất
double findMaxGpa(Student students[], int n) {
    if (n == 0) return 0.0;
    
    double maxGpa = students[0].getGpa();
    for (int i = 1; i < n; i++) {
        if (students[i].getGpa() > maxGpa) {
            maxGpa = students[i].getGpa();
        }
    }
    return maxGpa;
}

// Hàm tìm sinh viên theo tên
int findStudentByName(Student students[], int n, const std::string& searchName) {
    for (int i = 0; i < n; i++) {
        if (students[i].getName() == searchName) {
            return i;
        }
    }
    return -1; // Không tìm thấy
}

// Hàm sắp xếp sinh viên theo GPA tăng dần (Bubble Sort)
void sortStudentsByGpa(Student students[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (students[j].getGpa() > students[j + 1].getGpa()) {
                std::swap(students[j], students[j + 1]);
            }
        }
    }
}

// Hàm xóa sinh viên theo mã số
int removeStudentById(Student students[], int n, const std::string& removeId) {
    int removeIndex = -1;
    
    // Tìm vị trí sinh viên cần xóa
    for (int i = 0; i < n; i++) {
        if (students[i].getStudentId() == removeId) {
            removeIndex = i;
            break;
        }
    }
    
    if (removeIndex == -1) {
        return n; // Không tìm thấy, không xóa
    }
    
    // Dịch chuyển các phần tử sau lên trước
    for (int i = removeIndex; i < n - 1; i++) {
        students[i] = students[i + 1];
    }
    
    return n - 1; // Trả về kích thước mới
}

// Hàm thống kê xếp loại học lực
void statisticsGrade(Student students[], int n) {
    int excellent = 0, good = 0, fair = 0, average = 0, poor = 0;
    
    for (int i = 0; i < n; i++) {
        double gpa = students[i].getGpa();
        if (gpa >= 9.0) excellent++;
        else if (gpa >= 8.0) good++;
        else if (gpa >= 6.5) fair++;
        else if (gpa >= 5.0) average++;
        else poor++;
    }
    
    std::cout << "\n=== THỐNG KÊ XẾP LOẠI HỌC LỰC ===" << std::endl;
    std::cout << "Xuất sắc (>= 9.0): " << excellent << " sinh viên" << std::endl;
    std::cout << "Giỏi (>= 8.0):     " << good << " sinh viên" << std::endl;
    std::cout << "Khá (>= 6.5):      " << fair << " sinh viên" << std::endl;
    std::cout << "Trung bình (>= 5.0): " << average << " sinh viên" << std::endl;
    std::cout << "Yếu (< 5.0):       " << poor << " sinh viên" << std::endl;
}

int main() {
    const int MAX_STUDENTS = 100;
    Student students[MAX_STUDENTS];
    int n;

    std::cout << "=== CHƯƠNG TRÌNH QUẢN LÝ SINH VIÊN ===" << std::endl;
    
    // Nhập số sinh viên
    std::cout << "Nhập số sinh viên trong lớp: ";
    std::cin >> n;
    
    while (n <= 0 || n > MAX_STUDENTS) {
        std::cout << "Số sinh viên phải từ 1 đến " << MAX_STUDENTS << ". Nhập lại: ";
        std::cin >> n;
    }

    // Nhập thông tin các sinh viên
    std::cout << "\n=== NHẬP THÔNG TIN SINH VIÊN ===" << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << "\nSinh viên thứ " << (i + 1) << ":" << std::endl;
        students[i].input();
    }

    // Xuất danh sách ban đầu
    printStudentList(students, n, "=== DANH SÁCH SINH VIÊN LỚP HỌC ===");

    // Tìm điểm trung bình cao nhất
    std::cout << "\n=== ĐIỂM TRUNG BÌNH CAO NHẤT ===" << std::endl;
    double maxGpa = findMaxGpa(students, n);
    std::cout << "Điểm trung bình cao nhất trong lớp: " << std::fixed 
              << std::setprecision(2) << maxGpa << std::endl;
    
    std::cout << "Các sinh viên có GPA cao nhất:" << std::endl;
    printHeader();
    for (int i = 0; i < n; i++) {
        if (students[i].getGpa() == maxGpa) {
            students[i].output();
            std::cout << " | " << students[i].getGrade() << std::endl;
        }
    }

    // Tìm sinh viên theo tên
    std::cout << "\n=== TÌM SINH VIÊN THEO TÊN ===" << std::endl;
    std::string searchName;
    std::cout << "Nhập tên sinh viên cần tìm: ";
    std::cin.ignore();
    std::getline(std::cin, searchName);
    
    int foundIndex = findStudentByName(students, n, searchName);
    if (foundIndex != -1) {
        std::cout << "Tìm thấy sinh viên:" << std::endl;
        printHeader();
        students[foundIndex].output();
        std::cout << " | " << students[foundIndex].getGrade() << std::endl;
    } else {
        std::cout << "Không tìm thấy sinh viên có tên: " << searchName << std::endl;
    }

    // Sắp xếp danh sách theo GPA
    std::cout << "\n=== SẮP XẾP THEO ĐIỂM TRUNG BÌNH ===" << std::endl;
    sortStudentsByGpa(students, n);
    printStudentList(students, n, "Danh sách sinh viên sau khi sắp xếp theo GPA tăng dần:");

    // Thống kê xếp loại
    statisticsGrade(students, n);

    // Xóa sinh viên theo mã số
    std::cout << "\n=== XÓA SINH VIÊN THEO MÃ SỐ ===" << std::endl;
    std::string removeId;
    std::cout << "Nhập mã số sinh viên cần xóa: ";
    std::cin >> removeId;
    
    int oldSize = n;
    n = removeStudentById(students, n, removeId);
    
    if (n < oldSize) {
        std::cout << "Đã xóa sinh viên có mã số: " << removeId << std::endl;
        if (n > 0) {
            printStudentList(students, n, "Danh sách sinh viên sau khi xóa:");
        } else {
            std::cout << "Danh sách trống sau khi xóa." << std::endl;
        }
    } else {
        std::cout << "Không tìm thấy sinh viên có mã số: " << removeId << std::endl;
    }

    // Thống kê cuối cùng
    if (n > 0) {
        std::cout << "\n=== THỐNG KÊ CUỐI CÙNG ===" << std::endl;
        std::cout << "Tổng số sinh viên còn lại: " << n << std::endl;
        std::cout << "GPA trung bình của lớp: " << std::fixed << std::setprecision(2);
        
        double totalGpa = 0;
        for (int i = 0; i < n; i++) {
            totalGpa += students[i].getGpa();
        }
        std::cout << (totalGpa / n) << std::endl;
        
        statisticsGrade(students, n);
    }

    std::cout << "\nCảm ơn bạn đã sử dụng chương trình!" << std::endl;
    return 0;
}