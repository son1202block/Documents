#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <algorithm>
#include <chrono>
#include <thread>
#include <random>
#include <iomanip>

using namespace std;
using namespace std::chrono;

// Enum cho các trạng thái và hướng
enum Huong { BAC = 0, DONG = 1, NAM = 2, TAY = 3 };
enum TrangThaiO { TRONG, TUONG, DA_DI, CHUA_KHAM_PHA, LOI_VAO, LOI_RA };
enum TrangThaiRobot { DANG_KHAM_PHA, DA_TIM_THAY_LOI_RA, DANG_QUAY_LAI, HOAN_THANH };

// Cấu trúc điểm 2D
struct Diem {
    int x, y;
    Diem(int x = 0, int y = 0) : x(x), y(y) {}
    
    bool operator==(const Diem& other) const {
        return x == other.x && y == other.y;
    }
    
    bool operator<(const Diem& other) const {
        return x < other.x || (x == other.x && y < other.y);
    }
    
    string toString() const {
        return "(" + to_string(x) + "," + to_string(y) + ")";
    }
};

// Lớp Mê Cung
class MeCung {
private:
    int chieuRong, chieuCao;
    Diem loiVao, loiRa;
    vector<vector<TrangThaiO>> maTranTuong;
    vector<vector<bool>> daKhamPha;
    vector<vector<int>> khoangCach;

public:
    MeCung(int rong, int cao) : chieuRong(rong), chieuCao(cao) {
        maTranTuong.resize(cao, vector<TrangThaiO>(rong, TRONG));
        daKhamPha.resize(cao, vector<bool>(rong, false));
        khoangCach.resize(cao, vector<int>(rong, -1));
        
        // Tạo tường xung quanh
        taoTuongXungQuanh();
        
        // Đặt lối vào và lối ra mặc định
        loiVao = Diem(1, 1);
        loiRa = Diem(rong - 2, cao - 2);
        maTranTuong[loiVao.y][loiVao.x] = LOI_VAO;
        maTranTuong[loiRa.y][loiRa.x] = LOI_RA;
    }

    void taoTuongXungQuanh() {
        // Tường trên và dưới
        for (int x = 0; x < chieuRong; x++) {
            maTranTuong[0][x] = TUONG;
            maTranTuong[chieuCao - 1][x] = TUONG;
        }
        
        // Tường trái và phải
        for (int y = 0; y < chieuCao; y++) {
            maTranTuong[y][0] = TUONG;
            maTranTuong[y][chieuRong - 1] = TUONG;
        }
    }

    void taoTuongNgauNhien(float tyLeTuong = 0.3f) {
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<float> dis(0.0f, 1.0f);
        
        for (int y = 1; y < chieuCao - 1; y++) {
            for (int x = 1; x < chieuRong - 1; x++) {
                if (maTranTuong[y][x] != LOI_VAO && maTranTuong[y][x] != LOI_RA) {
                    if (dis(gen) < tyLeTuong) {
                        maTranTuong[y][x] = TUONG;
                    }
                }
            }
        }
    }

    void taoMeCungMau() {
        // Tạo mê cung mẫu với đường đi rõ ràng
        vector<vector<int>> mau = {
            {1,1,1,1,1,1,1,1,1,1},
            {1,0,0,1,0,0,0,1,0,1},
            {1,0,1,1,0,1,0,1,0,1},
            {1,0,0,0,0,1,0,0,0,1},
            {1,1,1,0,1,1,1,1,0,1},
            {1,0,0,0,0,0,0,0,0,1},
            {1,0,1,1,1,1,1,1,0,1},
            {1,0,0,0,0,0,0,0,0,1},
            {1,1,1,1,1,1,1,1,0,1},
            {1,1,1,1,1,1,1,1,1,1}
        };
        
        for (int y = 0; y < chieuCao && y < mau.size(); y++) {
            for (int x = 0; x < chieuRong && x < mau[y].size(); x++) {
                if (mau[y][x] == 1) {
                    maTranTuong[y][x] = TUONG;
                } else {
                    maTranTuong[y][x] = TRONG;
                }
            }
        }
        
        loiVao = Diem(1, 1);
        loiRa = Diem(8, 8);
        maTranTuong[loiVao.y][loiVao.x] = LOI_VAO;
        maTranTuong[loiRa.y][loiRa.x] = LOI_RA;
    }

    bool hopLe(Diem diem) const {
        return diem.x >= 0 && diem.x < chieuRong && 
               diem.y >= 0 && diem.y < chieuCao;
    }

    bool coTuong(Diem diem) const {
        return !hopLe(diem) || maTranTuong[diem.y][diem.x] == TUONG;
    }

    bool coTheDi(Diem diem) const {
        return hopLe(diem) && !coTuong(diem);
    }

    void danhDauDaKhamPha(Diem diem) {
        if (hopLe(diem)) {
            daKhamPha[diem.y][diem.x] = true;
        }
    }

    bool daKhamPhaO(Diem diem) const {
        return hopLe(diem) && daKhamPha[diem.y][diem.x];
    }

    Diem layLoiVao() const { return loiVao; }
    Diem layLoiRa() const { return loiRa; }
    int layChieuRong() const { return chieuRong; }
    int layChieuCao() const { return chieuCao; }
    TrangThaiO layTrangThai(Diem diem) const {
        return hopLe(diem) ? maTranTuong[diem.y][diem.x] : TUONG;
    }

    void inMeCung() const {
        cout << "\n=== ME CUNG ===" << endl;
        for (int y = 0; y < chieuCao; y++) {
            for (int x = 0; x < chieuRong; x++) {
                switch (maTranTuong[y][x]) {
                    case TUONG: cout << "#"; break;
                    case TRONG: cout << " "; break;
                    case DA_DI: cout << "."; break;
                    case LOI_VAO: cout << "S"; break;
                    case LOI_RA: cout << "E"; break;
                    default: cout << "?"; break;
                }
            }
            cout << endl;
        }
    }

    void inMeCungVoiDuongDi(const vector<Diem>& duongDi) const {
        cout << "\n=== ME CUNG VOI DUONG DI ===" << endl;
        vector<vector<char>> hienThi(chieuCao, vector<char>(chieuRong, ' '));
        
        // Vẽ mê cung
        for (int y = 0; y < chieuCao; y++) {
            for (int x = 0; x < chieuRong; x++) {
                switch (maTranTuong[y][x]) {
                    case TUONG: hienThi[y][x] = '#'; break;
                    case LOI_VAO: hienThi[y][x] = 'S'; break;
                    case LOI_RA: hienThi[y][x] = 'E'; break;
                    default: hienThi[y][x] = ' '; break;
                }
            }
        }
        
        // Vẽ đường đi
        for (const auto& diem : duongDi) {
            if (hopLe(diem) && hienThi[diem.y][diem.x] == ' ') {
                hienThi[diem.y][diem.x] = '.';
            }
        }
        
        // In ra
        for (int y = 0; y < chieuCao; y++) {
            for (int x = 0; x < chieuRong; x++) {
                cout << hienThi[y][x];
            }
            cout << endl;
        }
    }
};

// Lớp Cảm Biến Xe
class CamBienXe {
private:
    MeCung* meCung;
    Diem viTriHienTai;
    Huong huongHienTai;

public:
    CamBienXe(MeCung* mc) : meCung(mc), viTriHienTai(mc->layLoiVao()), huongHienTai(BAC) {}

    void capNhatViTri(Diem viTri, Huong huong) {
        viTriHienTai = viTri;
        huongHienTai = huong;
    }

    Diem layViTriHienTai() const { return viTriHienTai; }
    Huong layHuongHienTai() const { return huongHienTai; }

    // Cảm biến phía trước
    bool coTuongPhiaTruoc() const {
        Diem diemTruoc = layDiemPhiaTruoc();
        return meCung->coTuong(diemTruoc);
    }

    // Cảm biến bên trái
    bool coTuongBenTrai() const {
        Diem diemTrai = layDiemBenTrai();
        return meCung->coTuong(diemTrai);
    }

    // Cảm biến bên phải
    bool coTuongBenPhai() const {
        Diem diemPhai = layDiemBenPhai();
        return meCung->coTuong(diemPhai);
    }

    // Cảm biến khoảng cách (số ô trống phía trước)
    int layKhoangCachPhiaTruoc() const {
        int khoangCach = 0;
        Diem diemHienTai = viTriHienTai;
        
        while (true) {
            Diem diemTruoc = layDiemPhiaTruocTuDiem(diemHienTai);
            if (meCung->coTuong(diemTruoc)) {
                break;
            }
            khoangCach++;
            diemHienTai = diemTruoc;
        }
        
        return khoangCach;
    }

    // Quét môi trường xung quanh
    map<string, bool> quetMoiTruong() const {
        map<string, bool> ketQua;
        ketQua["truoc"] = coTuongPhiaTruoc();
        ketQua["trai"] = coTuongBenTrai();
        ketQua["phai"] = coTuongBenPhai();
        ketQua["sau"] = coTuongPhiaSau();
        return ketQua;
    }

    // Kiểm tra có phải lối ra không
    bool laLoiRa() const {
        return meCung->layTrangThai(viTriHienTai) == LOI_RA;
    }

private:
    Diem layDiemPhiaTruoc() const {
        return layDiemPhiaTruocTuDiem(viTriHienTai);
    }

    Diem layDiemPhiaTruocTuDiem(Diem diem) const {
        switch (huongHienTai) {
            case BAC: return Diem(diem.x, diem.y - 1);
            case DONG: return Diem(diem.x + 1, diem.y);
            case NAM: return Diem(diem.x, diem.y + 1);
            case TAY: return Diem(diem.x - 1, diem.y);
            default: return diem;
        }
    }

    Diem layDiemBenTrai() const {
        switch (huongHienTai) {
            case BAC: return Diem(viTriHienTai.x - 1, viTriHienTai.y);
            case DONG: return Diem(viTriHienTai.x, viTriHienTai.y - 1);
            case NAM: return Diem(viTriHienTai.x + 1, viTriHienTai.y);
            case TAY: return Diem(viTriHienTai.x, viTriHienTai.y + 1);
            default: return viTriHienTai;
        }
    }

    Diem layDiemBenPhai() const {
        switch (huongHienTai) {
            case BAC: return Diem(viTriHienTai.x + 1, viTriHienTai.y);
            case DONG: return Diem(viTriHienTai.x, viTriHienTai.y + 1);
            case NAM: return Diem(viTriHienTai.x - 1, viTriHienTai.y);
            case TAY: return Diem(viTriHienTai.x, viTriHienTai.y - 1);
            default: return viTriHienTai;
        }
    }

    bool coTuongPhiaSau() const {
        switch (huongHienTai) {
            case BAC: return meCung->coTuong(Diem(viTriHienTai.x, viTriHienTai.y + 1));
            case DONG: return meCung->coTuong(Diem(viTriHienTai.x - 1, viTriHienTai.y));
            case NAM: return meCung->coTuong(Diem(viTriHienTai.x, viTriHienTai.y - 1));
            case TAY: return meCung->coTuong(Diem(viTriHienTai.x + 1, viTriHienTai.y));
            default: return true;
        }
    }
};

// Lớp Bản Đồ Tạm Thời
class BanDoTamThoi {
private:
    MeCung* meCung;
    map<Diem, bool> daKhamPha;
    map<Diem, int> khoangCachTuLoiVao;
    map<Diem, Diem> chaCuaDiem;
    vector<Diem> duongDiHienTai;
    stack<Diem> nganXepQuayLai;

public:
    BanDoTamThoi(MeCung* mc) : meCung(mc) {
        // Khởi tạo với lối vào
        Diem loiVao = meCung->layLoiVao();
        daKhamPha[loiVao] = true;
        khoangCachTuLoiVao[loiVao] = 0;
        duongDiHienTai.push_back(loiVao);
        nganXepQuayLai.push(loiVao);
    }

    void capNhatBanDo(Diem viTri, const map<string, bool>& thongTinCamBien) {
        daKhamPha[viTri] = true;
        
        // Cập nhật thông tin về các ô xung quanh
        vector<Diem> cacO = {
            Diem(viTri.x, viTri.y - 1), // Bắc
            Diem(viTri.x + 1, viTri.y), // Đông
            Diem(viTri.x, viTri.y + 1), // Nam
            Diem(viTri.x - 1, viTri.y)  // Tây
        };
        
        for (const auto& o : cacO) {
            if (meCung->hopLe(o) && !meCung->coTuong(o)) {
                if (daKhamPha.find(o) == daKhamPha.end()) {
                    daKhamPha[o] = false; // Chưa khám phá
                }
            }
        }
    }

    void themVaoDuongDi(Diem diem) {
        if (!duongDiHienTai.empty() && duongDiHienTai.back() == diem) {
            return; // Đã có trong đường đi
        }
        
        duongDiHienTai.push_back(diem);
        
        // Cập nhật khoảng cách
        if (duongDiHienTai.size() > 1) {
            Diem diemTruoc = duongDiHienTai[duongDiHienTai.size() - 2];
            khoangCachTuLoiVao[diem] = khoangCachTuLoiVao[diemTruoc] + 1;
            chaCuaDiem[diem] = diemTruoc;
        }
    }

    void quayLai() {
        if (duongDiHienTai.size() > 1) {
            duongDiHienTai.pop_back();
        }
    }

    Diem timOChuaKhamPhaGanNhat(Diem tuViTri) const {
        queue<Diem> hangDoi;
        set<Diem> daTham;
        
        hangDoi.push(tuViTri);
        daTham.insert(tuViTri);
        
        while (!hangDoi.empty()) {
            Diem hienTai = hangDoi.front();
            hangDoi.pop();
            
            // Kiểm tra các ô xung quanh
            vector<Diem> cacO = {
                Diem(hienTai.x, hienTai.y - 1),
                Diem(hienTai.x + 1, hienTai.y),
                Diem(hienTai.x, hienTai.y + 1),
                Diem(hienTai.x - 1, hienTai.y)
            };
            
            for (const auto& o : cacO) {
                if (meCung->hopLe(o) && !meCung->coTuong(o) && 
                    daTham.find(o) == daTham.end()) {
                    
                    auto it = daKhamPha.find(o);
                    if (it == daKhamPha.end() || !it->second) {
                        return o; // Tìm thấy ô chưa khám phá
                    }
                    
                    hangDoi.push(o);
                    daTham.insert(o);
                }
            }
        }
        
        return Diem(-1, -1); // Không tìm thấy
    }

    vector<Diem> timDuongNganNhat(Diem tuDiem, Diem denDiem) const {
        queue<Diem> hangDoi;
        map<Diem, Diem> cha;
        map<Diem, bool> daTham;
        
        hangDoi.push(tuDiem);
        daTham[tuDiem] = true;
        
        while (!hangDoi.empty()) {
            Diem hienTai = hangDoi.front();
            hangDoi.pop();
            
            if (hienTai == denDiem) {
                // Tìm thấy đường đi, tái tạo đường
                vector<Diem> duongDi;
                Diem diem = denDiem;
                
                while (!(diem == tuDiem)) {
                    duongDi.push_back(diem);
                    diem = cha.at(diem);
                }
                duongDi.push_back(tuDiem);
                reverse(duongDi.begin(), duongDi.end());
                return duongDi;
            }
            
            // Thêm các ô kề vào hàng đợi
            vector<Diem> cacO = {
                Diem(hienTai.x, hienTai.y - 1),
                Diem(hienTai.x + 1, hienTai.y),
                Diem(hienTai.x, hienTai.y + 1),
                Diem(hienTai.x - 1, hienTai.y)
            };
            
            for (const auto& o : cacO) {
                if (meCung->hopLe(o) && !meCung->coTuong(o) && 
                    daTham.find(o) == daTham.end()) {
                    
                    hangDoi.push(o);
                    daTham[o] = true;
                    cha[o] = hienTai;
                }
            }
        }
        
        return vector<Diem>(); // Không tìm thấy đường
    }

    void inBanDoTamThoi() const {
        cout << "\n=== BAN DO TAM THOI ===" << endl;
        cout << "Da kham pha: " << daKhamPha.size() << " o" << endl;
        cout << "Duong di hien tai: " << duongDiHienTai.size() << " buoc" << endl;
        
        cout << "Duong di: ";
        for (size_t i = 0; i < duongDiHienTai.size(); i++) {
            cout << duongDiHienTai[i].toString();
            if (i < duongDiHienTai.size() - 1) cout << " -> ";
        }
        cout << endl;
    }

    vector<Diem> layDuongDiHienTai() const { return duongDiHienTai; }
    int laySoODaKhamPha() const { return daKhamPha.size(); }
    bool daKhamPhaO(Diem diem) const {
        auto it = daKhamPha.find(diem);
        return it != daKhamPha.end() && it->second;
    }
};

// Lớp Xe Robot Tự Lái
class XeRobotTuLai {
private:
    MeCung* meCung;
    CamBienXe camBien;
    BanDoTamThoi banDoTamThoi;
    Diem viTriHienTai;
    Huong huongHienTai;
    TrangThaiRobot trangThai;
    int soBuocDi;
    vector<Diem> duongDiToiUu;
    bool daTimThayLoiRaFlag;

public:
    XeRobotTuLai(MeCung* mc) : meCung(mc), camBien(mc), banDoTamThoi(mc),
                               viTriHienTai(mc->layLoiVao()), huongHienTai(BAC),
                               trangThai(DANG_KHAM_PHA), soBuocDi(0), daTimThayLoiRaFlag(false) {
        camBien.capNhatViTri(viTriHienTai, huongHienTai);
        banDoTamThoi.capNhatBanDo(viTriHienTai, camBien.quetMoiTruong());
    }

    // Thuật toán luật tay phải
    void thuatToanLuatTayPhai() {
        cout << "\n=== BAT DAU THUAT TOAN LUAT TAY PHAI ===" << endl;
        
        while (trangThai != HOAN_THANH) {
            inTrangThaiHienTai();
            
            if (camBien.laLoiRa()) {
                trangThai = DA_TIM_THAY_LOI_RA;
                cout << "🎉 DA TIM THAY LOI RA!" << endl;
                break;
            }
            
            // Quét môi trường
            auto thongTinCamBien = camBien.quetMoiTruong();
            banDoTamThoi.capNhatBanDo(viTriHienTai, thongTinCamBien);
            
            // Áp dụng luật tay phải
            Huong huongTiepTheo = quyetDinhHuongLuatTayPhai(thongTinCamBien);
            
            if (huongTiepTheo != huongHienTai) {
                quayHuong(huongTiepTheo);
            }
            
            if (coTheDiThang()) {
                diChuyenThang();
            } else {
                // Gặp đường cụt, cần quay lại
                trangThai = DANG_QUAY_LAI;
                quayLai();
            }
            
            this_thread::sleep_for(milliseconds(500)); // Tạm dừng để quan sát
        }
        
        if (trangThai == DA_TIM_THAY_LOI_RA) {
            timDuongToiUu();
        }
    }

    // Thuật toán khám phá toàn bộ
    void thuatToanKhamPhaToanBo() {
        cout << "\n=== BAT DAU THUAT TOAN KHAM PHA TOAN BO ===" << endl;
        
        while (trangThai != HOAN_THANH) {
            inTrangThaiHienTai();
            
            if (camBien.laLoiRa()) {
                trangThai = DA_TIM_THAY_LOI_RA;
                cout << "🎉 DA TIM THAY LOI RA!" << endl;
                break;
            }
            
            // Quét môi trường
            auto thongTinCamBien = camBien.quetMoiTruong();
            banDoTamThoi.capNhatBanDo(viTriHienTai, thongTinCamBien);
            
            // Tìm ô chưa khám phá gần nhất
            Diem oChuaKhamPha = banDoTamThoi.timOChuaKhamPhaGanNhat(viTriHienTai);
            
            if (oChuaKhamPha.x == -1) {
                // Không còn ô nào chưa khám phá
                cout << "Da kham pha het me cung!" << endl;
                trangThai = HOAN_THANH;
                break;
            }
            
            // Tìm đường đến ô chưa khám phá
            vector<Diem> duongDenO = banDoTamThoi.timDuongNganNhat(viTriHienTai, oChuaKhamPha);
            
            if (!duongDenO.empty()) {
                // Di chuyển theo đường đã tìm
                for (size_t i = 1; i < duongDenO.size(); i++) {
                    diChuyenDenDiem(duongDenO[i]);
                    this_thread::sleep_for(milliseconds(300));
                }
            }
            
            this_thread::sleep_for(milliseconds(500));
        }
        
        if (trangThai == DA_TIM_THAY_LOI_RA) {
            timDuongToiUu();
        }
    }

    // Quyết định hướng đi theo luật tay phải
    Huong quyetDinhHuongLuatTayPhai(const map<string, bool>& thongTinCamBien) {
        // Luật tay phải: Ưu tiên rẽ phải, đi thẳng, rẽ trái, quay lại
        if (!thongTinCamBien.at("phai")) {
            return quayPhai(huongHienTai);
        } else if (!thongTinCamBien.at("truoc")) {
            return huongHienTai; // Đi thẳng
        } else if (!thongTinCamBien.at("trai")) {
            return quayTrai(huongHienTai);
        } else {
            return quayNguoc(huongHienTai); // Quay lại
        }
    }

    // Di chuyển
    void diChuyenThang() {
        Diem diemTruoc = layDiemPhiaTruoc();
        if (meCung->coTheDi(diemTruoc)) {
            viTriHienTai = diemTruoc;
            soBuocDi++;
            banDoTamThoi.themVaoDuongDi(viTriHienTai);
            camBien.capNhatViTri(viTriHienTai, huongHienTai);
            
            cout << "Di chuyen den: " << viTriHienTai.toString() << endl;
        }
    }

    void diChuyenDenDiem(Diem diem) {
        // Tính hướng cần quay để đến điểm đích
        Huong huongCanQuay = tinhHuongDenDiem(viTriHienTai, diem);
        
        if (huongCanQuay != huongHienTai) {
            quayHuong(huongCanQuay);
        }
        
        viTriHienTai = diem;
        soBuocDi++;
        banDoTamThoi.themVaoDuongDi(viTriHienTai);
        camBien.capNhatViTri(viTriHienTai, huongHienTai);
        
        cout << "Di chuyen den: " << viTriHienTai.toString() << endl;
    }

    bool coTheDiThang() const {
        return !camBien.coTuongPhiaTruoc();
    }

    void quayHuong(Huong huongMoi) {
        if (huongMoi != huongHienTai) {
            cout << "Quay tu " << layTenHuong(huongHienTai) 
                 << " sang " << layTenHuong(huongMoi) << endl;
            huongHienTai = huongMoi;
            camBien.capNhatViTri(viTriHienTai, huongHienTai);
        }
    }

    void quayLai() {
        if (banDoTamThoi.layDuongDiHienTai().size() > 1) {
            banDoTamThoi.quayLai();
            viTriHienTai = banDoTamThoi.layDuongDiHienTai().back();
            camBien.capNhatViTri(viTriHienTai, huongHienTai);
            cout << "Quay lai den: " << viTriHienTai.toString() << endl;
        }
    }

    void timDuongToiUu() {
        cout << "\n=== TIM DUONG TOI UU ===" << endl;
        Diem loiVao = meCung->layLoiVao();
        Diem loiRa = meCung->layLoiRa();
        
        duongDiToiUu = banDoTamThoi.timDuongNganNhat(loiVao, loiRa);
        
        if (!duongDiToiUu.empty()) {
            cout << "Tim thay duong toi uu voi " << duongDiToiUu.size() << " buoc:" << endl;
            for (size_t i = 0; i < duongDiToiUu.size(); i++) {
                cout << duongDiToiUu[i].toString();
                if (i < duongDiToiUu.size() - 1) cout << " -> ";
            }
            cout << endl;
        } else {
            cout << "Khong tim thay duong toi uu!" << endl;
        }
    }

    // Báo cáo kết quả
    void baoCaoKetQua() {
        cout << "\n=== BAO CAO KET QUA ===" << endl;
        cout << "Trang thai: " << layTenTrangThai(trangThai) << endl;
        cout << "Vi tri hien tai: " << viTriHienTai.toString() << endl;
        cout << "Huong hien tai: " << layTenHuong(huongHienTai) << endl;
        cout << "So buoc da di: " << soBuocDi << endl;
        cout << "So o da kham pha: " << banDoTamThoi.laySoODaKhamPha() << endl;
        
        if (daTimThayLoiRaFlag) {
            cout << "Da tim thay loi ra!" << endl;
            if (!duongDiToiUu.empty()) {
                cout << "Duong toi uu co " << duongDiToiUu.size() << " buoc" << endl;
            }
        } else {
            cout << "Chua tim thay loi ra" << endl;
        }
        
        banDoTamThoi.inBanDoTamThoi();
    }

    void inTrangThaiHienTai() {
        cout << "\n--- Trang thai hien tai ---" << endl;
        cout << "Vi tri: " << viTriHienTai.toString() 
             << ", Huong: " << layTenHuong(huongHienTai) << endl;
        
        auto thongTinCamBien = camBien.quetMoiTruong();
        cout << "Cam bien - Truoc: " << (thongTinCamBien.at("truoc") ? "Tuong" : "Trong")
             << ", Trai: " << (thongTinCamBien.at("trai") ? "Tuong" : "Trong")
             << ", Phai: " << (thongTinCamBien.at("phai") ? "Tuong" : "Trong") << endl;
    }

    // Getters
    Diem layViTriHienTai() const { return viTriHienTai; }
    Huong layHuongHienTai() const { return huongHienTai; }
    TrangThaiRobot layTrangThai() const { return trangThai; }
    int laySoBuocDi() const { return soBuocDi; }
    vector<Diem> layDuongDiToiUu() const { return duongDiToiUu; }
    bool daTimThayLoiRa() const { return daTimThayLoiRaFlag; }

private:
    Diem layDiemPhiaTruoc() const {
        switch (huongHienTai) {
            case BAC: return Diem(viTriHienTai.x, viTriHienTai.y - 1);
            case DONG: return Diem(viTriHienTai.x + 1, viTriHienTai.y);
            case NAM: return Diem(viTriHienTai.x, viTriHienTai.y + 1);
            case TAY: return Diem(viTriHienTai.x - 1, viTriHienTai.y);
            default: return viTriHienTai;
        }
    }

    Huong tinhHuongDenDiem(Diem tuDiem, Diem denDiem) const {
        int dx = denDiem.x - tuDiem.x;
        int dy = denDiem.y - tuDiem.y;
        
        if (dx > 0) return DONG;
        if (dx < 0) return TAY;
        if (dy > 0) return NAM;
        if (dy < 0) return BAC;
        
        return huongHienTai; // Không thay đổi nếu cùng vị trí
    }

    Huong quayPhai(Huong huong) const {
        return static_cast<Huong>((huong + 1) % 4);
    }

    Huong quayTrai(Huong huong) const {
        return static_cast<Huong>((huong + 3) % 4);
    }

    Huong quayNguoc(Huong huong) const {
        return static_cast<Huong>((huong + 2) % 4);
    }

    string layTenHuong(Huong huong) const {
        switch (huong) {
            case BAC: return "Bac";
            case DONG: return "Dong";
            case NAM: return "Nam";
            case TAY: return "Tay";
            default: return "Khong xac dinh";
        }
    }

    string layTenTrangThai(TrangThaiRobot trangThai) const {
        switch (trangThai) {
            case DANG_KHAM_PHA: return "Dang kham pha";
            case DA_TIM_THAY_LOI_RA: return "Da tim thay loi ra";
            case DANG_QUAY_LAI: return "Dang quay lai";
            case HOAN_THANH: return "Hoan thanh";
            default: return "Khong xac dinh";
        }
    }
};

// Hàm main để test
int main() {
    cout << "=== HE THONG XE ROBOT TU LAI TRONG ME CUNG ===" << endl;
    
    // Tạo mê cung
    MeCung meCung(10, 10);
    meCung.taoMeCungMau();
    meCung.inMeCung();
    
    cout << "\nLoi vao: " << meCung.layLoiVao().toString() << endl;
    cout << "Loi ra: " << meCung.layLoiRa().toString() << endl;
    
    // Tạo robot
    XeRobotTuLai robot(&meCung);
    
    cout << "\n=== TEST THUAT TOAN LUAT TAY PHAI ===" << endl;
    robot.thuatToanLuatTayPhai();
    robot.baoCaoKetQua();
    
    // Hiển thị đường đi tối ưu
    auto duongDiToiUu = robot.layDuongDiToiUu();
    if (!duongDiToiUu.empty()) {
        meCung.inMeCungVoiDuongDi(duongDiToiUu);
    }
    
    cout << "\n=== TEST THUAT TOAN KHAM PHA TOAN BO ===" << endl;
    // Reset robot cho test thứ 2
    XeRobotTuLai robot2(&meCung);
    robot2.thuatToanKhamPhaToanBo();
    robot2.baoCaoKetQua();
    
    cout << "\n=== KET THUC CHUONG TRINH ===" << endl;
    cout << "Da hoan thanh tat ca cac test!" << endl;
    
    return 0;
}
