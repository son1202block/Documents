/*****************************************************
The object class created to use ports at addresses
BASE and BASE+1 has been expanded to include output
through the port at address BASE+2. The combined object
class is still named ParallelPort.
*****************************************************/
#include <dos.h>
#include <conio.h>
#include <stdio.h>
#include <windows.h>

#if defined(_MSC_VER)
#define outportb(port, data) _outp((unsigned short)(port), (int)(data))
#define inportb(port) ((unsigned char)_inp((unsigned short)(port)))
#else
#define outportb(port, data) ((void)0)
#define inportb(port) ((unsigned char)0)
#endif

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
    unsigned int BaseAddress;
    unsigned char InDataPort1;
public:
    ParallelPort();
    ParallelPort(int baseaddress);
    void WritePort0(unsigned char data);
    void WritePort2(unsigned char data);
    unsigned char ReadPort1();
};
ParallelPort::ParallelPort()
{
    BaseAddress = 0x378;
    InDataPort1 = 0;
}
ParallelPort::ParallelPort(int baseaddress)
{
    BaseAddress = baseaddress;
    InDataPort1 = 0;
}
void ParallelPort::WritePort0(unsigned char data)
{
    if (gOut32)
    {
        gOut32((short)BaseAddress, (short)data);
        return;
    }
    if (gDlPortWritePortUchar)
    {
        gDlPortWritePortUchar((unsigned short)BaseAddress, data);
        return;
    }
    outportb(BaseAddress,data);
}
void ParallelPort::WritePort2(unsigned char data)
{
    unsigned char value = (unsigned char)(data ^ 0x0B);
    if (gOut32)
    {
        gOut32((short)(BaseAddress + 2), (short)value);
        return;
    }
    if (gDlPortWritePortUchar)
    {
        gDlPortWritePortUchar((unsigned short)(BaseAddress + 2), value);
        return;
    }
    outportb(BaseAddress+2,value);
}
unsigned char ParallelPort::ReadPort1()
{
    if (gInp32)
    {
        InDataPort1 = (unsigned char)gInp32((short)(BaseAddress + 1));
    }
    else if (gDlPortReadPortUchar)
    {
        InDataPort1 = gDlPortReadPortUchar((unsigned short)(BaseAddress + 1));
    }
    else
    {
        InDataPort1 = inportb(BaseAddress+1);
    }
    // Inverting Most significant bit to compensate
    // for internal inversion by printer port hardware.
    InDataPort1 ^= 0x80;
    // Filter to clear unused data bits D0, D1 and D2 to zero.
    InDataPort1 &= 0xF8;
    return InDataPort1;
}
int main()
{
    unsigned char BASE1Data;
    ParallelPort OurPort;
    bool ok = InitializeInpOut();
    printf("InpOut initialized: %s\n", ok ? "yes" : "no");
    OurPort.WritePort0(0x55);
    printf("\n\nData sent to Port at BASE\n");
    getch();
    BASE1Data = OurPort.ReadPort1();
    printf("\nData read from Port at BASE+1: %2X\n",
        BASE1Data);
    getch();
    OurPort.WritePort2(0x00);
    printf("\nData sent to Port at BASE+2\n");
    getch();
    return 0;
}
