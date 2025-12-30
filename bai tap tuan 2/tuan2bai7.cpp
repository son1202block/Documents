#include <iostream>
#include <string>
using namespace std;

class CongTuDong {
private:
    bool trangThai;   // true = đang bật, false = đang tắt
    string matKhau;   // mật khẩu điều khiển
    int soLuotRaVao;  // đếm số lần mở cổng

public:
    string viTriCong; // vị trí cổng (public)

    // constructor: nhận vị trí và mật khẩu, khởi tạo cổng đóng, soLuot = 0
    CongTuDong(string viTri, string mk) {
        viTriCong = viTri;
        matKhau = mk;
        trangThai = false;
        soLuotRaVao = 0;
    }

    // phương thức mở cổng với kiểm tra mật khẩu
    void moCong(string mk) {
        if (mk == matKhau) {
            if (!trangThai) { // nếu cổng đang đóng
                trangThai = true;
                soLuotRaVao++;
                cout << "✅ ĐÃ MỞ cổng tại " << viTriCong << endl;
                cout << "Số lần mở cổng: " << soLuotRaVao << endl;
            } else {
                cout << "⚠️ Cổng tại " << viTriCong << " đã mở rồi!" << endl;
            }
        } else {
            cout << "❌ Sai mật khẩu! Vui lòng nhập lại." << endl;
        }
    }

    // phương thức đóng cổng với kiểm tra mật khẩu
    void dongCong(string mk) {
        if (mk == matKhau && trangThai) {
            trangThai = false;
            cout << "✅ Cổng đã được đóng: " << viTriCong << endl;
        } else if (mk != matKhau) {
            cout << "❌ Sai mật khẩu! Không thể đóng cổng." << endl;
        } else {
            cout << "⚠️ Cổng đã đóng sẵn rồi." << endl;
        }
    }

    // phương thức xem thống kê số lượt ra vào
    void xemThongKe(string mk) {
        if (mk == matKhau) {
            cout << "=== 📊 THỐNG KÊ CỔNG TỰ ĐỘNG ===" << endl;
            cout << "Vị trí cổng: " << viTriCong << endl;
            cout << "Trạng thái hiện tại: " << (trangThai ? "Mở" : "Đóng") << endl;
            cout << "Tổng số lượt ra vào: " << soLuotRaVao << endl;
            cout << "==============================" << endl;
        } else {
            cout << "❌ Sai mật khẩu! Không thể xem thống kê." << endl;
        }
    }

    // phương thức đổi mật khẩu
    void doiMatKhau(string mkCu, string mkMoi) {
        if (mkCu == matKhau) {
            matKhau = mkMoi;
            cout << "✅ Đã đổi mật khẩu thành công!" << endl;
        } else {
            cout << "❌ Sai mật khẩu cũ! Không thể đổi mật khẩu." << endl;
        }
    }

    // getter để kiểm tra trạng thái cổng (chỉ đọc)
    bool getTrangThai() {
        return trangThai;
    }
};

// =========================
// Chương trình chính (Menu)
// =========================
int main() {
    CongTuDong congChinh("Cổng chính tòa nhà", "123456");

    int luaChon;
    string mk, mkMoi;

    do {
        cout << "\n=== MENU ĐIỀU KHIỂN CỔNG TỰ ĐỘNG ===" << endl;
        cout << "1. Mở cổng" << endl;
        cout << "2. Đóng cổng" << endl;
        cout << "3. Xem thống kê" << endl;
        cout << "4. Đổi mật khẩu" << endl;
        cout << "0. Thoát" << endl;
        cout << "👉 Nhập lựa chọn: ";
        cin >> luaChon;

        switch (luaChon) {
            case 1:
                cout << "Nhập mật khẩu để mở cổng: ";
                cin >> mk;
                congChinh.moCong(mk);
                break;
            case 2:
                cout << "Nhập mật khẩu để đóng cổng: ";
                cin >> mk;
                congChinh.dongCong(mk);
                break;
            case 3:
                cout << "Nhập mật khẩu để xem thống kê: ";
                cin >> mk;
                congChinh.xemThongKe(mk);
                break;
            case 4:
                cout << "Nhập mật khẩu cũ: ";
                cin >> mk;
                cout << "Nhập mật khẩu mới: ";
                cin >> mkMoi;
                congChinh.doiMatKhau(mk, mkMoi);
                break;
            case 0:
                cout << "👋 Thoát chương trình." << endl;
                break;
            default:
                cout << "❌ Lựa chọn không hợp lệ! Hãy nhập lại." << endl;
        }
    } while (luaChon != 0);

    return 0;
}
