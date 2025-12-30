/*****************************************************
VÍ DỤ ĐÓNG GÓI ĐÚNG CÁCH
Minh họa cách chính xác để thay đổi thành viên dữ liệu private
thông qua các hàm thành viên public.
Điều này duy trì tính toàn vẹn dữ liệu và tuân theo nguyên tắc OOP.
*****************************************************/
#include <dos.h>
#include <windows.h>
#include <iostream>

#if defined(_MSC_VER)
#define outportb(port, data) _outp((unsigned short)(port), (int)(data))
#else
#define outportb(port, data) ((void)0)
#endif

using namespace std;

typedef void (__stdcall *Out32Ptr)(short, short);
typedef void (__stdcall *DlPortWritePortUcharPtr)(unsigned short, unsigned char);

static Out32Ptr gOut32 = nullptr;
static DlPortWritePortUcharPtr gDlPortWritePortUchar = nullptr;

static bool InitializeInpOut()
{
    HMODULE lib = LoadLibraryA("InpOutx64.dll");
    if (!lib)
    {
        lib = LoadLibraryA("InpOut32.dll");
    }
    if (!lib)
    {
        return false;
    }
    gOut32 = (Out32Ptr)GetProcAddress(lib, "Out32");
    gDlPortWritePortUchar = (DlPortWritePortUcharPtr)GetProcAddress(lib, "DlPortWritePortUchar");
    return gOut32 != nullptr || gDlPortWritePortUchar != nullptr;
}

class ParallelPort
{
private:    // Đóng gói đúng cách - dữ liệu được bảo vệ
    unsigned int diaChiCongCoBan;
    bool kiemTraDiaChiHopLe(unsigned int diaChi);
    
public:
    ParallelPort();
    ParallelPort(unsigned int diaChi);
    void GuiDuLieu(unsigned char giaTri);
    void DatDiaChiCong(unsigned int diaChiMoi);     // Cách an toàn để thay đổi địa chỉ
    unsigned int LayDiaChiCong();                   // Cách an toàn để đọc địa chỉ
    void HienThiTrangThai();
};

ParallelPort::ParallelPort()
{
    diaChiCongCoBan = 0x378;
}

ParallelPort::ParallelPort(unsigned int diaChi)
{
    if(kiemTraDiaChiHopLe(diaChi))
        diaChiCongCoBan = diaChi;
    else
        diaChiCongCoBan = 0x378;  // Dự phòng mặc định
}

void ParallelPort::GuiDuLieu(unsigned char giaTri)
{
    if (gOut32)
    {
        gOut32((short)diaChiCongCoBan, (short)giaTri);
    }
    else if (gDlPortWritePortUchar)
    {
        gDlPortWritePortUchar((unsigned short)diaChiCongCoBan, giaTri);
    }
    else
    {
        outportb(diaChiCongCoBan, giaTri);
    }
    cout << "Đã gửi giá trị " << dec << (int)giaTri << " đến cổng 0x" 
         << hex << diaChiCongCoBan << endl;
}

// Phương thức an toàn để thay đổi địa chỉ cổng với kiểm tra
void ParallelPort::DatDiaChiCong(unsigned int diaChiMoi)
{
    if(kiemTraDiaChiHopLe(diaChiMoi))
    {
        diaChiCongCoBan = diaChiMoi;
        cout << "Địa chỉ cổng đã được thay đổi thành: 0x" << hex << diaChiMoi << endl;
    }
    else
    {
        cout << "Địa chỉ không hợp lệ 0x" << hex << diaChiMoi << " - giữ địa chỉ hiện tại" << endl;
    }
}

// Phương thức an toàn để đọc địa chỉ hiện tại
unsigned int ParallelPort::LayDiaChiCong()
{
    return diaChiCongCoBan;
}

void ParallelPort::HienThiTrangThai()
{
    cout << "Trạng thái cổng - Địa chỉ: 0x" << hex << diaChiCongCoBan << endl;
}

// Hàm hỗ trợ private để kiểm tra địa chỉ
bool ParallelPort::kiemTraDiaChiHopLe(unsigned int diaChi)
{
    // Kiểm tra các địa chỉ cổng song song phổ biến
    return (diaChi == 0x378 || diaChi == 0x278 || diaChi == 0x3BC);
}

int main()
{
    cout << "=== Demo Đóng gói Đúng cách ===" << endl;
    bool ok = InitializeInpOut();
    cout << "InpOut initialized: " << (ok ? "yes" : "no") << endl;
    
    ParallelPort congAnToan;
    congAnToan.HienThiTrangThai();
    
    // Cách chính xác để sửa đổi dữ liệu private thông qua giao diện public
    congAnToan.DatDiaChiCong(0x278);     // Địa chỉ hợp lệ
    congAnToan.DatDiaChiCong(0x999);     // Địa chỉ không hợp lệ - sẽ bị từ chối
    
    congAnToan.GuiDuLieu(170);           // Gửi mẫu bit xen kẽ
    
    cout << "Địa chỉ cuối cùng: 0x" << hex << congAnToan.LayDiaChiCong() << endl;
    return 0;
}
