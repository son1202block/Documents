#include <iostream>
#include <string>

// Class = Bản thiết kế: Class DenLED là bản vẽ chung cho mọi đèn
// Object = Sản phẩm thực: Mỗi đèn cụ thể (đèn phòng khách, đèn phòng ngủ) là một object
// Thuộc tính = Đặc điểm: Mô tả đèn có gì (vị trí, màu, độ sáng)
// Phương thức = Hành động: Đèn có thể làm gì (bật, tắt, điều chỉnh)

class DenLED {
public:
    // Thuộc tính PUBLIC
    std::string viTri;   // Vị trí lắp đèn (phòng khách, phòng ngủ...)
    std::string mauSac;  // Màu của đèn
    int doSang;          // Độ sáng (0-100%)

    // Hàm tạo tiện dụng (không bắt buộc theo yêu cầu nhưng hữu ích)
    DenLED(const std::string &viTriLap, const std::string &mau, int doSangBanDau)
        : viTri(viTriLap), mauSac(mau), doSang(clampDoSang(doSangBanDau)) {}

    // Phương thức PUBLIC
    void batDen() {
        // Nếu đang tắt (độ sáng = 0) thì đặt mức mặc định 10%
        if (doSang == 0) {
            doSang = 10;
        }
        std::cout << "[BẬT] Đèn ở " << viTri
                  << " (màu " << mauSac
                  << ") đang bật với độ sáng " << doSang << "%\n";
    }

    void tatDen() {
        doSang = 0;
        std::cout << "[TẮT] Đèn ở " << viTri
                  << " (màu " << mauSac
                  << ") đã tắt.\n";
    }

    void tangDoSang() {
        int doSangMoi = clampDoSang(doSang + 10);
        std::cout << "[TĂNG] Độ sáng " << viTri
                  << ": " << doSang << "% -> " << doSangMoi << "%\n";
        doSang = doSangMoi;
    }

    void giamDoSang() {
        int doSangMoi = clampDoSang(doSang - 10);
        std::cout << "[GIẢM] Độ sáng " << viTri
                  << ": " << doSang << "% -> " << doSangMoi << "%\n";
        doSang = doSangMoi;
    }

private:
    static int clampDoSang(int value) {
        if (value < 0) return 0;
        if (value > 100) return 100;
        return value;
    }
};

int main() {
    // Tạo hai object đèn: phòng khách và phòng ngủ
    DenLED denPhongKhach("phòng khách", "trắng ấm", 0);
    DenLED denPhongNgu("phòng ngủ", "vàng", 30);

    // Minh hoạ thao tác
    denPhongKhach.batDen();   // Bật đèn phòng khách (mặc định 10%)
    denPhongKhach.tangDoSang();
    denPhongKhach.tangDoSang();
    denPhongKhach.giamDoSang();

    denPhongNgu.batDen();     // Đang 30%, chỉ in trạng thái bật
    denPhongNgu.giamDoSang();
    denPhongNgu.tatDen();

    return 0;
}


