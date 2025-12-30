#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <random>
#include <memory>
#include <cctype>

using namespace std;

// ==================== Lớp CauHoi ====================
class CauHoi {
private:
    string noiDung;
    vector<string> tuKhoaChinh;
    string loaiCauHoi;
    
    // Hàm chuyển chuỗi thành chữ thường
    string toLower(const string& str) {
        string result = str;
        transform(result.begin(), result.end(), result.begin(), ::tolower);
        return result;
    }
    
    // Hàm tách từ từ chuỗi
    vector<string> tachTu(const string& str) {
        vector<string> words;
        stringstream ss(str);
        string word;
        
        while (ss >> word) {
            // Loại bỏ dấu câu ở cuối từ
            while (!word.empty() && ispunct(word.back())) {
                word.pop_back();
            }
            if (!word.empty()) {
                words.push_back(toLower(word));
            }
        }
        return words;
    }
    
    // Trích xuất từ khóa quan trọng
    vector<string> trichXuatTuKhoa() {
        vector<string> stopWords = {"là", "của", "và", "có", "không", "được", "các", "này", "đó", "cho", "với", "trong", "để"};
        vector<string> words = tachTu(noiDung);
        vector<string> tuKhoa;
        
        for (const string& word : words) {
            // Kiểm tra xem từ có phải là stop word không
            bool isStopWord = false;
            for (const string& sw : stopWords) {
                if (word == sw) {
                    isStopWord = true;
                    break;
                }
            }
            
            // Chỉ giữ từ không phải stop word và có độ dài > 1
            if (!isStopWord && word.length() > 1) {
                tuKhoa.push_back(word);
            }
        }
        
        return tuKhoa;
    }
    
    // Xác định loại câu hỏi
    string xacDinhLoai() {
        string content = toLower(noiDung);
        
        if (content.find("ai") != string::npos || content.find("người nào") != string::npos) {
            return "AI";
        } else if (content.find("gì") != string::npos || content.find("cái gì") != string::npos) {
            return "GÌ";
        } else if (content.find("khi nào") != string::npos || content.find("bao giờ") != string::npos) {
            return "KHI_NAO";
        } else if (content.find("ở đâu") != string::npos || content.find("đâu") != string::npos) {
            return "O_DAU";
        } else if (content.find("thế nào") != string::npos || content.find("như thế nào") != string::npos) {
            return "NHU_THE_NAO";
        } else {
            return "KHAC";
        }
    }
    
public:
    CauHoi(const string& nd) : noiDung(nd) {
        tuKhoaChinh = trichXuatTuKhoa();
        loaiCauHoi = xacDinhLoai();
    }
    
    string getNoiDung() const { return noiDung; }
    vector<string> getTuKhoa() const { return tuKhoaChinh; }
    string getLoaiCauHoi() const { return loaiCauHoi; }
    
    void hienThi() const {
        cout << "Câu hỏi: " << noiDung << endl;
        cout << "Loại: " << loaiCauHoi << endl;
        cout << "Từ khóa: ";
        for (size_t i = 0; i < tuKhoaChinh.size(); i++) {
            cout << tuKhoaChinh[i];
            if (i < tuKhoaChinh.size() - 1) cout << ", ";
        }
        cout << endl;
    }
};

// ==================== Lớp CauTraLoi ====================
class CauTraLoi {
private:
    string noiDung;
    float doTinCay;
    string nguonThongTin;
    time_t thoiGianTao;
    
public:
    CauTraLoi(const string& nd, float dtc = 1.0, const string& nguon = "Hệ thống") 
        : noiDung(nd), nguonThongTin(nguon) {
        doTinCay = min(max(dtc, 0.0f), 1.0f);  // Giới hạn từ 0 đến 1
        thoiGianTao = time(nullptr);
    }
    
    void capNhatDoTinCay(float dtcMoi) {
        doTinCay = min(max(dtcMoi, 0.0f), 1.0f);
    }
    
    string getNoiDung() const { return noiDung; }
    float getDoTinCay() const { return doTinCay; }
    string getNguon() const { return nguonThongTin; }
    
    void hienThi() const {
        cout << noiDung << " (Độ tin cậy: " << fixed << setprecision(2) << doTinCay 
             << ", Nguồn: " << nguonThongTin << ")" << endl;
    }
};

// ==================== Lớp KhoKienThuc ====================
class KhoKienThuc {
private:
    string chuDe;
    map<vector<string>, vector<shared_ptr<CauTraLoi>>> kienThuc;
    vector<pair<time_t, vector<string>>> lichSuTimKiem;
    
    // Hàm chuyển chuỗi thành chữ thường
    string toLower(const string& str) {
        string result = str;
        transform(result.begin(), result.end(), result.begin(), ::tolower);
        return result;
    }
    
    // Khởi tạo kiến thức mẫu
    void khoiTaoKienThucMau() {
        // Kiến thức về thời tiết
        themKienThuc({"thời", "tiết", "hôm", "nay"},
            make_shared<CauTraLoi>("Hôm nay trời nắng đẹp, nhiệt độ khoảng 28°C, độ ẩm 65%", 0.9, "Dự báo thời tiết"));
        
        themKienThuc({"thời", "tiết", "ngày", "mai"},
            make_shared<CauTraLoi>("Ngày mai có thể có mưa rào, nhiệt độ 25-30°C", 0.8, "Dự báo thời tiết"));
        
        // Kiến thức về thể thao
        themKienThuc({"bóng", "đá", "world", "cup"},
            make_shared<CauTraLoi>("World Cup là giải bóng đá lớn nhất thế giới, tổ chức 4 năm một lần", 1.0, "FIFA"));
        
        themKienThuc({"ronaldo", "cr7", "bóng", "đá"},
            make_shared<CauTraLoi>("Cristiano Ronaldo là một trong những cầu thủ vĩ đại nhất lịch sử bóng đá", 0.95, "Wikipedia"));
        
        themKienThuc({"messi", "bóng", "đá"},
            make_shared<CauTraLoi>("Lionel Messi là cầu thủ người Argentina, đã giành 8 Quả bóng vàng", 0.95, "Wikipedia"));
        
        // Kiến thức về ẩm thực
        themKienThuc({"phở", "món", "ăn", "việt", "nam"},
            make_shared<CauTraLoi>("Phở là món ăn truyền thống nổi tiếng của Việt Nam, có nước dùng từ xương hầm", 1.0, "Ẩm thực VN"));
        
        themKienThuc({"bánh", "mì", "việt", "nam"},
            make_shared<CauTraLoi>("Bánh mì Việt Nam là món ăn đường phố nổi tiếng thế giới", 0.95, "Ẩm thực VN"));
        
        themKienThuc({"bún", "bò", "huế"},
            make_shared<CauTraLoi>("Bún bò Huế là đặc sản của cố đô, có vị cay và mùi sả đặc trưng", 1.0, "Ẩm thực VN"));
        
        // Kiến thức chung
        themKienThuc({"xin", "chào"},
            make_shared<CauTraLoi>("Xin chào! Tôi là chatbot trợ lý. Tôi có thể giúp gì cho bạn?", 1.0, "Hệ thống"));
        
        themKienThuc({"cảm", "ơn"},
            make_shared<CauTraLoi>("Không có gì! Rất vui được giúp đỡ bạn!", 1.0, "Hệ thống"));
        
        themKienThuc({"tạm", "biệt"},
            make_shared<CauTraLoi>("Tạm biệt! Hẹn gặp lại bạn!", 1.0, "Hệ thống"));
        
        // Kiến thức về công nghệ
        themKienThuc({"ai", "trí", "tuệ", "nhân", "tạo"},
            make_shared<CauTraLoi>("AI (Artificial Intelligence) là công nghệ mô phỏng trí thông minh của con người trong máy móc", 1.0, "Tech Wiki"));
        
        themKienThuc({"chatbot", "là", "gì"},
            make_shared<CauTraLoi>("Chatbot là chương trình máy tính có khả năng trò chuyện với con người thông qua văn bản hoặc giọng nói", 1.0, "Tech Wiki"));
    }
    
public:
    KhoKienThuc(const string& cd = "Tổng hợp") : chuDe(cd) {
        khoiTaoKienThucMau();
    }
    
    void themKienThuc(const vector<string>& tuKhoa, shared_ptr<CauTraLoi> cauTraLoi) {
        // Chuyển từ khóa thành chữ thường và sắp xếp
        vector<string> key = tuKhoa;
        for (string& k : key) {
            k = toLower(k);
        }
        sort(key.begin(), key.end());
        
        kienThuc[key].push_back(cauTraLoi);
    }
    
    shared_ptr<CauTraLoi> timCauTraLoi(const vector<string>& tuKhoaList) {
        if (tuKhoaList.empty()) return nullptr;
        
        // Lưu lịch sử tìm kiếm
        lichSuTimKiem.push_back({time(nullptr), tuKhoaList});
        
        shared_ptr<CauTraLoi> ketQuaTotNhat = nullptr;
        float doPhuHopCaoNhat = 0;
        
        // Duyệt qua tất cả kiến thức
        for (const auto& pair : kienThuc) {
            const vector<string>& keyTuple = pair.first;
            const vector<shared_ptr<CauTraLoi>>& cauTraLoiList = pair.second;
            
            // Tính số từ khóa trùng khớp
            int soTuTrung = 0;
            for (const string& tu1 : tuKhoaList) {
                string tu1Lower = toLower(tu1);
                for (const string& tu2 : keyTuple) {
                    if (tu1Lower == tu2) {
                        soTuTrung++;
                        break;
                    }
                }
            }
            
            if (soTuTrung > 0) {
                // Tính độ phù hợp
                float doPhuHop = (float)soTuTrung / max(tuKhoaList.size(), keyTuple.size());
                
                if (doPhuHop > doPhuHopCaoNhat) {
                    doPhuHopCaoNhat = doPhuHop;
                    // Chọn câu trả lời có độ tin cậy cao nhất
                    float doTinCayMax = 0;
                    for (const auto& ctl : cauTraLoiList) {
                        if (ctl->getDoTinCay() > doTinCayMax) {
                            doTinCayMax = ctl->getDoTinCay();
                            ketQuaTotNhat = ctl;
                        }
                    }
                }
            }
        }
        
        // Chỉ trả về kết quả nếu độ phù hợp > 30%
        if (doPhuHopCaoNhat > 0.3) {
            return ketQuaTotNhat;
        }
        
        return nullptr;
    }
    
    void thongKeKienThuc() const {
        cout << "\n=== Thống kê kho kiến thức ===" << endl;
        cout << "Chủ đề: " << chuDe << endl;
        cout << "Số chủ đề: " << kienThuc.size() << endl;
        
        int tongCauTraLoi = 0;
        for (const auto& pair : kienThuc) {
            tongCauTraLoi += pair.second.size();
        }
        cout << "Tổng số câu trả lời: " << tongCauTraLoi << endl;
        cout << "Số lần tìm kiếm: " << lichSuTimKiem.size() << endl;
    }
};

// ==================== Lớp ChatBot ====================
class ChatBot {
private:
    string tenBot;
    unique_ptr<KhoKienThuc> khoKienThuc;
    vector<tuple<time_t, string, string, string>> lichSuTroChuyen;  // thời gian, người, bot, loại câu hỏi
    vector<string> cauTraLoiMacDinh;
    
    // Random engine cho câu trả lời mặc định
    random_device rd;
    mt19937 gen;
    uniform_int_distribution<> dis;
    
public:
    ChatBot(const string& ten = "AI Assistant") : tenBot(ten), gen(rd()) {
        khoKienThuc = make_unique<KhoKienThuc>("Tổng hợp");
        
        // Khởi tạo câu trả lời mặc định
        cauTraLoiMacDinh = {
            "Xin lỗi, tôi chưa hiểu câu hỏi của bạn.",
            "Bạn có thể diễn đạt lại câu hỏi được không?",
            "Tôi đang học hỏi thêm về vấn đề này.",
            "Câu hỏi thú vị! Nhưng tôi cần thêm thông tin để trả lời chính xác.",
            "Hmm, tôi chưa có đủ kiến thức về vấn đề này.",
            "Bạn có thể cho tôi thêm thông tin được không?"
        };
        
        dis = uniform_int_distribution<>(0, cauTraLoiMacDinh.size() - 1);
    }
    
    unique_ptr<CauHoi> phanTichCauHoi(const string& noiDung) {
        return make_unique<CauHoi>(noiDung);
    }
    
    string timCauTraLoi(const CauHoi& cauHoi) {
        // Tìm trong kho kiến thức
        shared_ptr<CauTraLoi> cauTraLoi = khoKienThuc->timCauTraLoi(cauHoi.getTuKhoa());
        
        if (cauTraLoi) {
            string ketQua = cauTraLoi->getNoiDung();
            
            // Nếu độ tin cậy thấp, thêm cảnh báo
            if (cauTraLoi->getDoTinCay() < 0.7) {
                ketQua += "\n(Lưu ý: Thông tin này có thể chưa chính xác hoàn toàn)";
            }
            return ketQua;
        } else {
            // Trả về câu trả lời mặc định ngẫu nhiên
            return cauTraLoiMacDinh[dis(gen)];
        }
    }
    
    void hocTuPhanHoi(const string& cauHoiStr, const string& cauTraLoiDung, float doTinCay = 0.8) {
        auto cauHoi = phanTichCauHoi(cauHoiStr);
        auto cauTraLoiMoi = make_shared<CauTraLoi>(cauTraLoiDung, doTinCay, "Người dùng");
        khoKienThuc->themKienThuc(cauHoi->getTuKhoa(), cauTraLoiMoi);
        cout << "✓ Đã học kiến thức mới!" << endl;
    }
    
    string troChuyen(const string& noiDungNguoiDung) {
        // Phân tích câu hỏi
        auto cauHoi = phanTichCauHoi(noiDungNguoiDung);
        
        // Tìm câu trả lời
        string cauTraLoi = timCauTraLoi(*cauHoi);
        
        // Lưu lịch sử
        lichSuTroChuyen.push_back(make_tuple(
            time(nullptr),
            noiDungNguoiDung,
            cauTraLoi,
            cauHoi->getLoaiCauHoi()
        ));
        
        return cauTraLoi;
    }
    
    void xemLichSu(int soLuong = 5) {
        cout << "\n=== Lịch sử " << soLuong << " cuộc trò chuyện gần nhất ===" << endl;
        
        int start = max(0, (int)lichSuTroChuyen.size() - soLuong);
        for (int i = start; i < lichSuTroChuyen.size(); i++) {
            time_t thoiGian = get<0>(lichSuTroChuyen[i]);
            tm* timeInfo = localtime(&thoiGian);
            
            cout << "\n[" << put_time(timeInfo, "%H:%M:%S") << "]" << endl;
            cout << "👤 Người: " << get<1>(lichSuTroChuyen[i]) << endl;
            cout << "🤖 Bot: " << get<2>(lichSuTroChuyen[i]) << endl;
            cout << "(Loại câu hỏi: " << get<3>(lichSuTroChuyen[i]) << ")" << endl;
        }
    }
    
    void thongKePhien() {
        cout << "\n=== Thống kê phiên làm việc ===" << endl;
        cout << "Tên bot: " << tenBot << endl;
        cout << "Số lượt trò chuyện: " << lichSuTroChuyen.size() << endl;
        
        if (!lichSuTroChuyen.empty()) {
            // Thống kê loại câu hỏi
            map<string, int> loaiCauHoiCount;
            for (const auto& item : lichSuTroChuyen) {
                loaiCauHoiCount[get<3>(item)]++;
            }
            
            cout << "\nPhân loại câu hỏi:" << endl;
            for (const auto& pair : loaiCauHoiCount) {
                cout << "  - " << pair.first << ": " << pair.second << " câu" << endl;
            }
        }
        
        // Thống kê kho kiến thức
        khoKienThuc->thongKeKienThuc();
    }
    
    string getTenBot() const { return tenBot; }
};

// ==================== Hàm Demo ====================
void demoChatbot() {
    cout << "============================================================" << endl;
    cout << "           CHATBOT HỎI ĐÁP ĐƠN GIẢN (C++)                " << endl;
    cout << "============================================================" << endl;
    
    // Khởi tạo chatbot
    ChatBot bot("AI Assistant");
    
    cout << "\n🤖 Xin chào! Tôi là " << bot.getTenBot() << endl;
    cout << "Tôi có thể trả lời về: thời tiết, thể thao, ẩm thực, công nghệ" << endl;
    cout << "Gõ 'thoát' để kết thúc, 'lịch sử' để xem lịch sử chat" << endl;
    cout << "Gõ 'học: <câu hỏi> | <câu trả lời>' để dạy tôi kiến thức mới" << endl;
    cout << "------------------------------------------------------------" << endl;
    
    string nguoiDung;
    while (true) {
        cout << "\n👤 Bạn: ";
        getline(cin, nguoiDung);
        
        // Chuyển thành chữ thường để so sánh lệnh
        string lenh = nguoiDung;
        transform(lenh.begin(), lenh.end(), lenh.begin(), ::tolower);
        
        // Kiểm tra lệnh đặc biệt
        if (lenh == "thoát" || lenh == "thoat" || lenh == "exit" || lenh == "quit") {
            cout << "\n🤖 " << bot.getTenBot() << ": Tạm biệt! Hẹn gặp lại bạn!" << endl;
            bot.thongKePhien();
            break;
        }
        else if (lenh == "lịch sử" || lenh == "lich su" || lenh == "history") {
            bot.xemLichSu();
            continue;
        }
        else if (lenh.substr(0, 4) == "học:" || lenh.substr(0, 4) == "hoc:") {
            // Xử lý học kiến thức mới
            size_t colonPos = nguoiDung.find(':');
            size_t pipePos = nguoiDung.find('|');
            
            if (colonPos != string::npos && pipePos != string::npos && pipePos > colonPos) {
                string cauHoi = nguoiDung.substr(colonPos + 1, pipePos - colonPos - 1);
                string cauTraLoi = nguoiDung.substr(pipePos + 1);
                
                // Trim whitespace
                cauHoi.erase(0, cauHoi.find_first_not_of(" \t"));
                cauHoi.erase(cauHoi.find_last_not_of(" \t") + 1);
                cauTraLoi.erase(0, cauTraLoi.find_first_not_of(" \t"));
                cauTraLoi.erase(cauTraLoi.find_last_not_of(" \t") + 1);
                
                bot.hocTuPhanHoi(cauHoi, cauTraLoi);
            } else {
                cout << "❌ Định dạng không đúng. Dùng: học: <câu hỏi> | <câu trả lời>" << endl;
            }
            continue;
        }
        else if (nguoiDung.empty()) {
            continue;
        }
        
        // Xử lý câu hỏi thông thường
        string cauTraLoi = bot.troChuyen(nguoiDung);
        cout << "🤖 " << bot.getTenBot() << ": " << cauTraLoi << endl;
    }
}

// ==================== Hàm chính ====================
int main() {
    // Thiết lập encoding cho tiếng Việt (Windows)
    #ifdef _WIN32
        system("chcp 65001 > nul");
    #endif
    
    // Demo các lớp riêng lẻ
    cout << "\n=== DEMO CÁC THÀNH PHẦN CỦA CHATBOT ===" << endl;
    cout << "\n1. Demo lớp CauHoi:" << endl;
    cout << "-------------------" << endl;
    CauHoi ch1("Thời tiết hôm nay thế nào?");
    ch1.hienThi();
    
    cout << "\n2. Demo lớp CauTraLoi:" << endl;
    cout << "----------------------" << endl;
    CauTraLoi ctl1("Hôm nay trời nắng đẹp", 0.9, "Dự báo thời tiết");
    ctl1.hienThi();
    
    cout << "\n3. Demo lớp KhoKienThuc:" << endl;
    cout << "------------------------" << endl;
    KhoKienThuc kkt("Demo");
    kkt.thongKeKienThuc();
    
    cout << "\n============================================" << endl;
    cout << "Nhấn Enter để bắt đầu chat với bot..." << endl;
    cin.get();
    
    // Chạy demo chatbot
    demoChatbot();
    
    return 0;
}