#include <iostream>
#include <iomanip>
using namespace std;

class NgayThangNam {
private:
    int ngay;
    int thang;
    int nam;

public:
    // Constructor mặc định
    NgayThangNam() {
        ngay = 1;
        thang = 1;
        nam = 2000;
    }
    
    // Constructor có tham số
    NgayThangNam(int d, int m, int y) {
        ngay = d;
        thang = m;
        nam = y;
        
        // Nếu ngày không hợp lệ, đặt về mặc định
        if (!hopLe()) {
            ngay = 1;
            thang = 1;
            nam = 2000;
        }
    }
    
    // Kiểm tra năm nhuận
    bool laNamNhuan(int year) const {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }
    
    // Lấy số ngày trong tháng
    int soNgayTrongThang(int month, int year) const {
        int ngayTrongThang[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        
        if (month == 2 && laNamNhuan(year)) {
            return 29;
        }
        return ngayTrongThang[month - 1];
    }
    
    // Kiểm tra ngày tháng năm có hợp lệ không
    bool hopLe() const {
        if (nam < 1 || thang < 1 || thang > 12 || ngay < 1) {
            return false;
        }
        
        return ngay <= soNgayTrongThang(thang, nam);
    }
    
    // Nhập ngày tháng năm
    void nhapNgay() {
        do {
            cout << "Nhap ngay: ";
            cin >> ngay;
            cout << "Nhap thang: ";
            cin >> thang;
            cout << "Nhap nam: ";
            cin >> nam;
            
            if (!hopLe()) {
                cout << "Loi: Ngay thang nam khong hop le! Vui long nhap lai." << endl;
            }
        } while (!hopLe());
    }
    
    // Hiển thị ngày tháng năm
    void hienThiNgay() const {
        cout << setfill('0') << setw(2) << ngay << "/"
             << setw(2) << thang << "/"
             << nam;
    }
    
    // Tính ngày sau
    NgayThangNam ngaySau() const {
        int newNgay = ngay + 1;
        int newThang = thang;
        int newNam = nam;
        
        // Kiểm tra vượt quá số ngày trong tháng
        if (newNgay > soNgayTrongThang(thang, nam)) {
            newNgay = 1;
            newThang++;
            
            // Kiểm tra vượt quá tháng 12
            if (newThang > 12) {
                newThang = 1;
                newNam++;
            }
        }
        
        return NgayThangNam(newNgay, newThang, newNam);
    }
    
    // Tính ngày trước
    NgayThangNam ngayTruoc() const {
        int newNgay = ngay - 1;
        int newThang = thang;
        int newNam = nam;
        
        // Kiểm tra nhỏ hơn ngày 1
        if (newNgay < 1) {
            newThang--;
            
            // Kiểm tra nhỏ hơn tháng 1
            if (newThang < 1) {
                newThang = 12;
                newNam--;
                
                // Đảm bảo năm không âm
                if (newNam < 1) {
                    newNam = 1;
                }
            }
            
            newNgay = soNgayTrongThang(newThang, newNam);
        }
        
        return NgayThangNam(newNgay, newThang, newNam);
    }
    
    // Getter methods
    int getNgay() const { return ngay; }
    int getThang() const { return thang; }
    int getNam() const { return nam; }
    
    // So sánh hai ngày
    bool bang(const NgayThangNam& other) const {
        return (ngay == other.ngay && thang == other.thang && nam == other.nam);
    }
    
    // Tính khoảng cách giữa hai ngày (đơn giản)
    int khoangCach(const NgayThangNam& other) const {
        // Chỉ tính khoảng cách đơn giản trong cùng năm
        if (nam != other.nam) return -1;
        
        int ngayThu1 = 0, ngayThu2 = 0;
        
        // Tính số ngày từ đầu năm
        for (int m = 1; m < thang; m++) {
            ngayThu1 += soNgayTrongThang(m, nam);
        }
        ngayThu1 += ngay;
        
        for (int m = 1; m < other.thang; m++) {
            ngayThu2 += soNgayTrongThang(m, other.nam);
        }
        ngayThu2 += other.ngay;
        
        return abs(ngayThu2 - ngayThu1);
    }
};

int main() {
    cout << "=== CHUONG TRINH QUAN LY NGAY THANG NAM ===" << endl << endl;
    
    NgayThangNam ngay1;
    
    cout << "Nhap ngay thang nam:" << endl;
    ngay1.nhapNgay();
    
    cout << "\n=== KET QUA ===" << endl;
    cout << "Ngay hien tai: ";
    ngay1.hienThiNgay();
    cout << endl;
    
    NgayThangNam ngayTiepTheo = ngay1.ngaySau();
    cout << "Ngay sau: ";
    ngayTiepTheo.hienThiNgay();
    cout << endl;
    
    NgayThangNam ngayTruocDo = ngay1.ngayTruoc();
    cout << "Ngay truoc: ";
    ngayTruocDo.hienThiNgay();
    cout << endl;
    
    // Tính năng bổ sung: Kiểm tra năm nhuận
    cout << "\n=== THONG TIN BO SUNG ===" << endl;
    cout << "Nam " << ngay1.getNam();
    if (NgayThangNam().laNamNhuan(ngay1.getNam())) {
        cout << " la nam nhuan";
    } else {
        cout << " khong phai la nam nhuan";
    }
    cout << endl;
    
    cout << "Thang " << ngay1.getThang() << "/" << ngay1.getNam() 
         << " co " << NgayThangNam().soNgayTrongThang(ngay1.getThang(), ngay1.getNam()) 
         << " ngay" << endl;
    
    // Tính năng mở rộng: Tính nhiều ngày sau/trước
    int soNgay;
    cout << "\nBan muon tinh ngay thu may tiep theo? ";
    cin >> soNgay;
    
    NgayThangNam ngayKetQua = ngay1;
    for (int i = 0; i < soNgay; i++) {
        ngayKetQua = ngayKetQua.ngaySau();
    }
    
    cout << "Sau " << soNgay << " ngay: ";
    ngayKetQua.hienThiNgay();
    cout << endl;
    
    return 0;
}