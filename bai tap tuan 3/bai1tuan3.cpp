#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <cmath>
using namespace std;

// ===== ENUMS - Định nghĩa các hằng số =====
enum Huong { BAC, NAM, DONG, TAY };
enum TrangThai { DANG_DON, DANG_SAC, TAT, CHO, VE_SAC };
enum CheDoLamViec { ECO, NORMAL, TURBO };
enum LoaiO { SACH, BAN, VAT_CAN, TRAM_SAC };

// ===== LỚP CHA: ROBOT =====
class Robot {
protected:
    int viTriX, viTriY;
    Huong huong;
    float mucPin;
    TrangThai trangThai;
    int tocDoDiChuyen;
    string tenRobot;
    vector<pair<int,int>> lichSuDiChuyen;

public:
    Robot(string ten = "Robot", int x = 0, int y = 0) {
        tenRobot = ten;
        viTriX = x;
        viTriY = y;
        huong = BAC;
        mucPin = 100.0;
        trangThai = CHO;
        tocDoDiChuyen = 1;
        lichSuDiChuyen.push_back({x, y});
    }

    // ===== GETTER METHODS =====
    pair<int,int> layViTri() const { return {viTriX, viTriY}; }
    Huong layHuong() const { return huong; }
    float kiemTraPin() const { return mucPin; }
    TrangThai layTrangThai() const { return trangThai; }
    string layTenRobot() const { return tenRobot; }

    // ===== SETTER METHODS =====
    void datTrangThai(TrangThai tt) { trangThai = tt; }
    void datViTri(int x, int y) { 
        viTriX = x; 
        viTriY = y; 
        lichSuDiChuyen.push_back({x, y});
    }

    // ===== PHƯƠNG THỨC DI CHUYỂN =====
    bool diChuyenToi(int x, int y) {
        if (mucPin >= 3.0) {
            float khoangCach = abs(x - viTriX) + abs(y - viTriY);
            float pinCanThiet = khoangCach * 1.5; // 1.5% pin mỗi ô
            
            if (mucPin >= pinCanThiet) {
                viTriX = x;
                viTriY = y;
                mucPin -= pinCanThiet;
                lichSuDiChuyen.push_back({x, y});
                cout << tenRobot << " di chuyển đến (" << x << "," << y 
                     << ") - Pin còn: " << fixed << setprecision(1) << mucPin << "%" << endl;
                return true;
            }
        }
        cout << "⚠️ " << tenRobot << " không đủ pin để di chuyển!" << endl;
        return false;
    }

    // ===== PHƯƠNG THỨC SẠC PIN =====
    void sacPin() {
        if (mucPin < 100.0) {
            mucPin = min(100.0f, mucPin + 8.0f); // Sạc nhanh hơn: 8%/lần
            cout << "🔋 " << tenRobot << " đang sạc... Pin: " 
                 << fixed << setprecision(1) << mucPin << "%" << endl;
        }
    }

    // ===== HIỂN THỊ THÔNG TIN =====
    virtual void hienThiThongTin() {
        cout << "\n=== THÔNG TIN " << tenRobot << " ===" << endl;
        cout << "📍 Vị trí: (" << viTriX << "," << viTriY << ")" << endl;
        cout << "🧭 Hướng: " << (huong == BAC ? "Bắc" : huong == NAM ? "Nam" : 
                              huong == DONG ? "Đông" : "Tây") << endl;
        cout << "🔋 Pin: " << fixed << setprecision(1) << mucPin << "%" << endl;
        cout << "⚡ Trạng thái: " << (trangThai == DANG_DON ? "Đang dọn" :
                                  trangThai == DANG_SAC ? "Đang sạc" :
                                  trangThai == VE_SAC ? "Đang về sạc" :
                                  trangThai == TAT ? "Tắt" : "Chờ") << endl;
    }
};

// ===== LỚP CON: ROBOT HÚT BỤI =====
class RobotHutBui : public Robot {
private:
    int dungLuongHopBui;
    int buiHienTai;
    int soODaDon;
    int congSuatHut;
    CheDoLamViec cheDoLamViec;
    bool coSensorBui;
    int thoiGianDon;
    int soLanVeSac; // Đếm số lần về sạc

public:
    RobotHutBui(string ten = "RobotHutBui", int x = 0, int y = 0) 
        : Robot(ten, x, y) {
        dungLuongHopBui = 300; // Giảm dung lượng để cần đổ bụi thường xuyên hơn
        buiHienTai = 0;
        soODaDon = 0;
        congSuatHut = 25;
        cheDoLamViec = NORMAL;
        coSensorBui = true;
        thoiGianDon = 0;
        soLanVeSac = 0;
    }

    // ===== GETTER METHODS =====
    int layDungLuongHopBui() const { return dungLuongHopBui; }
    int layBuiHienTai() const { return buiHienTai; }
    int laySoODaDon() const { return soODaDon; }
    int laySoLanVeSac() const { return soLanVeSac; }

    // ===== KIỂM TRA CẦN SẠC =====
    bool canSac() const {
        return mucPin < 25.0; // Cần sạc khi pin dưới 25%
    }

    bool canDoBui() const {
        return kiemTraHopBui() > 85.0; // Cần đổ bụi khi đầy 85%
    }

    // ===== PHƯƠNG THỨC HÚT BỤI =====
    bool hutBui() {
        if (trangThai != DANG_DON) {
            cout << "❌ Robot không trong chế độ dọn dẹp!" << endl;
            return false;
        }

        if (canDoBui()) {
            cout << "🗑️ Hộp bụi đầy! Cần làm trống!" << endl;
            return false;
        }

        if (mucPin < 8.0) {
            cout << "⚠️ Pin quá thấp để hút bụi!" << endl;
            return false;
        }

        // Mô phỏng hút bụi
        int luongBuiHut = 0;
        switch(cheDoLamViec) {
            case ECO: 
                luongBuiHut = 15; 
                mucPin -= 2.5; 
                break;
            case NORMAL: 
                luongBuiHut = 25; 
                mucPin -= 4.0; 
                break;
            case TURBO: 
                luongBuiHut = 35; 
                mucPin -= 6.0; 
                break;
        }

        buiHienTai = min(dungLuongHopBui, buiHienTai + luongBuiHut);
        soODaDon++;
        thoiGianDon += 5; // 5 giây/ô

        cout << "🧹 " << tenRobot << " hút bụi tại (" << viTriX << "," << viTriY 
             << ") - Thu được " << luongBuiHut << "ml bụi (Pin: " 
             << fixed << setprecision(1) << mucPin << "%)" << endl;
        
        return true;
    }

    // ===== KIỂM TRA HỘP BỤI =====
    float kiemTraHopBui() const {
        return (float)buiHienTai / dungLuongHopBui * 100.0;
    }

    void doBui() {
        buiHienTai = 0;
        cout << "🗑️ " << tenRobot << " đã làm trống hộp bụi" << endl;
    }

    // ===== ĐẶT CHỂ ĐỘ HÚT =====
    void datCheDoHut(CheDoLamViec cheDo) {
        cheDoLamViec = cheDo;
        string tenCheDo = (cheDo == ECO ? "ECO 🌱" : 
                          cheDo == NORMAL ? "NORMAL ⚡" : "TURBO 🚀");
        cout << "🔧 " << tenRobot << " chuyển sang chế độ " << tenCheDo << endl;
    }

    // ===== TĂNG SỐ LẦN VỀ SẠC =====
    void tangSoLanVeSac() {
        soLanVeSac++;
    }

    // ===== BÁO CÁO KẾT QUẢ =====
    void baoCaoDonDep() {
        cout << "\n📊 === BÁO CÁO DỌN DẸP ===" << endl;
        cout << "🤖 Robot: " << tenRobot << endl;
        cout << "🏠 Số ô đã dọn: " << soODaDon << endl;
        cout << "⏱️ Thời gian dọn: " << thoiGianDon << " giây" << endl;
        cout << "🗑️ Bụi đã thu: " << buiHienTai << "/" << dungLuongHopBui << " ml" << endl;
        cout << "🔌 Số lần về sạc: " << soLanVeSac << endl;
        cout << "🔋 Pin còn lại: " << fixed << setprecision(1) << mucPin << "%" << endl;
    }

    // Override phương thức hiển thị thông tin
    void hienThiThongTin() override {
        Robot::hienThiThongTin();
        cout << "🗑️ Hộp bụi: " << buiHienTai << "/" << dungLuongHopBui 
             << " ml (" << fixed << setprecision(1) << kiemTraHopBui() << "%)" << endl;
        cout << "🧹 Ô đã dọn: " << soODaDon << endl;
        cout << "🔧 Chế độ: " << (cheDoLamViec == ECO ? "ECO 🌱" :
                              cheDoLamViec == NORMAL ? "NORMAL ⚡" : "TURBO 🚀") << endl;
        cout << "🔌 Số lần về sạc: " << soLanVeSac << endl;
    }
};

// ===== LỚP PHÒNG =====
class Phong {
private:
    int chieuDai, chieuRong;
    vector<vector<LoaiO>> maTranO;
    pair<int,int> viTriTramSac;
    int soOBan;
    int soVatCan;
    vector<pair<int,int>> danhSachVatCan;
    vector<pair<int,int>> danhSachViTriBan; // Lưu vị trí bẩn do người dùng nhập

public:
    Phong(int dai = 10, int rong = 10) {
        chieuDai = dai;
        chieuRong = rong;
        soOBan = 0;
        soVatCan = 0;
        viTriTramSac = {0, 0};
        
        khoiTaoPhongTrong();
    }

    // ===== KHỞI TẠO PHÒNG TRỐNG =====
    void khoiTaoPhongTrong() {
        // Khởi tạo ma trận toàn bộ sạch
        maTranO = vector<vector<LoaiO>>(chieuRong, vector<LoaiO>(chieuDai, SACH));
        
        // Đặt trạm sạc ở góc (0,0)
        maTranO[0][0] = TRAM_SAC;
        viTriTramSac = {0, 0};
        
        cout << "🏠 Phòng " << chieuDai << "x" << chieuRong 
             << " đã được khởi tạo (trống)" << endl;
    }

    // ===== THÊM VẬT CẢN NGẪU NHIÊN =====
    void themVatCanNgauNhien(int soPhanTram = 10) {
        srand(time(0));
        int soVatCanTaoRa = (chieuDai * chieuRong) * soPhanTram / 100;
        
        cout << "🚧 Thêm " << soVatCanTaoRa << " vật cản ngẫu nhiên..." << endl;
        
        for (int i = 0; i < soVatCanTaoRa; i++) {
            int x = rand() % chieuDai;
            int y = rand() % chieuRong;
            
            // Không đặt vật cản tại trạm sạc hoặc vị trí đã có vật cản
            if ((x != viTriTramSac.first || y != viTriTramSac.second) && 
                maTranO[y][x] != VAT_CAN) {
                datVatCan(x, y);
            }
        }
    }

    // ===== ĐẶT VẬT CẢN =====
    void datVatCan(int x, int y) {
        if (kiemTraHopLe(x, y) && maTranO[y][x] != TRAM_SAC) {
            maTranO[y][x] = VAT_CAN;
            danhSachVatCan.push_back({x, y});
            soVatCan++;
        }
    }

    // ===== ĐẶT BỤI THEO VỊ TRÍ NGƯỜI DÙNG NHẬP =====
    void datBuiTaiViTri(int x, int y) {
        if (kiemTraHopLe(x, y) && maTranO[y][x] == SACH) {
            maTranO[y][x] = BAN;
            soOBan++;
            danhSachViTriBan.push_back({x, y});
            cout << "🟤 Đặt bụi tại (" << x << "," << y << ")" << endl;
        } else if (!kiemTraHopLe(x, y)) {
            cout << "❌ Vị trí (" << x << "," << y << ") nằm ngoài phòng!" << endl;
        } else if (maTranO[y][x] == TRAM_SAC) {
            cout << "❌ Không thể đặt bụi tại trạm sạc!" << endl;
        } else if (maTranO[y][x] == VAT_CAN) {
            cout << "❌ Không thể đặt bụi tại vị trí có vật cản!" << endl;
        } else {
            cout << "❌ Vị trí (" << x << "," << y << ") đã có bụi!" << endl;
        }
    }

    // ===== LÀM SẠCH Ô =====
    bool lamSachO(int x, int y) {
        if (kiemTraHopLe(x, y) && maTranO[y][x] == BAN) {
            maTranO[y][x] = SACH;
            soOBan--;
            cout << "✨ Ô (" << x << "," << y << ") đã được làm sạch" << endl;
            return true;
        }
        return false;
    }

    // ===== TÌM ĐƯỜNG NGẮN NHẤT VỀ TRẠM SẠC (BFS) =====
    vector<pair<int,int>> timDuongVeTramSac(int startX, int startY) {
        vector<vector<bool>> daXet(chieuRong, vector<bool>(chieuDai, false));
        vector<vector<pair<int,int>>> parent(chieuRong, vector<pair<int,int>>(chieuDai, {-1, -1}));
        queue<pair<int,int>> hangDoi;
        
        hangDoi.push({startX, startY});
        daXet[startY][startX] = true;
        
        // 4 hướng di chuyển
        int dx[] = {0, 0, 1, -1};
        int dy[] = {1, -1, 0, 0};
        
        while (!hangDoi.empty()) {
            auto [x, y] = hangDoi.front();
            hangDoi.pop();
            
            // Nếu đến trạm sạc
            if (x == viTriTramSac.first && y == viTriTramSac.second) {
                vector<pair<int,int>> duong;
                int cx = x, cy = y;
                
                // Xây dựng đường đi từ cuối về đầu
                while (parent[cy][cx].first != -1) {
                    duong.push_back({cx, cy});
                    auto [px, py] = parent[cy][cx];
                    cx = px;
                    cy = py;
                }
                
                reverse(duong.begin(), duong.end());
                return duong;
            }
            
            // Thử 4 hướng
            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                
                if (kiemTraHopLe(nx, ny) && !daXet[ny][nx] && !kiemTraVatCan(nx, ny)) {
                    daXet[ny][nx] = true;
                    parent[ny][nx] = {x, y};
                    hangDoi.push({nx, ny});
                }
            }
        }
        
        return {}; // Không tìm thấy đường
    }

    // ===== KIỂM TRA =====
    bool kiemTraHopLe(int x, int y) const {
        return (x >= 0 && x < chieuDai && y >= 0 && y < chieuRong);
    }

    LoaiO kiemTraO(int x, int y) const {
        if (!kiemTraHopLe(x, y)) return VAT_CAN;
        return maTranO[y][x];
    }

    bool kiemTraVatCan(int x, int y) const {
        return kiemTraO(x, y) == VAT_CAN || !kiemTraHopLe(x, y);
    }

    // ===== GETTER METHODS =====
    int layChieuDai() const { return chieuDai; }
    int layChieuRong() const { return chieuRong; }
    int laySoOBan() const { return soOBan; }
    pair<int,int> layViTriTramSac() const { return viTriTramSac; }
    vector<pair<int,int>> layDanhSachViTriBan() const { return danhSachViTriBan; }

    // ===== HIỂN THỊ BẢN ĐỒ =====
    void hienThiBanDo(const RobotHutBui& robot) {
        cout << "\n🗺️  === BẢN ĐỒ PHÒNG ===" << endl;
        cout << "   ";
        for (int x = 0; x < chieuDai; x++) {
            cout << setw(3) << x;
        }
        cout << endl;

        for (int y = 0; y < chieuRong; y++) {
            cout << setw(2) << y << " ";
            for (int x = 0; x < chieuDai; x++) {
                pair<int,int> robotPos = robot.layViTri();
                
                if (robotPos.first == x && robotPos.second == y) {
                    cout << " 🤖";
                } else {
                    switch(maTranO[y][x]) {
                        case SACH: cout << " · "; break;
                        case BAN: cout << " 🟤"; break;
                        case VAT_CAN: cout << " ■ "; break;
                        case TRAM_SAC: cout << " ⚡"; break;
                    }
                }
            }
            cout << endl;
        }
        
        cout << "\nChú thích: 🤖=Robot, ·=Sạch, 🟤=Bẩn, ■=Vật cản, ⚡=Trạm sạc" << endl;
        cout << "Còn lại " << soOBan << " ô bẩn" << endl;
    }
};

// ===== LỚP TRẠM SẠC =====
class TramSac {
private:
    int viTriX, viTriY;
    bool dangSac;
    float tocDoSac;

public:
    TramSac(int x = 0, int y = 0) {
        viTriX = x;
        viTriY = y; 
        dangSac = false;
        tocDoSac = 8.0;
    }

    bool batDauSac(RobotHutBui& robot) {
        pair<int,int> robotPos = robot.layViTri();
        if (robotPos.first == viTriX && robotPos.second == viTriY) {
            dangSac = true;
            robot.datTrangThai(DANG_SAC);
            cout << "🔌 " << robot.layTenRobot() << " bắt đầu sạc tại trạm" << endl;
            return true;
        }
        return false;
    }

    void dungSac(RobotHutBui& robot) {
        dangSac = false;
        robot.datTrangThai(CHO);
        cout << "🔋 " << robot.layTenRobot() << " đã sạc xong (Pin: " 
             << fixed << setprecision(1) << robot.kiemTraPin() << "%)" << endl;
    }

    bool kiemTraCoSan() const {
        return !dangSac;
    }
};

// ===== HÀM NHẬP DỮ LIỆU =====
void nhapKichThuocPhong(int& dai, int& rong) {
    cout << "\n📐 === NHẬP KÍCH THƯỚC PHÒNG ===" << endl;
    do {
        cout << "Nhập chiều dài phòng (5-20): ";
        cin >> dai;
        if (dai < 5 || dai > 20) {
            cout << "❌ Chiều dài phải từ 5 đến 20!" << endl;
        }
    } while (dai < 5 || dai > 20);
    
    do {
        cout << "Nhập chiều rộng phòng (5-15): ";
        cin >> rong;
        if (rong < 5 || rong > 15) {
            cout << "❌ Chiều rộng phải từ 5 đến 15!" << endl;
        }
    } while (rong < 5 || rong > 15);
    
    cout << "✅ Đã tạo phòng kích thước " << dai << "x" << rong << endl;
}

void nhapViTriBan(Phong& phong) {
    cout << "\n🟤 === NHẬP VỊ TRÍ BẨN ===" << endl;
    cout << "Nhập số lượng vị trí bẩn: ";
    int soViTri;
    cin >> soViTri;
    
    if (soViTri <= 0) {
        cout << "❌ Không có vị trí bẩn nào được thêm!" << endl;
        return;
    }
    
    cout << "Nhập tọa độ các vị trí bẩn (x y):" << endl;
    cout << "Lưu ý: x từ 0-" << (phong.layChieuDai()-1) 
         << ", y từ 0-" << (phong.layChieuRong()-1) << endl;
         
    for (int i = 0; i < soViTri; i++) {
        int x, y;
        cout << "Vị trí " << (i+1) << ": ";
        cin >> x >> y;
        phong.datBuiTaiViTri(x, y);
    }
    
    cout << "✅ Đã thêm " << soViTri << " vị trí bẩn!" << endl;
}

// ===== HÀM MAIN =====
int main() {
    cout << "🤖 === ROBOT DỌN DẸP PHÒNG - PHIÊN BẢN CẢI TIẾN ===" << endl;
    
    // 1. NHẬP KÍCH THƯỚC PHÒNG
    int chieuDai, chieuRong;
    nhapKichThuocPhong(chieuDai, chieuRong);
    
    // 2. KHỞI TẠO HỆ THỐNG
    Phong phong(chieuDai, chieuRong);
    RobotHutBui robot("CleanBot-Pro");
    TramSac tram(0, 0);
    
    robot.datViTri(0, 0);
    robot.datTrangThai(CHO);
    
    // 3. THÊM VẬT CẢN NGẪU NHIÊN
    phong.themVatCanNgauNhien(8); // 8% diện tích
    
    // 4. NHẬP VỊ TRÍ BẨN
    nhapViTriBan(phong);
    
    if (phong.laySoOBan() == 0) {
        cout << "❌ Không có vị trí bẩn nào! Kết thúc chương trình." << endl;
        return 0;
    }
    
    // 5. HIỂN THỊ TRẠNG THÁI BAN ĐẦU
    cout << "\n📊 === TRẠNG THÁI BAN ĐẦU ===" << endl;
    phong.hienThiBanDo(robot);
    robot.hienThiThongTin();
    
    // 6. BẮT ĐẦU DỌN DẸP
    cout << "\n🧹 === BẮT ĐẦU DỌN DẸP ===" << endl;
    robot.datCheDoHut(NORMAL);
    robot.datTrangThai(DANG_DON);
    
    int buocDiChuyen = 0;
    vector<pair<int,int>> viTriBanConLai = phong.layDanhSachViTriBan();
    int viTriHienTai = 0;
    
    while (phong.laySoOBan() > 0 && buocDiChuyen < 200) {
        buocDiChuyen++;
        
        // Kiểm tra cần sạc
        if (robot.canSac() && robot.layTrangThai() != VE_SAC) {
            cout << "\n⚠️ === PIN THẤP - BẮT ĐẦU VỀ SẠC ===" << endl;
            robot.datTrangThai(VE_SAC);
            robot.tangSoLanVeSac();
        }
        
        // Kiểm tra cần đổ bụi
        if (robot.canDoBui()) {
            cout << "\n🗑️ === HỘP BỤI ĐẦY - ĐỔ BỤI ===" << endl;
            robot.doBui();
        }
        
        // Nếu đang về sạc
        if (robot.layTrangThai() == VE_SAC) {
            pair<int,int> viTriHienTai = robot.layViTri();
            auto duongVeSac = phong.timDuongVeTramSac(viTriHienTai.first, viTriHienTai.second);
            
            if (!duongVeSac.empty()) {
                // Di chuyển theo đường về trạm sạc
                auto viTriTiepTheo = duongVeSac[0];
                if (robot.diChuyenToi(viTriTiepTheo.first, viTriTiepTheo.second)) {
                    // Kiểm tra đã đến trạm sạc chưa
                    if (viTriTiepTheo == phong.layViTriTramSac()) {
                        cout << "🏠 Robot đã về đến trạm sạc!" << endl;
                        tram.batDauSac(robot);
                        
                        // Sạc đến 90%
                        while (robot.kiemTraPin() < 90.0) {
                            robot.sacPin();
                        }
                        tram.dungSac(robot);
                        robot.datTrangThai(DANG_DON);
                        cout << "🔋 Robot đã sạc xong, tiếp tục dọn dẹp!" << endl;
                    }
                }
            } else {
                cout << "❌ Không tìm thấy đường về trạm sạc!" << endl;
                robot.datViTri(0, 0); // Teleport về trạm sạc (trường hợp khẩn cấp)
            }
            continue;
        }
        
        // Tiếp tục dọn dẹp
        if (robot.layTrangThai() == DANG_DON) {
            pair<int,int> viTriRobot = robot.layViTri();
            
            // Kiểm tra ô hiện tại có bẩn không
            if (phong.kiemTraO(viTriRobot.first, viTriRobot.second) == BAN) {
                if (robot.hutBui()) {
                    phong.lamSachO(viTriRobot.first, viTriRobot.second);
                }
            }
            
            // Tìm ô bẩn gần nhất
            int oGanNhat = -1;
            float khoangCachNhoNhat = 1000;
            
            for (int i = 0; i < viTriBanConLai.size(); i++) {
                auto [x, y] = viTriBanConLai[i];
                if (phong.kiemTraO(x, y) == BAN) {
                    float khoangCach = abs(x - viTriRobot.first) + abs(y - viTriRobot.second);
                    if (khoangCach < khoangCachNhoNhat) {
                        khoangCachNhoNhat = khoangCach;
                        oGanNhat = i;
                    }
                }
            }
            
            // Di chuyển đến ô bẩn gần nhất
            if (oGanNhat != -1) {
                auto [targetX, targetY] = viTriBanConLai[oGanNhat];
                
                // Di chuyển từng bước về phía target
                int deltaX = (targetX > viTriRobot.first) ? 1 : (targetX < viTriRobot.first) ? -1 : 0;
                int deltaY = (targetY > viTriRobot.second) ? 1 : (targetY < viTriRobot.second) ? -1 : 0;
                
                int newX = viTriRobot.first + deltaX;
                int newY = viTriRobot.second + deltaY;
                
                // Kiểm tra có thể di chuyển không
                if (!phong.kiemTraVatCan(newX, newY)) {
                    if (!robot.diChuyenToi(newX, newY)) {
                        // Không đủ pin để di chuyển
                        robot.datTrangThai(VE_SAC);
                        robot.tangSoLanVeSac();
                        continue;
                    }
                } else {
                    // Thử tìm đường khác
                    bool daDiChuyen = false;
                    int dx[] = {1, -1, 0, 0};
                    int dy[] = {0, 0, 1, -1};
                    
                    for (int i = 0; i < 4; i++) {
                        int nx = viTriRobot.first + dx[i];
                        int ny = viTriRobot.second + dy[i];
                        
                        if (!phong.kiemTraVatCan(nx, ny)) {
                            if (robot.diChuyenToi(nx, ny)) {
                                daDiChuyen = true;
                                break;
                            }
                        }
                    }
                    
                    if (!daDiChuyen) {
                        cout << "🚧 Robot bị kẹt! Thử tìm đường khác..." << endl;
                    }
                }
            }
        }
        
        // Hiển thị trạng thái mỗi 10 bước
        if (buocDiChuyen % 10 == 0) {
            cout << "\n--- Bước " << buocDiChuyen << " ---" << endl;
            phong.hienThiBanDo(robot);
            cout << "🔋 Pin: " << fixed << setprecision(1) << robot.kiemTraPin() 
                 << "% | 🗑️ Hộp bụi: " << fixed << setprecision(1) << robot.kiemTraHopBui() << "%" << endl;
        }
        
        // Tạm dừng để quan sát (có thể bỏ trong phiên bản thực tế)
        if (buocDiChuyen % 5 == 0) {
            cout << "\n⏸️  Nhấn Enter để tiếp tục...";
            cin.ignore();
            cin.get();
        }
    }
    
    // 7. KẾT THÚC VÀ THỐNG KÊ
    cout << "\n🎉 === KẾT THÚC DỌN DẸP ===" << endl;
    
    robot.datTrangThai(CHO);
    phong.hienThiBanDo(robot);
    robot.baoCaoDonDep();
    
    cout << "\n📈 === THỐNG KÊ TỔNG KẾT ===" << endl;
    cout << "🏠 Diện tích phòng: " << phong.layChieuDai() << "x" << phong.layChieuRong() 
         << " = " << (phong.layChieuDai() * phong.layChieuRong()) << " ô" << endl;
    cout << "🧹 Số bước di chuyển: " << buocDiChuyen << endl;
    cout << "🗑️ Ô còn lại chưa sạch: " << phong.laySoOBan() << endl;
    cout << "🔌 Số lần robot về sạc: " << robot.laySoLanVeSac() << endl;
    cout << "🤖 Số ô đã dọn: " << robot.laySoODaDon() << endl;
    
    float hieuQuaDonDep = 0.0;
    if (viTriBanConLai.size() > 0) {
        hieuQuaDonDep = (float)(viTriBanConLai.size() - phong.laySoOBan()) / viTriBanConLai.size() * 100.0;
    }
    cout << "✅ Hiệu quả dọn dẹp: " << fixed << setprecision(1) << hieuQuaDonDep << "%" << endl;
    
    if (phong.laySoOBan() == 0) {
        cout << "\n🏆 XUẤT SẮC! Robot đã dọn sạch toàn bộ phòng!" << endl;
        cout << "🎖️  Chúc mừng bạn đã hoàn thành nhiệm vụ!" << endl;
    } else {
        cout << "\n⏰ Chưa hoàn thành hết (giới hạn 200 bước demo)" << endl;
        cout << "💡 Robot đã cố gắng hết sức!" << endl;
    }
    
    cout << "\n🎮 Cảm ơn bạn đã sử dụng Robot Dọn Dẹp Phòng!" << endl;
    cout << "💡 Nhấn Enter để thoát..." << endl;
    cin.ignore();
    cin.get();
    
    return 0;
}