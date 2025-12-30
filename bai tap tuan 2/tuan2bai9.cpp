#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

class HeThongTuoiCay {
    private:
        int doAmDat;
        int nguongTuoi;
        bool vanNuoc;
        int soLanTuoi;

    public:
    HeThongTuoiCay(int nguong = 30) {
        if (nguong < 0 || nguong > 100) {
            cout << "Nguong tuoi khong hop le! Su dung mac dinh (30)." << endl;
            nguongTuoi = 30;
        } else {
            nguongTuoi = nguong;
        }
        doAmDat = 50;
        vanNuoc = false;
        soLanTuoi = 0;

        cout << "He thong tuoi cay da duoc khoi tao voi nguong tuoi: " << nguongTuoi << endl;
    }

    void capNhatDoAmDat(int doAm) {
        if (doAm < 0 || doAm > 100) {
            cout << "Do am dat khong hop le! phai tu 0-100%" << endl;
            return;
        }

        doAmDat = doAm;
        cout << "Do am dat da duoc cap nhat thanh " << doAm << "%" << endl;

        kiemTraVaTuoiCay();
    }

    void kiemTraVaTuoiCay() {
        cout << "Kiem tra he thong tuoi cay" << endl;
        cout << "Do am dat hien tai: " << doAmDat << "%" << endl;
        if (doAmDat < nguongTuoi && !vanNuoc) {
            // Đất khô và van đang đóng -> Mở van tưới
            vanNuoc = true;
            soLanTuoi++;
            cout << "🚰 CẢNH BÁO: Đất khô! Mở van nước tưới...\n";
            cout << "Van nước: MỞ | Lần tưới thứ: " << soLanTuoi << "\n";
        } else if (doAmDat >= nguongTuoi && vanNuoc) {
            // Đất đã đủ ẩm và van đang mở -> Đóng van
            vanNuoc = false;
            cout << "✅ Độ ẩm đã đủ! Đóng van nước.\n";
        } else if (doAmDat >= nguongTuoi) {
            cout << "✅ Độ ẩm tốt, không cần tưới.\n";
        } else {
            cout << "🚰 Đang tưới...\n";
        }
    }

    // Dừng tưới - đóng van nước
    void dungTuoi() {
        if (vanNuoc) {
            vanNuoc = false;
            cout << "⏹️ Dừng tưới - Đóng van nước.\n";
        } else {
            cout << "Van nước đã đóng rồi!\n";
        }
    }

    // Cài đặt ngưỡng tưới mới
    void caiDatNguong(int nguong) {
        if (nguong < 0 || nguong > 100) {
            cout << "Ngưỡng không hợp lệ! Phải từ 0-100%\n";
            return;
        }
        
        int nguongCu = nguongTuoi;
        nguongTuoi = nguong;
        cout << "Thay đổi ngưỡng tưới từ " << nguongCu << "% thành " << nguongTuoi << "%\n";
        
        // Kiểm tra lại sau khi thay đổi ngưỡng
        kiemTraVaTuoiCay();
    }

    // Getter methods - Lấy thông tin
    int getDoAmDat() const { return doAmDat; }
    int getNguongTuoi() const { return nguongTuoi; }
    bool getVanNuoc() const { return vanNuoc; }
    int getSoLanTuoi() const { return soLanTuoi; }

    // Setter methods với validation
    void setDoAmDat(int doAm) {
        if (doAm >= 0 && doAm <= 100) {
            doAmDat = doAm;
        } else {
            cout << "Độ ẩm không hợp lệ!\n";
        }
    }

    void setNguongTuoi(int nguong) {
        if (nguong >= 0 && nguong <= 100) {
            nguongTuoi = nguong;
        } else {
            cout << "Ngưỡng không hợp lệ!\n";
        }
    }

    // Hiển thị trạng thái hệ thống
    void hienThiTrangThai() {
        cout << "\n" << string(50, '=') << "\n";
        cout << "           TRẠNG THÁI HỆ THỐNG TƯỚI\n";
        cout << string(50, '=') << "\n";
        cout << "Độ ẩm đất        : " << doAmDat << "%\n";
        cout << "Ngưỡng tưới      : " << nguongTuoi << "%\n";
        cout << "Van nước         : " << (vanNuoc ? "MỞ 🚰" : "ĐÓNG ⏹️") << "\n";
        cout << "Số lần đã tưới   : " << soLanTuoi << " lần\n";
        cout << "Trạng thái       : ";
        if (doAmDat < nguongTuoi) {
            cout << "CẦN TƯỚI ⚠️\n";
        } else {
            cout << "TỐT ✅\n";
        }
        cout << string(50, '=') << "\n\n";
    }
};

// Hàm nhập số an toàn
int nhapSoAnToan(const string& thongBao, int min = 0, int max = 100) {
    int gia_tri;
    while (true) {
        cout << thongBao;
        if (cin >> gia_tri && gia_tri >= min && gia_tri <= max) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return gia_tri;
        } else {
            cout << "❌ Vui lòng nhập số từ " << min << " đến " << max << "!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

// Hàm hiển thị menu
void hienThiMenu() {
    cout << "\n" << string(40, '-') << "\n";
    cout << "    HỆ THỐNG TƯỚI CÂY TỰ ĐỘNG\n";
    cout << string(40, '-') << "\n";
    cout << "1. Cập nhật độ ẩm từ cảm biến\n";
    cout << "2. Kiểm tra và tưới tự động\n";
    cout << "3. Dừng tưới (đóng van)\n";
    cout << "4. Cài đặt ngưỡng tưới\n";
    cout << "5. Xem trạng thái hệ thống\n";
    cout << "0. Thoát chương trình\n";
    cout << string(40, '-') << "\n";
}

int main() {
    cout << "🌱 CHƯƠNG TRÌNH HỆ THỐNG TƯỚI CÂY TỰ ĐỘNG 🌱\n";
    cout << string(50, '=') << "\n";

    // Khởi tạo hệ thống với ngưỡng tưới do người dùng nhập
    int nguongBanDau = nhapSoAnToan("Nhập ngưỡng tưới ban đầu (0-100%): ");
    HeThongTuoiCay heThong(nguongBanDau);

    int luaChon;
    do {
        hienThiMenu();
        luaChon = nhapSoAnToan("Nhập lựa chọn (0-5): ", 0, 5);
        
        switch (luaChon) {
            case 1: {
                int doAm = nhapSoAnToan("Nhập độ ẩm từ cảm biến (0-100%): ");
                heThong.capNhatDoAmDat(doAm);
                break;
            }
            case 2:
                heThong.kiemTraVaTuoiCay();
                break;
            case 3:
                heThong.dungTuoi();
                break;
            case 4: {
                int nguongMoi = nhapSoAnToan("Nhập ngưỡng tưới mới (0-100%): ");
                heThong.caiDatNguong(nguongMoi);
                break;
            }
            case 5:
                heThong.hienThiTrangThai();
                break;
            case 0:
                cout << "🌿 Cảm ơn bạn đã sử dụng hệ thống tưới cây! 🌿\n";
                break;
        }
        
        if (luaChon != 0 && luaChon != 5) {
            cout << "\nNhấn Enter để tiếp tục...";
            cin.get();
        }
    } while (luaChon != 0);

    return 0;
}
