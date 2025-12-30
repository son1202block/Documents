#include <dos.h>
// Modernized includes and InpOut dynamic loader
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
private:
    unsigned int diaChiCongCoBan;
    
public:
    ParallelPort();                     // Hàm khởi tạo mặc định
    ParallelPort(unsigned int diaChi);  // Hàm khởi tạo có tham số
    void GuiDuLieu(unsigned char giaTri);
    void HienThiThongTinCong();
};

// Hàm khởi tạo mặc định - đặt địa chỉ LPT1 chuẩn
ParallelPort::ParallelPort()
{
    diaChiCongCoBan = 0x378;
    cout << "Đối tượng ParallelPort đã được tạo với địa chỉ mặc định: 0x378" << endl;
}

// Hàm khởi tạo có tham số - đặt địa chỉ tùy chỉnh
ParallelPort::ParallelPort(unsigned int diaChi)
{
    diaChiCongCoBan = diaChi;
    cout << "Đối tượng ParallelPort đã được tạo với địa chỉ: 0x" << hex << diaChi << endl;
}

// Gửi dữ liệu đến cổng song song
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
    cout << "Dữ liệu đã gửi: " << dec << (int)giaTri << " (Nhị phân: ";
    for(int i = 7; i >= 0; i--)
        cout << ((giaTri >> i) & 1);
    cout << ")" << endl;
}

// Hiển thị thông tin cổng
void ParallelPort::HienThiThongTinCong()
{
    cout << "Địa chỉ cơ sở của cổng: 0x" << hex << diaChiCongCoBan << endl;
}

int main()
{
    cout << "=== Demo Giao tiếp Cổng Song song ===" << endl;
    bool ok = InitializeInpOut();
    cout << "InpOut initialized: " << (ok ? "yes" : "no") << endl;
    
    ParallelPort congCuaToi;          // Tạo đối tượng với địa chỉ mặc định
    congCuaToi.HienThiThongTinCong(); // Hiển thị thông tin cổng
    congCuaToi.GuiDuLieu(255);        // Gửi giá trị tối đa (tất cả LED sáng)
    
    cout << "\nChương trình hoàn thành thành công." << endl;
    return 0;
}
