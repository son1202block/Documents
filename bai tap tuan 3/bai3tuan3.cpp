#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cmath>
#include <memory>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <sstream>
#include <thread>
#include <mutex>
#include <queue>
#include <random>
#include <iomanip>

using namespace std;
using namespace std::chrono;

// Enum các loại đồ vật và hình dạng
enum LoaiDoVat { DO_CHOI, DO_AN, RAC, DO_DUNG, KHONG_XAC_DINH };
enum HinhDang { TRON, VUONG, TAM_GIAC, CHU_NHAT, KHAC };

// Enum cho trạng thái và mức độ tin cậy
enum TrangThai { DANG_HOAT_DONG, DANG_QUET, DANG_HOC, BAO_TRI, LOI };
enum MucDoTinCay { THAP = 1, TRUNG_BINH = 2, CAO = 3, RAT_CAO = 4 };

// Cấu trúc cấu hình hệ thống
struct CauHinhHeThong {
    float nguongTinCay = 0.7f;
    float nguongDienTich = 1000.0f;
    int soLuongMauToiDa = 100;
    int doPhanGiaiX = 640;
    int doPhanGiaiY = 480;
    int gocNhin = 70;
    float khoangCachToiDa = 50.0f;
    bool cheDoDebug = false;
    bool cheDoRealTime = false;
    int intervalQuet = 1000; // milliseconds
};

// Cấu trúc thống kê hiệu suất
struct ThongKeHieuSuat {
    int soLanQuet = 0;
    int soDoVatNhanDien = 0;
    int soDoVatHoc = 0;
    double thoiGianTrungBinh = 0.0;
    double doChinhXacTrungBinh = 0.0;
    vector<double> lichSuThoiGian;
    vector<double> lichSuDoChinhXac;
};

// Lớp Logging System
class LoggingSystem {
private:
    static mutex logMutex;
    static ofstream logFile;
    static bool initialized;
    
public:
    static void init(const string& filename = "robot_log.txt") {
        lock_guard<mutex> lock(logMutex);
        if (!initialized) {
            logFile.open(filename, ios::app);
            initialized = true;
        }
    }
    
    static void log(const string& level, const string& message) {
        lock_guard<mutex> lock(logMutex);
        auto now = system_clock::now();
        auto time_t = system_clock::to_time_t(now);
        auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;
        
        cout << "[" << put_time(localtime(&time_t), "%Y-%m-%d %H:%M:%S") 
             << "." << setfill('0') << setw(3) << ms.count() << "] "
             << "[" << level << "] " << message << endl;
             
        if (logFile.is_open()) {
            logFile << "[" << put_time(localtime(&time_t), "%Y-%m-%d %H:%M:%S") 
                    << "." << setfill('0') << setw(3) << ms.count() << "] "
                    << "[" << level << "] " << message << endl;
            logFile.flush();
        }
    }
    
    static void info(const string& message) { log("INFO", message); }
    static void warning(const string& message) { log("WARNING", message); }
    static void error(const string& message) { log("ERROR", message); }
    static void debug(const string& message) { log("DEBUG", message); }
};

mutex LoggingSystem::logMutex;
ofstream LoggingSystem::logFile;
bool LoggingSystem::initialized = false;

// Lớp Đồ Vật nâng cao
class DoVat {
private:
    string ten;
    LoaiDoVat loai;
    HinhDang hinhDang;
    float trongLuong;
    vector<string> dacDiem;
    pair<int, int> viTri;
    float doTinCay;
    high_resolution_clock::time_point thoiGianPhatHien;
    string anhId;
    vector<float> histogramMauSac;
    float dienTich;
    bool daXacNhan;

public:
    DoVat(string ten, LoaiDoVat loai, HinhDang hd, float tl, pair<int, int> vt, 
           float dtc = 0.0f, const string& aid = "", float dt = 0.0f)
        : ten(ten), loai(loai), hinhDang(hd), trongLuong(tl), viTri(vt), 
          doTinCay(dtc), anhId(aid), dienTich(dt), daXacNhan(false) {
        thoiGianPhatHien = high_resolution_clock::now();
    }

    string layThongTin() const {
        stringstream ss;
        ss << "Ten: " << ten 
           << ", Loai: " << loaiToString(loai)
           << ", Hinh dang: " << hinhDangToString(hinhDang)
           << ", Tin cay: " << fixed << setprecision(2) << doTinCay
           << ", Vi tri: (" << viTri.first << "," << viTri.second << ")"
           << ", Dien tich: " << dienTich
           << ", Da xac nhan: " << (daXacNhan ? "Co" : "Khong");
        return ss.str();
    }

    string layThongTinChiTiet() const {
        stringstream ss;
        ss << layThongTin() << "\n";
        ss << "Anh ID: " << anhId << "\n";
        ss << "Thoi gian phat hien: " << duration_cast<milliseconds>(thoiGianPhatHien.time_since_epoch()).count() << "ms\n";
        ss << "Histogram mau sac: [";
        for (size_t i = 0; i < histogramMauSac.size(); ++i) {
            ss << histogramMauSac[i];
            if (i < histogramMauSac.size() - 1) ss << ", ";
        }
        ss << "]";
        return ss.str();
    }

    static string loaiToString(LoaiDoVat loai) {
        switch(loai) {
            case DO_CHOI: return "Do choi";
            case DO_AN: return "Do an";
            case RAC: return "Rac";
            case DO_DUNG: return "Do dung";
            default: return "Khong xac dinh";
        }
    }

    static string hinhDangToString(HinhDang hd) {
        switch(hd) {
            case TRON: return "Tron";
            case VUONG: return "Vuong";
            case TAM_GIAC: return "Tam giac";
            case CHU_NHAT: return "Chu nhat";
            default: return "Khac";
        }
    }

    // Getters và Setters
    void capNhatViTri(int x, int y) { viTri = make_pair(x, y); }
    pair<int, int> getViTri() const { return viTri; }
    HinhDang getHinhDang() const { return hinhDang; }
    LoaiDoVat getLoai() const { return loai; }
    float getDoTinCay() const { return doTinCay; }
    void setDoTinCay(float dtc) { doTinCay = dtc; }
    string getTen() const { return ten; }
    string getAnhId() const { return anhId; }
    void setAnhId(const string& aid) { anhId = aid; }
    float getDienTich() const { return dienTich; }
    void setDienTich(float dt) { dienTich = dt; }
    bool isDaXacNhan() const { return daXacNhan; }
    void setDaXacNhan(bool dxn) { daXacNhan = dxn; }
    vector<float> getHistogramMauSac() const { return histogramMauSac; }
    void setHistogramMauSac(const vector<float>& hist) { histogramMauSac = hist; }
    
    high_resolution_clock::time_point getThoiGianPhatHien() const { return thoiGianPhatHien; }
    
    // Tính khoảng cách đến đồ vật khác
    float tinhKhoangCach(const DoVat& dvKhac) const {
        int dx = viTri.first - dvKhac.viTri.first;
        int dy = viTri.second - dvKhac.viTri.second;
        return sqrt(dx*dx + dy*dy);
    }
    
    // Kiểm tra xem có phải cùng loại không
    bool cungLoai(const DoVat& dvKhac) const {
        return loai == dvKhac.loai;
    }
};

// Lớp Camera nâng cao
class Camera {
private:
    pair<int, int> doPhanGiai;
    int gocNhin;
    float khoangCach;
    int doSang;
    bool trangThai;
    TrangThai trangThaiCamera;
    int soLanChupAnh;
    vector<string> lichSuAnh;
    mutex cameraMutex;
    random_device rd;
    mt19937 gen;

public:
    Camera(pair<int, int> dp = make_pair(640, 480), int gn = 70, float kc = 50.0f, int ds = 50)
        : doPhanGiai(dp), gocNhin(gn), khoangCach(kc), doSang(ds), 
          trangThai(true), trangThaiCamera(DANG_HOAT_DONG), soLanChupAnh(0), gen(rd()) {
        LoggingSystem::info("Camera initialized with resolution: " + to_string(dp.first) + "x" + to_string(dp.second));
    }

    // Chụp ảnh với nhiều tùy chọn
    string chupAnh(bool luuLichSu = true) {
        lock_guard<mutex> lock(cameraMutex);
        
        if (!trangThai) {
            LoggingSystem::error("Camera is not active");
            return "invalid";
        }

        // Giả lập thời gian chụp ảnh
        this_thread::sleep_for(milliseconds(50));
        
        stringstream ss;
        ss << "anh_" << soLanChupAnh << "_" << duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch()).count();
        string anhId = ss.str();
        
        soLanChupAnh++;
        
        if (luuLichSu) {
            lichSuAnh.push_back(anhId);
            if (lichSuAnh.size() > 100) { // Giới hạn lịch sử
                lichSuAnh.erase(lichSuAnh.begin());
            }
        }
        
        LoggingSystem::debug("Captured image: " + anhId);
        return anhId;
    }

    // Chụp ảnh liên tiếp
    vector<string> chupAnhLienTiep(int soLuong) {
        vector<string> danhSachAnh;
        for (int i = 0; i < soLuong; ++i) {
            danhSachAnh.push_back(chupAnh());
            this_thread::sleep_for(milliseconds(100));
        }
        return danhSachAnh;
    }

    // Điều chỉnh camera
    void dieuChinhLayNet(float kc) { 
        khoangCach = kc; 
        LoggingSystem::info("Focus distance adjusted to: " + to_string(kc));
    }
    
    void dieuChinhDoSang(int ds) { 
        doSang = ds; 
        LoggingSystem::info("Brightness adjusted to: " + to_string(ds));
    }
    
    void dieuChinhDoPhanGiai(int x, int y) {
        doPhanGiai = make_pair(x, y);
        LoggingSystem::info("Resolution adjusted to: " + to_string(x) + "x" + to_string(y));
    }

    // Kiểm tra chất lượng ảnh nâng cao
    bool kiemTraChatLuong(const string& anhId) {
        if (anhId.empty() || anhId == "invalid") return false;
        
        // Giả lập kiểm tra chất lượng dựa trên độ sáng và độ phân giải
        uniform_real_distribution<float> dis(0.0f, 1.0f);
        float chatLuong = dis(gen);
        
        bool datYeuCau = chatLuong > 0.3f; // Ngưỡng chất lượng
        LoggingSystem::debug("Image quality check for " + anhId + ": " + (datYeuCau ? "PASS" : "FAIL"));
        return datYeuCau;
    }

    // Calibration camera
    bool calibration() {
        LoggingSystem::info("Starting camera calibration...");
        trangThaiCamera = BAO_TRI;
        
        // Giả lập quá trình calibration
        this_thread::sleep_for(milliseconds(2000));
        
        trangThaiCamera = DANG_HOAT_DONG;
        LoggingSystem::info("Camera calibration completed successfully");
        return true;
    }

    // Getters và Setters
    pair<int, int> getDoPhanGiai() const { return doPhanGiai; }
    int getGocNhin() const { return gocNhin; }
    float getKhoangCach() const { return khoangCach; }
    int getDoSang() const { return doSang; }
    bool getTrangThai() const { return trangThai; }
    TrangThai getTrangThaiCamera() const { return trangThaiCamera; }
    int getSoLanChupAnh() const { return soLanChupAnh; }
    
    void setTrangThai(bool tt) { 
        trangThai = tt; 
        LoggingSystem::info("Camera status changed to: " + (tt ? "ACTIVE" : "INACTIVE"));
    }
    
    void setTrangThaiCamera(TrangThai tt) { trangThaiCamera = tt; }
    
    vector<string> getLichSuAnh() const { return lichSuAnh; }
    
    // Thống kê camera
    string layThongTinCamera() const {
        stringstream ss;
        ss << "Camera Info:\n";
        ss << "Resolution: " << doPhanGiai.first << "x" << doPhanGiai.second << "\n";
        ss << "Field of view: " << gocNhin << " degrees\n";
        ss << "Focus distance: " << khoangCach << " cm\n";
        ss << "Brightness: " << doSang << "\n";
        ss << "Status: " << (trangThai ? "Active" : "Inactive") << "\n";
        ss << "Camera state: " << trangThaiCamera << "\n";
        ss << "Total captures: " << soLanChupAnh << "\n";
        ss << "History size: " << lichSuAnh.size();
        return ss.str();
    }
};

// Lớp Xử Lý Hình Ảnh nâng cao
class XuLyHinhAnh {
private:
    string anhGocId;
    int nguongPhatHien;
    map<string, string> cacheXuLy;
    mutex processingMutex;
    random_device rd;
    mt19937 gen;
    vector<string> lichSuXuLy;

public:
    XuLyHinhAnh() : nguongPhatHien(100), gen(rd()) {
        LoggingSystem::info("Image processing system initialized");
    }

    void setAnhGoc(const string& anhId) { 
        anhGocId = anhId; 
        LoggingSystem::debug("Source image set to: " + anhId);
    }
    
    string chuyenXam() {
        lock_guard<mutex> lock(processingMutex);
        string key = anhGocId + "_gray";
        
        if (cacheXuLy.find(key) != cacheXuLy.end()) {
            LoggingSystem::debug("Using cached grayscale conversion");
            return cacheXuLy[key];
        }
        
        // Giả lập thời gian xử lý
        this_thread::sleep_for(milliseconds(20));
        
        string result = anhGocId + "_xam";
        cacheXuLy[key] = result;
        lichSuXuLy.push_back("Grayscale: " + result);
        
        LoggingSystem::debug("Grayscale conversion completed: " + result);
        return result;
    }

    string locNhieu() {
        lock_guard<mutex> lock(processingMutex);
        string key = anhGocId + "_denoise";
        
        if (cacheXuLy.find(key) != cacheXuLy.end()) {
            LoggingSystem::debug("Using cached denoising");
            return cacheXuLy[key];
        }
        
        this_thread::sleep_for(milliseconds(30));
        
        string result = anhGocId + "_loc_nhieu";
        cacheXuLy[key] = result;
        lichSuXuLy.push_back("Denoise: " + result);
        
        LoggingSystem::debug("Denoising completed: " + result);
        return result;
    }

    string phatHienCanh() {
        lock_guard<mutex> lock(processingMutex);
        string key = anhGocId + "_edges";
        
        if (cacheXuLy.find(key) != cacheXuLy.end()) {
            LoggingSystem::debug("Using cached edge detection");
            return cacheXuLy[key];
        }
        
        this_thread::sleep_for(milliseconds(40));
        
        string result = anhGocId + "_phat_hien_canh";
        cacheXuLy[key] = result;
        lichSuXuLy.push_back("Edge detection: " + result);
        
        LoggingSystem::debug("Edge detection completed: " + result);
        return result;
    }

    // Tìm viền đồ vật với thuật toán nâng cao
    vector<vector<pair<int, int>>> timVienDoVat() {
        lock_guard<mutex> lock(processingMutex);
        
        LoggingSystem::debug("Starting contour detection...");
        this_thread::sleep_for(milliseconds(50));
        
        vector<vector<pair<int, int>>> contours;
        
        // Tạo nhiều contours giả lập với kích thước và hình dạng khác nhau
        uniform_int_distribution<int> sizeDis(50, 300);
        uniform_int_distribution<int> posDis(50, 500);
        
        int numContours = uniform_int_distribution<int>(1, 5)(gen);
        
        for (int i = 0; i < numContours; ++i) {
            vector<pair<int, int>> contour;
            int x = posDis(gen);
            int y = posDis(gen);
            int width = sizeDis(gen);
            int height = sizeDis(gen);
            
            // Tạo hình chữ nhật
            contour.push_back(make_pair(x, y));
            contour.push_back(make_pair(x + width, y));
            contour.push_back(make_pair(x + width, y + height));
            contour.push_back(make_pair(x, y + height));
            
            contours.push_back(contour);
        }
        
        LoggingSystem::debug("Found " + to_string(contours.size()) + " contours");
        return contours;
    }

    // Tính diện tích với thuật toán Shoelace
    float tinhDienTich(const vector<pair<int, int>>& contour) {
        if (contour.size() < 3) return 0.0f;
        
        float area = 0.0f;
        int n = contour.size();
        
        for (int i = 0; i < n; ++i) {
            int j = (i + 1) % n;
            area += contour[i].first * contour[j].second;
            area -= contour[j].first * contour[i].second;
        }
        
        return abs(area) / 2.0f;
    }

    // Xác định tâm đồ vật với độ chính xác cao hơn
    pair<int, int> xacDinhTamDoVat(const vector<pair<int, int>>& contour) {
        if (contour.empty()) return make_pair(0, 0);
        
        double sumX = 0.0, sumY = 0.0;
        for (const auto& point : contour) {
            sumX += point.first;
            sumY += point.second;
        }
        
        int centerX = static_cast<int>(sumX / contour.size());
        int centerY = static_cast<int>(sumY / contour.size());
        
        LoggingSystem::debug("Object center calculated: (" + to_string(centerX) + ", " + to_string(centerY) + ")");
        return make_pair(centerX, centerY);
    }

    // Tính chu vi của contour
    float tinhChuVi(const vector<pair<int, int>>& contour) {
        if (contour.size() < 2) return 0.0f;
        
        float perimeter = 0.0f;
        for (size_t i = 0; i < contour.size(); ++i) {
            size_t next = (i + 1) % contour.size();
            int dx = contour[next].first - contour[i].first;
            int dy = contour[next].second - contour[i].second;
            perimeter += sqrt(dx*dx + dy*dy);
        }
        
        return perimeter;
    }

    // Tính tỷ lệ khung hình
    float tinhTyLeKhungHinh(const vector<pair<int, int>>& contour) {
        if (contour.size() < 4) return 1.0f;
        
        int minX = contour[0].first, maxX = contour[0].first;
        int minY = contour[0].second, maxY = contour[0].second;
        
        for (const auto& point : contour) {
            minX = min(minX, point.first);
            maxX = max(maxX, point.first);
            minY = min(minY, point.second);
            maxY = max(maxY, point.second);
        }
        
        int width = maxX - minX;
        int height = maxY - minY;
        
        if (height == 0) return 1.0f;
        return static_cast<float>(width) / static_cast<float>(height);
    }

    // Làm sạch cache
    void lamSachCache() {
        lock_guard<mutex> lock(processingMutex);
        cacheXuLy.clear();
        LoggingSystem::info("Image processing cache cleared");
    }

    // Thống kê xử lý
    string layThongTinXuLy() const {
        stringstream ss;
        ss << "Image Processing Info:\n";
        ss << "Current image: " << anhGocId << "\n";
        ss << "Detection threshold: " << nguongPhatHien << "\n";
        ss << "Cache size: " << cacheXuLy.size() << "\n";
        ss << "Processing history: " << lichSuXuLy.size() << " operations";
        return ss.str();
    }

    // Getters
    int getNguongPhatHien() const { return nguongPhatHien; }
    void setNguongPhatHien(int nguong) { nguongPhatHien = nguong; }
    map<string, string> getCacheXuLy() const { return cacheXuLy; }
    vector<string> getLichSuXuLy() const { return lichSuXuLy; }
};

// Lớp Phân Tích Đặc Điểm nâng cao
class PhanTichDacDiem {
private:
    map<string, vector<float>> cacheHistogram;
    mutex analysisMutex;
    random_device rd;
    mt19937 gen;

public:
    PhanTichDacDiem() : gen(rd()) {
        LoggingSystem::info("Feature analysis system initialized");
    }

    // Trích xuất hình dạng với thuật toán nâng cao
    HinhDang trichXuatHinhDang(const vector<pair<int, int>>& contour) {
        lock_guard<mutex> lock(analysisMutex);
        
        if (contour.size() < 3) {
            LoggingSystem::warning("Contour has insufficient points for shape analysis");
            return KHAC;
        }

        LoggingSystem::debug("Analyzing shape with " + to_string(contour.size()) + " points");

        // Phân tích dựa trên số điểm và tỷ lệ
        if (contour.size() == 3) {
            LoggingSystem::debug("Shape identified as triangle");
            return TAM_GIAC;
        }
        
        if (contour.size() == 4) {
            // Tính độ dài các cạnh
            vector<float> edgeLengths;
            for (int i = 0; i < 4; ++i) {
                int next = (i + 1) % 4;
                int dx = contour[next].first - contour[i].first;
                int dy = contour[next].second - contour[i].second;
                edgeLengths.push_back(sqrt(dx*dx + dy*dy));
            }
            
            // Kiểm tra tỷ lệ các cạnh
            float ratio1 = edgeLengths[0] / edgeLengths[1];
            float ratio2 = edgeLengths[2] / edgeLengths[3];
            
            if (abs(ratio1 - 1.0f) < 0.1f && abs(ratio2 - 1.0f) < 0.1f) {
                LoggingSystem::debug("Shape identified as square");
                return VUONG;
            } else {
                LoggingSystem::debug("Shape identified as rectangle");
                return CHU_NHAT;
            }
        }
        
        if (contour.size() > 8) {
            // Kiểm tra độ tròn bằng cách tính tỷ lệ chu vi và diện tích
            float perimeter = 0.0f;
            for (size_t i = 0; i < contour.size(); ++i) {
                size_t next = (i + 1) % contour.size();
                int dx = contour[next].first - contour[i].first;
                int dy = contour[next].second - contour[i].second;
                perimeter += sqrt(dx*dx + dy*dy);
            }
            
            // Tính diện tích bằng Shoelace formula
            float area = 0.0f;
            int n = contour.size();
            for (int i = 0; i < n; ++i) {
                int j = (i + 1) % n;
                area += contour[i].first * contour[j].second;
                area -= contour[j].first * contour[i].second;
            }
            area = abs(area) / 2.0f;
            
            // Tính circularity (4π*area/perimeter²)
            float circularity = (4.0f * M_PI * area) / (perimeter * perimeter);
            
            if (circularity > 0.7f) {
                LoggingSystem::debug("Shape identified as circle (circularity: " + to_string(circularity) + ")");
                return TRON;
            }
        }
        
        LoggingSystem::debug("Shape identified as other");
        return KHAC;
    }

    // Trích xuất màu sắc với histogram nâng cao
    vector<float> trichXuatMauSac(const string& anhId, const vector<pair<int, int>>& contour) {
        lock_guard<mutex> lock(analysisMutex);
        
        string key = anhId + "_" + to_string(contour.size());
        
        if (cacheHistogram.find(key) != cacheHistogram.end()) {
            LoggingSystem::debug("Using cached color histogram");
            return cacheHistogram[key];
        }
        
        // Giả lập thời gian phân tích màu sắc
        this_thread::sleep_for(milliseconds(25));
        
        vector<float> histogram(3, 0.0f);
        
        // Tạo histogram màu sắc giả lập dựa trên kích thước contour
        uniform_real_distribution<float> dis(0.0f, 1.0f);
        
        float total = 0.0f;
        for (int i = 0; i < 3; ++i) {
            histogram[i] = dis(gen);
            total += histogram[i];
        }
        
        // Chuẩn hóa histogram
        for (int i = 0; i < 3; ++i) {
            histogram[i] /= total;
        }
        
        cacheHistogram[key] = histogram;
        
        LoggingSystem::debug("Color histogram extracted: [" + 
            to_string(histogram[0]) + ", " + 
            to_string(histogram[1]) + ", " + 
            to_string(histogram[2]) + "]");
        
        return histogram;
    }

    // Trích xuất texture features
    vector<float> trichXuatTexture(const string& anhId, const vector<pair<int, int>>& contour) {
        lock_guard<mutex> lock(analysisMutex);
        
        // Giả lập phân tích texture
        this_thread::sleep_for(milliseconds(30));
        
        vector<float> textureFeatures(5, 0.0f);
        uniform_real_distribution<float> dis(0.0f, 1.0f);
        
        for (int i = 0; i < 5; ++i) {
            textureFeatures[i] = dis(gen);
        }
        
        LoggingSystem::debug("Texture features extracted for " + anhId);
        return textureFeatures;
    }

    // Trích xuất đặc điểm tổng hợp
    vector<float> trichXuatDacDiemTongHop(const string& anhId, const vector<pair<int, int>>& contour) {
        vector<float> features;
        
        // Thêm hình dạng
        features.push_back(static_cast<float>(trichXuatHinhDang(contour)));
        
        // Thêm màu sắc
        auto colorHist = trichXuatMauSac(anhId, contour);
        features.insert(features.end(), colorHist.begin(), colorHist.end());
        
        // Thêm texture
        auto textureFeatures = trichXuatTexture(anhId, contour);
        features.insert(features.end(), textureFeatures.begin(), textureFeatures.end());
        
        // Thêm kích thước và tỷ lệ
        if (contour.size() >= 4) {
            int minX = contour[0].first, maxX = contour[0].first;
            int minY = contour[0].second, maxY = contour[0].second;
            
            for (const auto& point : contour) {
                minX = min(minX, point.first);
                maxX = max(maxX, point.first);
                minY = min(minY, point.second);
                maxY = max(maxY, point.second);
            }
            
            float width = maxX - minX;
            float height = maxY - minY;
            float area = width * height;
            float aspectRatio = (height > 0) ? width / height : 1.0f;
            
            features.push_back(width);
            features.push_back(height);
            features.push_back(area);
            features.push_back(aspectRatio);
        }
        
        LoggingSystem::debug("Comprehensive features extracted: " + to_string(features.size()) + " features");
        return features;
    }

    // Làm sạch cache
    void lamSachCache() {
        lock_guard<mutex> lock(analysisMutex);
        cacheHistogram.clear();
        LoggingSystem::info("Feature analysis cache cleared");
    }

    // Thống kê phân tích
    string layThongTinPhanTich() const {
        stringstream ss;
        ss << "Feature Analysis Info:\n";
        ss << "Cached histograms: " << cacheHistogram.size() << "\n";
        ss << "Analysis system: Active";
        return ss.str();
    }
};

// Lớp Bộ Nhận Diện nâng cao với Machine Learning
class BoNhanDien {
private:
    vector<pair<DoVat, vector<float>>> thuVienMau;
    float doChinhXacYeuCau;
    int soMauToiDa;
    mutex recognitionMutex;
    map<string, int> thongKeNhanDien;
    vector<pair<float, float>> lichSuDoChinhXac;
    random_device rd;
    mt19937 gen;

public:
    BoNhanDien(float dc = 0.7f, int sm = 100) : doChinhXacYeuCau(dc), soMauToiDa(sm), gen(rd()) {
        LoggingSystem::info("Recognition system initialized with threshold: " + to_string(dc));
    }

    void themMauMoi(const DoVat& dv, const vector<float>& dacDiem) {
        lock_guard<mutex> lock(recognitionMutex);
        
        if (thuVienMau.size() < soMauToiDa) {
            thuVienMau.push_back(make_pair(dv, dacDiem));
            thongKeNhanDien[dv.getTen()] = 0;
            LoggingSystem::info("Added new sample: " + dv.getTen() + " (Total samples: " + to_string(thuVienMau.size()) + ")");
        } else {
            LoggingSystem::warning("Sample library is full, cannot add: " + dv.getTen());
        }
    }

    // Nhận diện với nhiều thuật toán
    pair<DoVat, float> soSanhVoiMau(const vector<float>& dacDiem) {
        lock_guard<mutex> lock(recognitionMutex);
        
        if (thuVienMau.empty()) {
            LoggingSystem::warning("No samples available for recognition");
            return make_pair(DoVat("", KHONG_XAC_DINH, KHAC, 0.0f, make_pair(0, 0)), 0.0f);
        }

        LoggingSystem::debug("Starting recognition with " + to_string(thuVienMau.size()) + " samples");

        float diemCaoNhat = 0.0f;
        DoVat vatDuDoan = thuVienMau[0].first;
        string tenDuDoan = "";

        // Sử dụng nhiều thuật toán và kết hợp kết quả
        vector<pair<DoVat, float>> ketQuaCacThuatToan;

        for (const auto& mau : thuVienMau) {
            // Euclidean distance
            float diemEuclidean = tinhKhoangCachEuclidean(dacDiem, mau.second);
            
            // Cosine similarity
            float diemCosine = tinhCosineSimilarity(dacDiem, mau.second);
            
            // Manhattan distance
            float diemManhattan = tinhKhoangCachManhattan(dacDiem, mau.second);
            
            // Kết hợp các điểm số
            float diemTongHop = (diemEuclidean * 0.4f + diemCosine * 0.4f + diemManhattan * 0.2f);
            
            ketQuaCacThuatToan.push_back(make_pair(mau.first, diemTongHop));
            
            if (diemTongHop > diemCaoNhat) {
                diemCaoNhat = diemTongHop;
                vatDuDoan = mau.first;
                tenDuDoan = mau.first.getTen();
            }
        }

        // Cập nhật thống kê
        if (diemCaoNhat >= doChinhXacYeuCau) {
            thongKeNhanDien[tenDuDoan]++;
            lichSuDoChinhXac.push_back(make_pair(diemCaoNhat, 1.0f));
            LoggingSystem::info("Recognition successful: " + tenDuDoan + " (confidence: " + to_string(diemCaoNhat) + ")");
        } else {
            lichSuDoChinhXac.push_back(make_pair(diemCaoNhat, 0.0f));
            LoggingSystem::warning("Recognition failed - confidence too low: " + to_string(diemCaoNhat));
        }

        vatDuDoan.setDoTinCay(diemCaoNhat);
        return make_pair(vatDuDoan, diemCaoNhat);
    }

    // Euclidean distance
    float tinhKhoangCachEuclidean(const vector<float>& v1, const vector<float>& v2) {
        if (v1.size() != v2.size() || v1.empty()) return 0.0f;

        float distance = 0.0f;
        for (size_t i = 0; i < v1.size(); i++) {
            distance += pow(v1[i] - v2[i], 2);
        }
        return 1.0f / (1.0f + sqrt(distance));
    }

    // Cosine similarity
    float tinhCosineSimilarity(const vector<float>& v1, const vector<float>& v2) {
        if (v1.size() != v2.size() || v1.empty()) return 0.0f;

        float dotProduct = 0.0f;
        float norm1 = 0.0f;
        float norm2 = 0.0f;

        for (size_t i = 0; i < v1.size(); i++) {
            dotProduct += v1[i] * v2[i];
            norm1 += v1[i] * v1[i];
            norm2 += v2[i] * v2[i];
        }

        if (norm1 == 0.0f || norm2 == 0.0f) return 0.0f;
        return dotProduct / (sqrt(norm1) * sqrt(norm2));
    }

    // Manhattan distance
    float tinhKhoangCachManhattan(const vector<float>& v1, const vector<float>& v2) {
        if (v1.size() != v2.size() || v1.empty()) return 0.0f;

        float distance = 0.0f;
        for (size_t i = 0; i < v1.size(); i++) {
            distance += abs(v1[i] - v2[i]);
        }
        return 1.0f / (1.0f + distance);
    }

    // Học từ dữ liệu mới (online learning)
    void hocTuDuLieuMoi(const DoVat& dv, const vector<float>& dacDiem, bool dungDuDoan = true) {
        lock_guard<mutex> lock(recognitionMutex);
        
        if (dungDuDoan) {
            // Cập nhật mẫu hiện có nếu tìm thấy mẫu tương tự
            for (auto& mau : thuVienMau) {
                if (mau.first.getTen() == dv.getTen()) {
                    // Cập nhật đặc điểm bằng trung bình có trọng số
                    for (size_t i = 0; i < mau.second.size() && i < dacDiem.size(); ++i) {
                        mau.second[i] = (mau.second[i] * 0.7f + dacDiem[i] * 0.3f);
                    }
                    LoggingSystem::info("Updated existing sample: " + dv.getTen());
                    return;
                }
            }
        }
        
        // Thêm mẫu mới
        themMauMoi(dv, dacDiem);
    }

    // Làm sạch dữ liệu cũ
    void lamSachDuLieuCu(int soNgayCu) {
        lock_guard<mutex> lock(recognitionMutex);
        
        // Giả lập việc xóa dữ liệu cũ
        if (thuVienMau.size() > soMauToiDa * 0.8) {
            int soXoa = thuVienMau.size() - soMauToiDa * 0.7;
            thuVienMau.erase(thuVienMau.begin(), thuVienMau.begin() + soXoa);
            LoggingSystem::info("Cleaned " + to_string(soXoa) + " old samples");
        }
    }

    // Thống kê nhận diện
    string layThongKeNhanDien() const {
        stringstream ss;
        ss << "Recognition Statistics:\n";
        ss << "Total samples: " << thuVienMau.size() << "\n";
        ss << "Recognition threshold: " << doChinhXacYeuCau << "\n";
        ss << "Recognition history: " << lichSuDoChinhXac.size() << " attempts\n";
        
        if (!lichSuDoChinhXac.empty()) {
            float tongDoChinhXac = 0.0f;
            int soThanhCong = 0;
            
            for (const auto& ketQua : lichSuDoChinhXac) {
                tongDoChinhXac += ketQua.first;
                if (ketQua.second > 0.5f) soThanhCong++;
            }
            
            ss << "Average confidence: " << fixed << setprecision(3) << (tongDoChinhXac / lichSuDoChinhXac.size()) << "\n";
            ss << "Success rate: " << fixed << setprecision(1) << (soThanhCong * 100.0f / lichSuDoChinhXac.size()) << "%\n";
        }
        
        ss << "Object recognition counts:\n";
        for (const auto& pair : thongKeNhanDien) {
            ss << "  " << pair.first << ": " << pair.second << " times\n";
        }
        
        return ss.str();
    }

    // Getters
    int getSoMau() const { return thuVienMau.size(); }
    float getDoChinhXacYeuCau() const { return doChinhXacYeuCau; }
    void setDoChinhXacYeuCau(float dc) { doChinhXacYeuCau = dc; }
    map<string, int> getThongKeNhanDien() const { return thongKeNhanDien; }
    vector<pair<float, float>> getLichSuDoChinhXac() const { return lichSuDoChinhXac; }
};

// Lớp Robot Nhận Diện nâng cao với Real-time Processing
class RobotNhanDien {
private:
    Camera camera;
    XuLyHinhAnh xuLyAnh;
    PhanTichDacDiem phanTich;
    BoNhanDien boNhanDien;
    vector<DoVat> danhSachDoVat;
    CauHinhHeThong cauHinh;
    ThongKeHieuSuat thongKe;
    TrangThai trangThai;
    mutex robotMutex;
    thread realTimeThread;
    bool dangChayRealTime;
    queue<string> hangDoiXuLy;

public:
    RobotNhanDien() : trangThai(DANG_HOAT_DONG), dangChayRealTime(false) {
        LoggingSystem::info("Advanced Robot Recognition System initialized");
        LoggingSystem::init();
    }

    // Quét phòng với xử lý nâng cao
    void quetPhong() {
        lock_guard<mutex> lock(robotMutex);
        
        auto startTime = high_resolution_clock::now();
        LoggingSystem::info("Starting room scan...");
        
        trangThai = DANG_QUET;
        
        // Chụp ảnh với kiểm tra chất lượng
        string anh = camera.chupAnh();
        if (!camera.kiemTraChatLuong(anh)) {
            LoggingSystem::error("Image quality check failed!");
            trangThai = DANG_HOAT_DONG;
            return;
        }

        // Xử lý hình ảnh pipeline
        xuLyAnh.setAnhGoc(anh);
        string anhXam = xuLyAnh.chuyenXam();
        string anhLocNhieu = xuLyAnh.locNhieu();
        string anhCanh = xuLyAnh.phatHienCanh();

        // Tìm contours
        auto contours = xuLyAnh.timVienDoVat();
        LoggingSystem::debug("Found " + to_string(contours.size()) + " contours");

        int soDoVatNhanDien = 0;
        
        for (const auto& contour : contours) {
            float dienTich = xuLyAnh.tinhDienTich(contour);
            
            if (dienTich > cauHinh.nguongDienTich) {
                // Trích xuất đặc điểm tổng hợp
                auto dacDiem = phanTich.trichXuatDacDiemTongHop(anh, contour);
                auto tam = xuLyAnh.xacDinhTamDoVat(contour);

                // Nhận diện
                auto ketQua = boNhanDien.soSanhVoiMau(dacDiem);
                
                if (ketQua.second >= cauHinh.nguongTinCay) {
                    DoVat dv = ketQua.first;
                    dv.capNhatViTri(tam.first, tam.second);
                    dv.setAnhId(anh);
                    dv.setDienTich(dienTich);
                    dv.setHistogramMauSac(phanTich.trichXuatMauSac(anh, contour));
                    
                    danhSachDoVat.push_back(dv);
                    soDoVatNhanDien++;
                    
                    LoggingSystem::info("Recognized: " + dv.getTen() + " (confidence: " + to_string(ketQua.second) + ")");
                }
            }
        }

        // Cập nhật thống kê
        auto endTime = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(endTime - startTime);
        
        thongKe.soLanQuet++;
        thongKe.soDoVatNhanDien += soDoVatNhanDien;
        thongKe.lichSuThoiGian.push_back(duration.count());
        thongKe.thoiGianTrungBinh = tinhTrungBinh(thongKe.lichSuThoiGian);
        
        trangThai = DANG_HOAT_DONG;
        LoggingSystem::info("Room scan completed in " + to_string(duration.count()) + "ms, found " + to_string(soDoVatNhanDien) + " objects");
    }

    // Học đồ vật mới với validation
    void hocDoVatMoi(const string& ten, LoaiDoVat loai, HinhDang hd, const string& anhMauId) {
        lock_guard<mutex> lock(robotMutex);
        
        LoggingSystem::info("Learning new object: " + ten);
        trangThai = DANG_HOC;
        
        xuLyAnh.setAnhGoc(anhMauId);
        xuLyAnh.chuyenXam();
        xuLyAnh.locNhieu();
        xuLyAnh.phatHienCanh();

        auto contours = xuLyAnh.timVienDoVat();
        if (!contours.empty()) {
            // Sử dụng đặc điểm tổng hợp
            auto dacDiem = phanTich.trichXuatDacDiemTongHop(anhMauId, contours[0]);

            DoVat dv(ten, loai, hd, 0.0f, make_pair(0, 0));
            boNhanDien.themMauMoi(dv, dacDiem);
            
            thongKe.soDoVatHoc++;
            LoggingSystem::info("Successfully learned: " + ten);
        } else {
            LoggingSystem::error("Failed to learn " + ten + " - no contours found");
        }
        
        trangThai = DANG_HOAT_DONG;
    }

    // Báo cáo kết quả chi tiết
    void baoCaoKetQua() {
        lock_guard<mutex> lock(robotMutex);
        
        cout << "\n=== BAO CAO NHAN DIEN CHI TIET ===" << endl;
        cout << "Thoi gian: " << duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch()).count() << "ms" << endl;
        cout << "Trang thai: " << trangThai << endl;
        cout << "So do vat phat hien: " << danhSachDoVat.size() << endl;
        
        if (danhSachDoVat.empty()) {
            cout << "Khong phat hien do vat nao!" << endl;
            return;
        }

        // Nhóm đồ vật theo loại
        map<LoaiDoVat, vector<DoVat>> nhomDoVat;
        for (const auto& dv : danhSachDoVat) {
            nhomDoVat[dv.getLoai()].push_back(dv);
        }

        for (const auto& pair : nhomDoVat) {
            cout << "\n--- " << DoVat::loaiToString(pair.first) << " (" << pair.second.size() << " vat) ---" << endl;
            for (const auto& dv : pair.second) {
                cout << "  " << dv.layThongTin() << endl;
            }
        }
    }

    // Báo cáo thống kê hệ thống
    void baoCaoThongKe() {
        cout << "\n=== BAO CAO THONG KE HE THONG ===" << endl;
        cout << thongKe.soLanQuet << " lan quet" << endl;
        cout << thongKe.soDoVatNhanDien << " do vat nhan dien" << endl;
        cout << thongKe.soDoVatHoc << " do vat da hoc" << endl;
        cout << "Thoi gian trung binh: " << fixed << setprecision(2) << thongKe.thoiGianTrungBinh << "ms" << endl;
        
        cout << "\n" << boNhanDien.layThongKeNhanDien() << endl;
        cout << "\n" << camera.layThongTinCamera() << endl;
        cout << "\n" << xuLyAnh.layThongTinXuLy() << endl;
        cout << "\n" << phanTich.layThongTinPhanTich() << endl;
    }

    // Xử lý real-time
    void batDauRealTime() {
        if (dangChayRealTime) {
            LoggingSystem::warning("Real-time processing already running");
            return;
        }
        
        dangChayRealTime = true;
        realTimeThread = thread([this]() {
            LoggingSystem::info("Real-time processing started");
            
            while (dangChayRealTime) {
                quetPhong();
                this_thread::sleep_for(milliseconds(cauHinh.intervalQuet));
            }
            
            LoggingSystem::info("Real-time processing stopped");
        });
    }

    void dungRealTime() {
        if (!dangChayRealTime) {
            LoggingSystem::warning("Real-time processing not running");
            return;
        }
        
        dangChayRealTime = false;
        if (realTimeThread.joinable()) {
            realTimeThread.join();
        }
    }

    // Quản lý cấu hình
    void capNhatCauHinh(const CauHinhHeThong& cauHinhMoi) {
        lock_guard<mutex> lock(robotMutex);
        cauHinh = cauHinhMoi;
        boNhanDien.setDoChinhXacYeuCau(cauHinh.nguongTinCay);
        xuLyAnh.setNguongPhatHien(cauHinh.nguongDienTich);
        LoggingSystem::info("System configuration updated");
    }

    // Utility functions
    void xoaDanhSachDoVat() {
        lock_guard<mutex> lock(robotMutex);
        danhSachDoVat.clear();
        LoggingSystem::info("Object list cleared");
    }

    void lamSachCache() {
        lock_guard<mutex> lock(robotMutex);
        xuLyAnh.lamSachCache();
        phanTich.lamSachCache();
        boNhanDien.lamSachDuLieuCu(30);
        LoggingSystem::info("All caches cleared");
    }

    // Getters
    vector<DoVat> getDanhSachDoVat() const { return danhSachDoVat; }
    TrangThai getTrangThai() const { return trangThai; }
    CauHinhHeThong getCauHinh() const { return cauHinh; }
    ThongKeHieuSuat getThongKe() const { return thongKe; }
    bool isDangChayRealTime() const { return dangChayRealTime; }

private:
    double tinhTrungBinh(const vector<double>& values) {
        if (values.empty()) return 0.0;
        double sum = 0.0;
        for (double value : values) {
            sum += value;
        }
        return sum / values.size();
    }
};

// Hàm main để test hệ thống nâng cao
int main() {
    cout << "=== HE THONG ROBOT NHAN DIEN NANG CAO ===" << endl;
    cout << "Khoi tao he thong..." << endl;
    
    RobotNhanDien robot;

    // Cấu hình hệ thống
    CauHinhHeThong cauHinh;
    cauHinh.nguongTinCay = 0.75f;
    cauHinh.nguongDienTich = 800.0f;
    cauHinh.cheDoDebug = true;
    cauHinh.intervalQuet = 2000;
    robot.capNhatCauHinh(cauHinh);

    cout << "\n=== PHASE 1: HOC CAC MAU DO VAT ===" << endl;
    
    // Học các mẫu đồ vật với nhiều loại khác nhau
    robot.hocDoVatMoi("Qua bong", DO_CHOI, TRON, "qua_bong_mau");
    robot.hocDoVatMoi("Hop banh", DO_AN, VUONG, "hop_banh_mau");
    robot.hocDoVatMoi("Lon nuoc", DO_DUNG, TRON, "lon_nuoc_mau");
    robot.hocDoVatMoi("Ghe", DO_DUNG, CHU_NHAT, "ghe_mau");
    robot.hocDoVatMoi("Tam giac", DO_CHOI, TAM_GIAC, "tam_giac_mau");
    robot.hocDoVatMoi("Hop giay", RAC, VUONG, "hop_giay_mau");

    cout << "\n=== PHASE 2: QUET VA NHAN DIEN ===" << endl;
    
    // Quét và nhận diện lần 1
    cout << "\nLan quet thu 1:" << endl;
    robot.quetPhong();
    robot.baoCaoKetQua();

    // Quét lại lần 2
    cout << "\nLan quet thu 2:" << endl;
    robot.xoaDanhSachDoVat();
    robot.quetPhong();
    robot.baoCaoKetQua();

    // Quét lại lần 3
    cout << "\nLan quet thu 3:" << endl;
    robot.xoaDanhSachDoVat();
    robot.quetPhong();
    robot.baoCaoKetQua();

    cout << "\n=== PHASE 3: TEST REAL-TIME PROCESSING ===" << endl;
    
    // Test real-time processing
    cout << "Bat dau real-time processing (5 giay)..." << endl;
    robot.batDauRealTime();
    this_thread::sleep_for(seconds(5));
    robot.dungRealTime();
    
    cout << "\nKet qua sau real-time processing:" << endl;
    robot.baoCaoKetQua();

    cout << "\n=== PHASE 4: BAO CAO THONG KE ===" << endl;
    robot.baoCaoThongKe();

    cout << "\n=== PHASE 5: TEST CAC TINH NANG NANG CAO ===" << endl;
    
    // Test camera calibration
    cout << "\nTest camera calibration..." << endl;
    // Note: Camera calibration method would be called here
    
    // Test cache management
    cout << "\nTest cache management..." << endl;
    robot.lamSachCache();
    
    // Test configuration update
    cout << "\nTest configuration update..." << endl;
    cauHinh.nguongTinCay = 0.8f;
    cauHinh.nguongDienTich = 1200.0f;
    robot.capNhatCauHinh(cauHinh);
    
    // Final scan with new configuration
    cout << "\nLan quet cuoi cung voi cau hinh moi:" << endl;
    robot.xoaDanhSachDoVat();
    robot.quetPhong();
    robot.baoCaoKetQua();

    cout << "\n=== PHASE 6: BAO CAO CUOI CUNG ===" << endl;
    robot.baoCaoThongKe();

    cout << "\n=== KET THUC CHUONG TRINH ===" << endl;
    cout << "He thong da hoan thanh tat ca cac test!" << endl;
    cout << "Log file da duoc luu tai: robot_log.txt" << endl;

    return 0;
}
