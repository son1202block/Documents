#include <iostream>
using namespace std;

// Hàm trả về số ngày trong tháng
int soNgayTrongThang(int m, int y) {
    switch (m) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            // Năm nhuận
            if ((y % 400 == 0) || (y % 4 == 0 && y % 100 != 0))
                return 29;
            else
                return 28;
        default:
            return 0; // tháng không hợp lệ
    }
}

// Hàm kiểm tra ngày hợp lệ
bool hopLeNgay(int d, int m, int y) {
    if (m < 1 || m > 12) return false;
    int maxDay = soNgayTrongThang(m, y);
    if (d < 1 || d > maxDay) return false;
    return true;
}

// Hàm tính số thứ tự trong năm
int soThuTuTrongNam(int d, int m, int y) {
    int stt = d;
    for (int i = 1; i < m; i++) {
        stt += soNgayTrongThang(i, y);
    }
    return stt;
}

int main() {
    int d, m, y;
    cout << "Nhap ngay thang nam (dd mm yyyy): ";
    if (!(cin >> d >> m >> y)) {
        cout << "Nhap sai!" << endl;
        return 1;
    }

    if (!hopLeNgay(d, m, y)) {
        cout << "Ngay khong hop le!" << endl;
        return 1;
    }

    int kq = soThuTuTrongNam(d, m, y);
    cout << "Ngay " << d << "/" << m << "/" << y
         << " la ngay thu " << kq << " trong nam." << endl;

    return 0;
}
