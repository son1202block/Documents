#ifndef DAC_H
#define DAC_H

class DAC
{
private:
    unsigned char lastOutput;

public:
    DAC() : lastOutput(0) {}

    void SendData(unsigned char value)
    {
        lastOutput = value;
    }

    unsigned char GetLastOutput() const
    {
        return lastOutput;
    }
};

#endif // DAC_H


