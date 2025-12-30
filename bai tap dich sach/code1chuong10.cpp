// VCO class declarations (header-style)
#ifndef VcoH
#define VcoH
#include "pport.h"
enum BITNUMBER{Bit7=0x80,Bit6=0x40,Bit5=0x20,
Bit4=0x10,Bit3=0x08};
class VCO : public ParallelPort
{
private:
long int Period;
BITNUMBER Bit;
public:
VCO(int baseaddress = 0x378, BITNUMBER bit=Bit3);
long int MeasurePeriod();
long int GetPeriod();
int SignalLevel();
virtual ~VCO(){}
};
#endif
