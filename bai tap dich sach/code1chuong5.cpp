#include <dos.h>
#include <conio.h>
#include <windows.h>
#include <iostream>

#if defined(_MSC_VER) && !defined(_WIN64)
#define outportb(port, data) _outp((unsigned short)(port), (int)(data))
#else
/* Non-MSVC toolchains or MSVC x64 builds: make outportb a no-op to avoid undefined reference */
#define outportb(port, data) ((void)0)
#endif
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
    unsigned int BaseAddress;
public:
    ParallelPort(unsigned int baseAddress = 0x378)
    {
        BaseAddress = baseAddress;
    }
    void WritePort0(unsigned char data)
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
};

int main()
{
    std::cout << "Program started" << std::endl;
    bool ok = InitializeInpOut();
    std::cout << "InpOut initialized: " << (ok ? "yes" : "no") << std::endl;
    ParallelPort lpt;
    std::cout << "Writing 0xFF to base 0x" << std::hex << 0x378 << std::dec << std::endl;
    lpt.WritePort0(0xFF);
    std::cout << "Done" << std::endl;
    return 0;
}
