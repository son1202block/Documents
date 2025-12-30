#ifndef PPORT_H
#define PPORT_H

class ParallelPort
{
protected:
    unsigned int BaseAddress;
public:
    explicit ParallelPort(unsigned int baseAddress = 0x378)
        : BaseAddress(baseAddress) {}
    virtual ~ParallelPort() {}
    // Minimal stub to allow code2chuong10.cpp to compile; replace with real I/O later
    virtual unsigned char ReadPort1() const { return 0; }
};

#endif // PPORT_H


