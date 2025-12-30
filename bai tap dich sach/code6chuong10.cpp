/*****************************************************
The frequency of the pulse-train being output by the
voltage-controlled oscillator will change as we change
the analog input voltage to the VCO circuit. The
Potentiometer (POT1) on the interface board generates
the input voltage to the VCO and the program reads the
pulse-train being output by the VCO. This pulse-train
is graphically displayed on-screen.
*****************************************************/
#include <iostream>
#include <conio.h>
#include <chrono>
#include <thread>
#include "vco.h"
int main()
{
VCO Vco;
int i=0; // controls plotting in the x range
int SignalLevel;
const int width = 80;
std::string line(width, ' ');
std::cout << "Press any key to stop...\n";
while(!kbhit())
{
SignalLevel = Vco.SignalLevel();
line[i] = (SignalLevel == 0) ? '_' : '^';
std::cout << '\r' << line << std::flush;
i++;
if(i >= width)
{
i = 0;
std::fill(line.begin(), line.end(), ' ');
}
std::this_thread::sleep_for(std::chrono::milliseconds(20));
}
getch();
return 0;
}
