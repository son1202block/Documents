#include "vco.h"

VCO::VCO(int baseaddress, BITNUMBER bit) : ParallelPort(baseaddress)
{
    this->Bit = bit;
    this->Period = 0L;
}

long int VCO::MeasurePeriod()
{
    unsigned char currentLevel;
    unsigned char previousLevel;
    
    // Reset period counter
    Period = 0;
    
    // Wait for first transition
    previousLevel = SignalLevel();
    do {
        currentLevel = SignalLevel();
    } while (currentLevel == previousLevel);
    
    // Count during second transition
    previousLevel = currentLevel;
    do {
        currentLevel = SignalLevel();
        Period++;
    } while (currentLevel == previousLevel);
    
    // Count during third transition  
    previousLevel = currentLevel;
    do {
        currentLevel = SignalLevel();
        Period++;
    } while (currentLevel == previousLevel);
    
    return this->Period;
}

long int VCO::GetPeriod()
{
    return this->Period;
}

int VCO::SignalLevel()
{
    unsigned char portValue = ReadPort1();
    return (portValue & Bit) ? 1 : 0;
}
