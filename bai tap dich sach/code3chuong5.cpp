/*****************************************************
DEMO THÀNH VIÊN DỮ LIỆU PUBLIC
Cảnh báo: Làm cho thành viên dữ liệu public là thực hành kém!
Ví dụ này cho thấy tại sao đóng gói là quan trọng.
Lưu ý: Địa chỉ 0x278 có thể không tồn tại trên tất cả hệ thống.
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
public:    // Đã thay đổi từ private thành public - THỰC HÀNH XẤU!
    unsigned int diaChiCongCoBan;
    
public:
    ParallelPort();
    ParallelPort(unsigned int diaChi);
    void GuiDuLieu(unsigned char giaTri);
    void HienThiTrangThaiCong();
};

ParallelPort::ParallelPort()
{
    diaChiCongCoBan = 0x378;
}

ParallelPort::ParallelPort(unsigned int diaChi)
{
    diaChiCongCoBan = diaChi;
}

void ParallelPort::GuiDuLieu(unsigned char giaTri)
{
    if (gOut32)
    {
        gOut32((short)diaChiCongCoBan, (short)giaTri);
        return;
    }
    if (gDlPortWritePortUchar)
    {
        gDlPortWritePortUchar((unsigned short)diaChiCongCoBan, giaTri);
        return;
    }
    outportb(diaChiCongCoBan, giaTri);
}

void ParallelPort::HienThiTrangThaiCong()
{
    cout << "Địa chỉ cổng hiện tại: 0x" << hex << diaChiCongCoBan << endl;
}

int main()
{
    ParallelPort congKiemThu;
    bool ok = InitializeInpOut();
    cout << "InpOut initialized: " << (ok ? "yes" : "no") << endl;
    congKiemThu.HienThiTrangThaiCong();
    
    // Truy cập trực tiếp vào thành viên dữ liệu public (thực hành kém)
    congKiemThu.diaChiCongCoBan = 0x278;    // Điều này biên dịch được nhưng là thiết kế xấu!
    congKiemThu.HienThiTrangThaiCong();
    congKiemThu.GuiDuLieu(128);
    
    return 0;
}
