/*****************************************************
Lớp đối tượng cơ bản ParallelPort được mở rộng để
bao gồm cổng đầu vào tại địa chỉ BASE+1. Đối tượng kết hợp
vẫn được đặt tên ParallelPort và được sử dụng để ghi
vào cổng tại địa chỉ BASE và đọc dữ liệu từ cổng
tại địa chỉ BASE+1.
*****************************************************/
#include <stdio.h>
#include <dos.h>
#include <windows.h>
#include <iostream>

#if defined(_MSC_VER)
#define outportb(port, data) _outp((unsigned short)(port), (int)(data))
#define inportb(port) ((unsigned char)_inp((unsigned short)(port)))
#else
#define outportb(port, data) ((void)0)
#define inportb(port) ((unsigned char)0)
#endif

using namespace std;

typedef void (__stdcall *Out32Ptr)(short, short);
typedef void (__stdcall *DlPortWritePortUcharPtr)(unsigned short, unsigned char);
typedef short (__stdcall *Inp32Ptr)(short);
typedef unsigned char (__stdcall *DlPortReadPortUcharPtr)(unsigned short);

static Out32Ptr gOut32 = nullptr;
static DlPortWritePortUcharPtr gDlPortWritePortUchar = nullptr;
static Inp32Ptr gInp32 = nullptr;
static DlPortReadPortUcharPtr gDlPortReadPortUchar = nullptr;

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
    gInp32 = (Inp32Ptr)GetProcAddress(lib, "Inp32");
    gDlPortReadPortUchar = (DlPortReadPortUcharPtr)GetProcAddress(lib, "DlPortReadPortUchar");
    return (gOut32 || gDlPortWritePortUchar) && (gInp32 || gDlPortReadPortUchar);
}
class ParallelPort
{
private:
    unsigned int DiaChiCoBan;
    unsigned char DuLieuVaoCong1;
public:
    ParallelPort();
    ParallelPort(int diachicoban);
    void GhiCong0(unsigned char dulieu);
    unsigned char DocCong1();
};
ParallelPort::ParallelPort()
{
    DiaChiCoBan = 0x378;
    DuLieuVaoCong1 = 0;
}
ParallelPort::ParallelPort(int diachicoban)
{
    DiaChiCoBan = diachicoban;
    DuLieuVaoCong1 = 0;
}
void ParallelPort::GhiCong0(unsigned char dulieu)
{
    if (gOut32)
    {
        gOut32((short)DiaChiCoBan, (short)dulieu);
        return;
    }
    if (gDlPortWritePortUchar)
    {
        gDlPortWritePortUchar((unsigned short)DiaChiCoBan, dulieu);
        return;
    }
    outportb(DiaChiCoBan, dulieu);
}
unsigned char ParallelPort::DocCong1()
{
    if (gInp32)
    {
        DuLieuVaoCong1 = (unsigned char)gInp32((short)(DiaChiCoBan + 1));
    }
    else if (gDlPortReadPortUchar)
    {
        DuLieuVaoCong1 = gDlPortReadPortUchar((unsigned short)(DiaChiCoBan + 1));
    }
    else
    {
        DuLieuVaoCong1 = inportb(DiaChiCoBan+1);
    }
    // Đảo bit có trọng số cao nhất để bù trừ cho
    // sự đảo ngược nội bộ bởi phần cứng cổng máy in.
    DuLieuVaoCong1 ^= 0x80;
    // Lọc để xóa các bit dữ liệu không sử dụng D0, D1 và D2 thành không.
    DuLieuVaoCong1 &= 0xF8;
    return DuLieuVaoCong1;
}
int main()
{
    unsigned char DuLieuBASE1;
    ParallelPort CongCuaChungTa;
    bool ok = InitializeInpOut();
    cout << "InpOut initialized: " << (ok ? "yes" : "no") << endl;
    CongCuaChungTa.GhiCong0(255);
    DuLieuBASE1 = CongCuaChungTa.DocCong1();
    printf("\nDu lieu doc tu Cong tai BASE+1: %2X\n", DuLieuBASE1);
    return 0;
}
