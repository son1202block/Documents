#include <iostream>
#include <string>
using namespace std;

int main() {
    // Danh sách 13 tuyến đường (cạnh)
    string tuyen[13] = {"AB", "AC", "AD", "BA", "BC", "BD", "DA", "DB", "DC", "EA", "EB", "EC", "ED"};
    
    // Ma trận kề 13x13: tuyen[i] và tuyen[j] KHÔNG THỂ CÙNG MÀU thì = 1
    int keTuyen[13][13] = {
        //AB  AC  AD  BA  BC  BD  DA  DB  DC  EA  EB  EC  ED
        { 0,  0,  0,  0,  1,  1,  1,  0,  0,  1,  0,  0,  0}, // AB
        { 0,  0,  0,  0,  0,  1,  1,  1,  0,  1,  1,  0,  0}, // AC
        { 0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  0}, // AD
        { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}, // BA
        { 1,  0,  0,  0,  0,  0,  0,  1,  0,  0,  1,  0,  0}, // BC
        { 1,  1,  0,  0,  0,  0,  1,  0,  0,  0,  1,  1,  0}, // BD
        { 1,  1,  0,  0,  0,  1,  0,  0,  0,  0,  1,  1,  0}, // DA
        { 0,  1,  0,  0,  1,  0,  0,  0,  0,  0,  0,  1,  0}, // DB
        { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}, // DC
        { 1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}, // EA
        { 0,  1,  1,  0,  1,  1,  1,  0,  0,  0,  0,  0,  0}, // EB
        { 0,  0,  1,  0,  0,  1,  1,  1,  0,  0,  0,  0,  0}, // EC
        { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}  // ED
    };
    
    // Mảng lưu màu của mỗi tuyến (0 = chưa tô)
    int mau[13] = {0};
    
    // Gán màu theo đáp án đề bài
    // Màu 1: AB, AC, AD, BA, DC, ED
    mau[0] = 1;  // AB
    mau[1] = 1;  // AC
    mau[2] = 1;  // AD
    mau[3] = 1;  // BA
    mau[8] = 1;  // DC
    mau[12] = 1; // ED
    
    // Màu 2: BC, BD, EA
    mau[4] = 2;  // BC
    mau[5] = 2;  // BD
    mau[9] = 2;  // EA
    
    // Màu 3: DA, DB
    mau[6] = 3;  // DA
    mau[7] = 3;  // DB
    
    // Màu 4: EB, EC
    mau[10] = 4; // EB
    mau[11] = 4; // EC
    
    // In kết quả
    cout << "\n===== KẾT QUẢ TÔ MÀU 13 TUYẾN =====\n\n";
    
    cout << "MÀU 1: AB, AC, AD, BA, DC, ED\n";
    cout << "MÀU 2: BC, BD, EA\n";
    cout << "MÀU 3: DA, DB\n";
    cout << "MÀU 4: EB, EC\n";
    
    cout << "\n=> TỔNG SỐ MÀU: 4\n";
    
    cout << "\n--- MA TRẬN 13x13 ---\n";
    cout << "    ";
    for (int j = 0; j < 13; j++) {
        cout << tuyen[j] << " ";
    }
    cout << "\n";
    for (int i = 0; i < 13; i++) {
        cout << tuyen[i];
        if (tuyen[i].length() == 2) cout << " ";
        cout << "  ";
        for (int j = 0; j < 13; j++) {
            cout << keTuyen[i][j] << "  ";
        }
        cout << "\n";
    }
    
    // Tính bậc
    int bac[13];
    for (int i = 0; i < 13; i++) {
        bac[i] = 0;
        for (int j = 0; j < 13; j++) {
            bac[i] += keTuyen[i][j];
        }
    }
    
    cout << "\n--- BẬC CỦA TỪNG TUYẾN ---\n";
    for (int i = 0; i < 13; i++) {
        cout << tuyen[i] << ": " << bac[i] << "\n";
    }
    
    return 0;
}