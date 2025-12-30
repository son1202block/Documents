#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <cmath>
#include <fstream>
#include <map>
using namespace std;

// ===== ENUMS - Định nghĩa các hằng số =====
enum Huong { BAC, NAM, DONG, TAY };
enum TrangThai { DANG_DON, DANG_SAC, TAT, CHO, VE_SAC };
enum CheDoLamViec { ECO, NORMAL, TURBO };
enum LoaiO { SACH, BAN, VAT_CAN, TRAM_SAC };
enum CheDoHoc { DANG_HOC, DA_HOC, TAT_HOC };

// ===== BIẾN GLOBAL ĐIỀU KHIỂN OUTPUT =====
bool CHI_TIET_OUTPUT = false;
bool HIEN_THI_BAN_DO_CHI_TIET = false;
int BUOC_HIEN_THI = 20; // Hiển thị mỗi N bước

// ===== LỚP BỘ NHỚ KINH NGHIỆM =====
class BoNhoKinhNghiem {
private:
    vector<pair<int,int>> danhSachVaCham;
    vector<vector<float>> banDoNguyHiem;
    int soLanVaCham;
    vector<vector<int>> banDoTanSuat;
    float mucDoHoc;
    int kichThuocVung;
    float trongSoGiamDan;
    int chieuDai, chieuRong;

public:
    BoNhoKinhNghiem(int dai, int rong) : chieuDai(dai), chieuRong(rong) {
        soLanVaCham = 0;
        mucDoHoc = 0.0;
        kichThuocVung = 2;
        trongSoGiamDan = 0.7;
        
        banDoNguyHiem = vector<vector<float>>(rong, vector<float>(dai, 0.0));
        banDoTanSuat = vector<vector<int>>(rong, vector<int>(dai, 0));
    }

    // ===== GHI NHỚ VA CHẠM (Rút gọn output) =====
    void ghiNhoVaCham(int x, int y, Huong huong) {
        danhSachVaCham.push_back({x, y});
        soLanVaCham++;
        banDoTanSuat[y][x]++;
        
        banDoNguyHiem[y][x] = 100.0;
        lanTruyenNguyHiem(x, y, kichThuocVung);
        capNhatMucDoHoc();
        
        // Chỉ hiển thị khi cần thiết
        if (CHI_TIET_OUTPUT) {
            cout << "Va chạm (" << x << "," << y << ") - Lần " << banDoTanSuat[y][x] << endl;
        }
    }

    float tinhDiemAnToan(int x, int y) const {
        if (x < 0 || x >= chieuDai || y < 0 || y >= chieuRong) {
            return 0.0;
        }
        
        float diemAnToan = 100.0 - banDoNguyHiem[y][x];
        if (banDoTanSuat[y][x] == 0) {
            diemAnToan += 10.0;
        }
        
        return max(0.0f, min(100.0f, diemAnToan));
    }

    // ===== GỢI Ý HƯỚNG DI (Rút gọn output) =====
    Huong goiYHuongDi(int x, int y) {
        vector<pair<float, Huong>> diemCacHuong;
        
        int dx[] = {0, 0, 1, -1};
        int dy[] = {-1, 1, 0, 0};
        Huong cacHuong[] = {BAC, NAM, DONG, TAY};
        
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            float diem = tinhDiemAnToan(nx, ny);
            diemCacHuong.push_back({diem, cacHuong[i]});
        }
        
        sort(diemCacHuong.rbegin(), diemCacHuong.rend());
        
        // Chỉ hiển thị chi tiết khi cần
        if (CHI_TIET_OUTPUT) {
            cout << "Hướng tối ưu: ";
            string tenHuong = (diemCacHuong[0].second == BAC ? "Bắc" : 
                              diemCacHuong[0].second == NAM ? "Nam" :
                              diemCacHuong[0].second == DONG ? "Đông" : "Tây");
            cout << tenHuong << "(" << fixed << setprecision(1) 
                 << diemCacHuong[0].first << ")" << endl;
        }
        
        return diemCacHuong[0].second;
    }

    void lanTruyenNguyHiem(int centerX, int centerY, int radius) {
        for (int dy = -radius; dy <= radius; dy++) {
            for (int dx = -radius; dx <= radius; dx++) {
                int nx = centerX + dx;
                int ny = centerY + dy;
                
                if (nx >= 0 && nx < chieuDai && ny >= 0 && ny < chieuRong) {
                    float khoangCach = sqrt(dx*dx + dy*dy);
                    if (khoangCach <= radius && khoangCach > 0) {
                        float mucDoNguyHiem = 100.0 * pow(trongSoGiamDan, khoangCach);
                        banDoNguyHiem[ny][nx] = max(banDoNguyHiem[ny][nx], mucDoNguyHiem);
                    }
                }
            }
        }
    }

    void capNhatMucDoHoc() {
        mucDoHoc = min(1.0f, (float)soLanVaCham / 20.0f);
    }

    void giamDanTheoThoiGian() {
        for (int y = 0; y < chieuRong; y++) {
            for (int x = 0; x < chieuDai; x++) {
                banDoNguyHiem[y][x] *= 0.98f;
            }
        }
    }

    // ===== THỐNG KÊ RÚT GỌN =====
    void thongKeTomTat() const {
        cout << "Va chạm: " << soLanVaCham 
             << " | Học: " << fixed << setprecision(1) << mucDoHoc * 100 << "%" << endl;
    }

    void xuatKinhNghiem() {
        ofstream file("robot_experience.txt");
        file << "Số va chạm: " << soLanVaCham << endl;
        file << "Mức độ học: " << fixed << setprecision(2) << mucDoHoc * 100 << "%" << endl;
        file.close();
        if (CHI_TIET_OUTPUT) {
            cout << "Đã lưu kinh nghiệm." << endl;
        }
    }

    int laySoLanVaCham() const { return soLanVaCham; }
    float layMucDoHoc() const { return mucDoHoc; }
    float layDiemNguyHiem(int x, int y) const {
        if (x >= 0 && x < chieuDai && y >= 0 && y < chieuRong) {
            return banDoNguyHiem[y][x];
        }
        return 100.0;
    }
};

// ===== LỚP CẢM BIẾN VA CHẠM (Rút gọn) =====
class CamBienVaCham {
private:
    int phamViPhatHien;
    bool trangThai;

public:
    CamBienVaCham() {
        phamViPhatHien = 3;
        trangThai = true;
    }

    map<Huong, int> quetMoiTruong(int x, int y, const vector<vector<LoaiO>>& banDo, int dai, int rong) {
        map<Huong, int> ketQua;
        
        if (!trangThai) {
            return ketQua;
        }
        
        int dx[] = {0, 0, 1, -1};
        int dy[] = {-1, 1, 0, 0};
        Huong cacHuong[] = {BAC, NAM, DONG, TAY};
        
        for (int i = 0; i < 4; i++) {
            int khoangCach = doKhoangCach(x, y, dx[i], dy[i], banDo, dai, rong);
            ketQua[cacHuong[i]] = khoangCach;
        }
        
        return ketQua;
    }

    int doKhoangCach(int startX, int startY, int dx, int dy, 
                     const vector<vector<LoaiO>>& banDo, int dai, int rong) {
        int khoangCach = 0;
        int x = startX;
        int y = startY;
        
        for (int i = 1; i <= phamViPhatHien; i++) {
            x += dx;
            y += dy;
            
            if (x < 0 || x >= dai || y < 0 || y >= rong || banDo[y][x] == VAT_CAN) {
                break;
            }
            khoangCach++;
        }
        
        return khoangCach;
    }

    bool kiemTraTrangThai() const { return trangThai; }
};

// ===== LỚP ROBOT CHA =====
class Robot {
protected:
    int viTriX, viTriY;
    Huong huong;
    float mucPin;
    TrangThai trangThai;
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
        lichSuDiChuyen.push_back({x, y});
    }

    pair<int,int> layViTri() const { return {viTriX, viTriY}; }
    Huong layHuong() const { return huong; }
    float kiemTraPin() const { return mucPin; }
    TrangThai layTrangThai() const { return trangThai; }
    string layTenRobot() const { return tenRobot; }

    void datTrangThai(TrangThai tt) { trangThai = tt; }
    void datViTri(int x, int y) { 
        viTriX = x; 
        viTriY = y; 
        lichSuDiChuyen.push_back({x, y});
    }

    bool diChuyenToi(int x, int y) {
        if (mucPin >= 3.0) {
            float khoangCach = abs(x - viTriX) + abs(y - viTriY);
            float pinCanThiet = khoangCach * 1.5;
            
            if (mucPin >= pinCanThiet) {
                viTriX = x;
                viTriY = y;
                mucPin -= pinCanThiet;
                lichSuDiChuyen.push_back({x, y});
                
                // Chỉ hiển thị khi cần thiết
                if (CHI_TIET_OUTPUT) {
                    cout << "→ (" << x << "," << y << ") Pin: " 
                         << fixed << setprecision(1) << mucPin << "%" << endl;
                }
                return true;
            }
        }
        return false;
    }

    void sacPin() {
        if (mucPin < 100.0) {
            mucPin = min(100.0f, mucPin + 8.0f);
        }
    }

    virtual void hienThiThongTin() const {
        cout << "\n=== " << tenRobot << " ===" << endl;
        cout << "Vị trí: (" << viTriX << "," << viTriY << ") | Pin: " 
             << fixed << setprecision(1) << mucPin << "%" << endl;
    }
};

// ===== LỚP ROBOT HÚT BỤI =====
class RobotHutBui : public Robot {
protected:
    int dungLuongHopBui;
    int buiHienTai;
    int soODaDon;

public:
    RobotHutBui(string ten = "RobotHutBui", int x = 0, int y = 0) 
        : Robot(ten, x, y) {
        dungLuongHopBui = 300;
        buiHienTai = 0;
        soODaDon = 0;
    }

    bool hutBui() {
        if (mucPin >= 4.0) {
            buiHienTai = min(dungLuongHopBui, buiHienTai + 25);
            soODaDon++;
            mucPin -= 4.0;
            return true;
        }
        return false;
    }

    bool canSac() const { return mucPin < 25.0; }
    bool canDoBui() const { return buiHienTai > 250; }
    void doBui() { buiHienTai = 0; }
    int laySoODaDon() const { return soODaDon; }
};

// ===== LỚP ROBOT HỌC TẬP =====
class RobotHocTap : public RobotHutBui {
private:
    BoNhoKinhNghiem boNho;
    CamBienVaCham camBien;
    CheDoHoc cheDoHoc;
    float nguyHiemToiThieu;
    vector<string> lichSuQuyetDinh;

public:
    RobotHocTap(string ten, int x, int y, int dai, int rong) 
        : RobotHutBui(ten, x, y), boNho(dai, rong) {
        cheDoHoc = DANG_HOC;
        nguyHiemToiThieu = 30.0;
    }

    void khoiDongCheDoHoc() {
        cheDoHoc = DANG_HOC;
        cout << "🧠 " << tenRobot << " bắt đầu học tập!" << endl;
    }

    void hocTuVaCham(int x, int y, Huong huongVaCham) {
        if (cheDoHoc == DANG_HOC) {
            boNho.ghiNhoVaCham(x, y, huongVaCham);
            lichSuQuyetDinh.push_back("Va chạm (" + to_string(x) + "," + to_string(y) + ")");
        }
    }

    bool duDoanVatCan(int x, int y) {
        float diemNguyHiem = boNho.layDiemNguyHiem(x, y);
        return diemNguyHiem > nguyHiemToiThieu;
    }

    Huong chonDuongDiAnToan() {
        pair<int,int> viTri = layViTri();
        
        if (cheDoHoc == DANG_HOC || cheDoHoc == DA_HOC) {
            return boNho.goiYHuongDi(viTri.first, viTri.second);
        }
        
        return (Huong)(rand() % 4);
    }

    Huong quetVaQuyetDinh(const vector<vector<LoaiO>>& banDo, int dai, int rong) {
        pair<int,int> viTri = layViTri();
        auto ketQuaQuet = camBien.quetMoiTruong(viTri.first, viTri.second, banDo, dai, rong);
        
        // Chỉ hiển thị radar khi cần thiết
        if (CHI_TIET_OUTPUT) {
            cout << "Radar: B(" << ketQuaQuet[BAC] << ") N(" << ketQuaQuet[NAM] 
                 << ") D(" << ketQuaQuet[DONG] << ") T(" << ketQuaQuet[TAY] << ")" << endl;
        }
        
        return chonDuongDiAnToan();
    }

    void capNhatSauDiChuyen(bool thanhCong, bool vaChammm = false) {
        if (cheDoHoc == DANG_HOC) {
            boNho.giamDanTheoThoiGian();
            
            if (vaChammm) {
                pair<int,int> viTri = layViTri();
                hocTuVaCham(viTri.first, viTri.second, BAC);
            }
        }
    }

    void luuTienTrinh() {
        boNho.xuatKinhNghiem();
        
        ofstream file("learning_progress.txt");
        file << "Tiến trình học tập hoàn thành." << endl;
        file << "Số quyết định: " << lichSuQuyetDinh.size() << endl;
        file.close();
    }

    // ===== THỐNG KÊ RÚT GỌN =====
    void thongKeTomTat() const {
        cout << "Va chạm: " << boNho.laySoLanVaCham() 
             << " | Học: " << fixed << setprecision(1) << boNho.layMucDoHoc() * 100 
             << "% | Dọn: " << soODaDon << " ô" << endl;
    }

    void hienThiThongTin() const override {
        Robot::hienThiThongTin();
        cout << "Học: " << fixed << setprecision(1) << boNho.layMucDoHoc() * 100 
             << "% | Va chạm: " << boNho.laySoLanVaCham() << " lần" << endl;
    }

    CheDoHoc layCheDoHoc() const { return cheDoHoc; }
    float layMucDoHoc() const { return boNho.layMucDoHoc(); }
    int laySoVaCham() const { return boNho.laySoLanVaCham(); }
};

// ===== LỚP PHÒNG =====
class Phong {
private:
    int chieuDai, chieuRong;
    vector<vector<LoaiO>> maTranO;
    pair<int,int> viTriTramSac;
    int soOBan;
    int soVatCan;

public:
    Phong(int dai = 10, int rong = 10) {
        chieuDai = dai;
        chieuRong = rong;
        soOBan = 0;
        soVatCan = 0;
        viTriTramSac = {0, 0};
        khoiTaoPhongTrong();
    }

    void khoiTaoPhongTrong() {
        maTranO = vector<vector<LoaiO>>(chieuRong, vector<LoaiO>(chieuDai, SACH));
        maTranO[0][0] = TRAM_SAC;
        viTriTramSac = {0, 0};
    }

    void themVatCanNgauNhien(int soPhanTram = 15) {
        srand(time(0));
        int soVatCanTaoRa = (chieuDai * chieuRong) * soPhanTram / 100;
        
        cout << "Thêm " << soVatCanTaoRa << " vật cản..." << endl;
        
        for (int i = 0; i < soVatCanTaoRa; i++) {
            int x = rand() % chieuDai;
            int y = rand() % chieuRong;
            
            if ((x != viTriTramSac.first || y != viTriTramSac.second) && 
                maTranO[y][x] != VAT_CAN) {
                datVatCan(x, y);
            }
        }
    }

    void datVatCan(int x, int y) {
        if (kiemTraHopLe(x, y) && maTranO[y][x] != TRAM_SAC) {
            maTranO[y][x] = VAT_CAN;
            soVatCan++;
        }
    }

    void datBuiTaiViTri(int x, int y) {
        if (kiemTraHopLe(x, y) && maTranO[y][x] == SACH) {
            maTranO[y][x] = BAN;
            soOBan++;
            if (CHI_TIET_OUTPUT) {
                cout << "Đặt bụi tại (" << x << "," << y << ")" << endl;
            }
        }
    }

    bool lamSachO(int x, int y) {
        if (kiemTraHopLe(x, y) && maTranO[y][x] == BAN) {
            maTranO[y][x] = SACH;
            soOBan--;
            return true;
        }
        return false;
    }

    bool kiemTraVaCham(int x, int y) {
        return !kiemTraHopLe(x, y) || maTranO[y][x] == VAT_CAN;
    }

    bool kiemTraHopLe(int x, int y) const {
        return (x >= 0 && x < chieuDai && y >= 0 && y < chieuRong);
    }

    LoaiO kiemTraO(int x, int y) const {
        if (!kiemTraHopLe(x, y)) return VAT_CAN;
        return maTranO[y][x];
    }

    // ===== HIỂN THỊ BẢN ĐỒ RÚT GỌN =====
    void hienThiBanDoRutGon(const RobotHocTap& robot) {
        if (!HIEN_THI_BAN_DO_CHI_TIET) {
            cout << "Bản đồ " << chieuDai << "x" << chieuRong 
                 << " | Còn " << soOBan << " ô bẩn | ";
            robot.thongKeTomTat();
            return;
        }
        
        cout << "\n🗺️  BẢN ĐỒ:" << endl;
        for (int y = 0; y < chieuRong; y++) {
            for (int x = 0; x < chieuDai; x++) {
                pair<int,int> robotPos = robot.layViTri();
                
                if (robotPos.first == x && robotPos.second == y) {
                    cout << "🤖";
                } else {
                    switch(maTranO[y][x]) {
                        case SACH: cout << " ·"; break;
                        case BAN: cout << " B"; break;
                        case VAT_CAN: cout << " ■"; break;
                        case TRAM_SAC: cout << " ⚡"; break;
                    }
                }
            }
            cout << endl;
        }
        cout << "Còn " << soOBan << " ô bẩn | ";
        robot.thongKeTomTat();
    }

    int layChieuDai() const { return chieuDai; }
    int layChieuRong() const { return chieuRong; }
    int laySoOBan() const { return soOBan; }
    const vector<vector<LoaiO>>& layMaTranO() const { return maTranO; }
};

// ===== HÀM NHẬP DỮ LIỆU RÚT GỌN =====
void nhapCauHinh(int& dai, int& rong, bool& chiTiet) {
    cout << "🤖 ROBOT HỌC TẬP - TRÁNH VẬT CẢN" << endl;
    cout << "1. Chế độ nhanh (10x8, ít text)" << endl;
    cout << "2. Chế độ chi tiết (tùy chỉnh)" << endl;
    cout << "Chọn (1/2): ";
    
    int chon;
    cin >> chon;
    
    if (chon == 1) {
        dai = 10;
        rong = 8;
        chiTiet = false;
        CHI_TIET_OUTPUT = false;
        HIEN_THI_BAN_DO_CHI_TIET = false;
        BUOC_HIEN_THI = 30;
        cout << "✅ Chế độ nhanh: " << dai << "x" << rong << endl;
    } else {
        cout << "Nhập chiều dài (5-15): ";
        cin >> dai;
        cout << "Nhập chiều rộng (5-12): ";
        cin >> rong;
        
        cout << "Hiển thị chi tiết? (1=Có, 0=Không): ";
        int ct;
        cin >> ct;
        chiTiet = (ct == 1);
        CHI_TIET_OUTPUT = chiTiet;
        HIEN_THI_BAN_DO_CHI_TIET = chiTiet;
        BUOC_HIEN_THI = chiTiet ? 10 : 25;
    }
}

void nhapViTriBanNhanh(Phong& phong) {
    cout << "Thêm bụi ngẫu nhiên (3-8 vị trí)..." << endl;
    int soBui = 3 + rand() % 6;
    
    for (int i = 0; i < soBui; i++) {
        int x = rand() % phong.layChieuDai();
        int y = rand() % phong.layChieuRong();
        phong.datBuiTaiViTri(x, y);
    }
    cout << "✅ Đã thêm " << soBui << " vị trí bẩn" << endl;
}

// ===== THUẬT TOÁN HỌC TẬP RÚT GỌN =====
void chayQuaTrinhHocNhanh(RobotHocTap& robot, Phong& phong) {
    cout << "\n📚 BẮT ĐẦU HỌC TẬP..." << endl;
    
    for (int lanHoc = 1; lanHoc <= 3; lanHoc++) {
        cout << "\n--- Lần học " << lanHoc << "/3 ---" << endl;
        
        robot.datViTri(0, 0);
        robot.datTrangThai(DANG_DON);
        
        int buocDiChuyen = 0;
        int maxBuoc = 40;
        
        while (buocDiChuyen < maxBuoc && !robot.canSac()) {
            buocDiChuyen++;
            pair<int,int> viTriHienTai = robot.layViTri();
            
            Huong huongChon = robot.quetVaQuyetDinh(phong.layMaTranO(), 
                                                    phong.layChieuDai(), 
                                                    phong.layChieuRong());
            
            int dx[] = {0, 0, 1, -1};
            int dy[] = {-1, 1, 0, 0};
            int newX = viTriHienTai.first + dx[huongChon];
            int newY = viTriHienTai.second + dy[huongChon];
            
            if (phong.kiemTraVaCham(newX, newY)) {
                if (CHI_TIET_OUTPUT) {
                    cout << "💥 Va chạm (" << newX << "," << newY << ")" << endl;
                }
                robot.hocTuVaCham(newX, newY, huongChon);
                robot.capNhatSauDiChuyen(false, true);
                
                // Thử hướng khác
                for (int i = 0; i < 4; i++) {
                    if (i != huongChon) {
                        int altX = viTriHienTai.first + dx[i];
                        int altY = viTriHienTai.second + dy[i];
                        if (!phong.kiemTraVaCham(altX, altY)) {
                            robot.diChuyenToi(altX, altY);
                            break;
                        }
                    }
                }
            } else {
                if (robot.diChuyenToi(newX, newY)) {
                    if (phong.kiemTraO(newX, newY) == BAN) {
                        if (robot.hutBui()) {
                            phong.lamSachO(newX, newY);
                            if (CHI_TIET_OUTPUT) {
                                cout << "✨ Hút bụi (" << newX << "," << newY << ")" << endl;
                            }
                        }
                    }
                    robot.capNhatSauDiChuyen(true, false);
                }
            }
            
            // Hiển thị tiến trình định kỳ
            if (buocDiChuyen % BUOC_HIEN_THI == 0) {
                phong.hienThiBanDoRutGon(robot);
            }
        }
        
        cout << "✅ Lần học " << lanHoc << " hoàn thành" << endl;
        robot.thongKeTomTat();
    }
    
    cout << "\n🎓 HỌC TẬP HOÀN THÀNH!" << endl;
    robot.luuTienTrinh();
}

// ===== DEMO ROBOT SAU KHI HỌC =====
void demoRobotNhanh(RobotHocTap& robot, Phong& phong) {
    cout << "\n🚀 DEMO ROBOT ĐÃ HỌC..." << endl;
    
    robot.datViTri(0, 0);
    robot.sacPin();
    robot.datTrangThai(DANG_DON);
    
    int buocDemo = 0;
    int maxBuocDemo = 60;
    
    while (phong.laySoOBan() > 0 && buocDemo < maxBuocDemo && !robot.canSac()) {
        buocDemo++;
        pair<int,int> viTriHienTai = robot.layViTri();
        
        Huong huongChon = robot.quetVaQuyetDinh(phong.layMaTranO(), 
                                                phong.layChieuDai(), 
                                                phong.layChieuRong());
        
        int dx[] = {0, 0, 1, -1};
        int dy[] = {-1, 1, 0, 0};
        int newX = viTriHienTai.first + dx[huongChon];
        int newY = viTriHienTai.second + dy[huongChon];
        
        // Dự đoán va chạm dựa trên kinh nghiệm
        if (robot.duDoanVatCan(newX, newY)) {
            if (CHI_TIET_OUTPUT) {
                cout << "🧠 Dự đoán nguy hiểm (" << newX << "," << newY << "), tránh!" << endl;
            }
            
            // Tìm hướng an toàn khác
            for (int i = 0; i < 4; i++) {
                int altX = viTriHienTai.first + dx[i];
                int altY = viTriHienTai.second + dy[i];
                if (!robot.duDoanVatCan(altX, altY) && !phong.kiemTraVaCham(altX, altY)) {
                    robot.diChuyenToi(altX, altY);
                    if (CHI_TIET_OUTPUT) {
                        cout << "✅ Chọn hướng an toàn" << endl;
                    }
                    break;
                }
            }
        } else if (!phong.kiemTraVaCham(newX, newY)) {
            robot.diChuyenToi(newX, newY);
            
            if (phong.kiemTraO(newX, newY) == BAN) {
                if (robot.hutBui()) {
                    phong.lamSachO(newX, newY);
                    if (CHI_TIET_OUTPUT) {
                        cout << "✨ Hút bụi thành công!" << endl;
                    }
                }
            }
        } else {
            if (CHI_TIET_OUTPUT) {
                cout << "💥 Va chạm không dự đoán được" << endl;
            }
            robot.hocTuVaCham(newX, newY, huongChon);
        }
        
        // Hiển thị tiến trình định kỳ
        if (buocDemo % BUOC_HIEN_THI == 0) {
            phong.hienThiBanDoRutGon(robot);
        }
    }
    
    cout << "\n🏁 DEMO HOÀN THÀNH!" << endl;
    phong.hienThiBanDoRutGon(robot);
}

// ===== BÁO CÁO KẾT QUẢ RÚT GỌN =====
void baoCaoKetQua(const RobotHocTap& robot) {
    cout << "\n📈 === BÁO CÁO TỔNG KẾT ===" << endl;
    robot.hienThiThongTin();
    
    cout << "\n🏆 ĐÁNH GIÁ: ";
    if (robot.layMucDoHoc() > 0.8) {
        cout << "XUẤT SẮC! Robot học rất giỏi!" << endl;
    } else if (robot.layMucDoHoc() > 0.5) {
        cout << "TỐT! Robot có tiến bộ rõ rệt!" << endl;
    } else if (robot.layMucDoHoc() > 0.2) {
        cout << "KHỞI ĐẦU TỐT! Robot đang học dần..." << endl;
    } else {
        cout << "Robot mới bắt đầu học, cần thêm thời gian!" << endl;
    }
    
    cout << "\n💡 KIẾN THỨC ĐÃ HỌC:" << endl;
    cout << "• Ghi nhớ vị trí nguy hiểm: " << robot.laySoVaCham() << " điểm" << endl;
    cout << "• Dự đoán va chạm dựa trên kinh nghiệm" << endl;
    cout << "• Chọn đường đi an toàn hơn" << endl;
    cout << "• Cải thiện hiệu quả dọn dẹp" << endl;
}

// ===== HÀM MAIN =====
int main() {
    srand(time(0));
    
    cout << "🤖🧠 ROBOT HỌC TRÁNH VẬT CẢN" << endl;
    cout << "Robot sẽ học từ kinh nghiệm để tránh va chạm!" << endl;
    
    // 1. NHẬP CẤU HÌNH
    int chieuDai, chieuRong;
    bool chiTiet;
    nhapCauHinh(chieuDai, chieuRong, chiTiet);
    
    // 2. KHỞI TẠO HỆ THỐNG
    Phong phong(chieuDai, chieuRong);
    RobotHocTap robot("SmartBot-AI", 0, 0, chieuDai, chieuRong);
    
    // 3. THIẾT LẬP MÔI TRƯỜNG
    phong.themVatCanNgauNhien(12);
    nhapViTriBanNhanh(phong);
    
    // 4. HIỂN THỊ TRẠNG THÁI BAN ĐẦU
    cout << "\n📊 TRẠNG THÁI BAN ĐẦU:" << endl;
    phong.hienThiBanDoRutGon(robot);
    robot.hienThiThongTin();
    
    // 5. KHỞI ĐỘNG HỌC TẬP
    robot.khoiDongCheDoHoc();
    
    cout << "\nChọn chế độ:" << endl;
    cout << "1. Xem robot học từ đầu" << endl;
    cout << "2. Demo robot đã học (giả lập)" << endl;
    cout << "Chọn (1/2): ";
    
    int luaChon;
    cin >> luaChon;
    
    if (luaChon == 1) {
        // 6. QUÁ TRÌNH HỌC TẬP
        chayQuaTrinhHocNhanh(robot, phong);
        
        // 7. DEMO SAU KHI HỌC
        cout << "\nXem demo robot áp dụng kinh nghiệm? (y/n): ";
        char tiepTuc;
        cin >> tiepTuc;
        if (tiepTuc == 'y' || tiepTuc == 'Y') {
            demoRobotNhanh(robot, phong);
        }
    } else {
        // Demo trực tiếp
        demoRobotNhanh(robot, phong);
    }
    
    // 8. BÁO CÁO KẾT QUẢ
    baoCaoKetQua(robot);
    
    cout << "\n🎮 Cảm ơn bạn đã trải nghiệm Robot AI!" << endl;
    cout << "📁 Dữ liệu học tập đã được lưu vào file." << endl;
    
    cout << "\nNhấn Enter để thoát...";
    cin.ignore();
    cin.get();
    
    return 0;
}