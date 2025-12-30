/*****************************************************
This program uses the thermistor on the interface board
to generate a voltage for input to the VCO, and then
repeatedly reads the cycle time of the VCO’s output pulse-
train. It also allows you to calibrate the thermistor so
the program can display the actual temperature.
*****************************************************/
#include <iostream>
#include <conio.h>
#include <cstdio>
#include "vco.h"
int main()
{
VCO Vco;
int Quit=0, HiFlag = 0, LoFlag = 0;
int key = 0;
float HiTemp = 0.0f, LoTemp = 0.0f, Temp = 0.0f;
long int HiCount = 0, LoCount = 0;
std::cout << "Press U to set Upper calibration, D for Lower, ESC to exit.\n";
while(!Quit)
{
Vco.MeasurePeriod();
std::cout << "\r";
if((HiFlag == 1) && (LoFlag == 1))
{
Temp = LoTemp + (HiTemp - LoTemp) *
(static_cast<float>(Vco.GetPeriod() - LoCount) / static_cast<float>(HiCount - LoCount));
std::printf("The temperature is: %7.1f (deg)   ", Temp);
}
else
{
std::printf("The pulse period is: %10lu   ", static_cast<unsigned long>(Vco.GetPeriod()/1000));
}
std::fflush(stdout);
if(kbhit())
{
key = getch();
if(key == 27) { Quit = 1; }
else if(key == 'U' || key == 'u')
{
std::cout << "\nEnter Upper Calibration Temp: ";
std::cin >> HiTemp;
HiCount = Vco.GetPeriod();
HiFlag = 1;
}
else if(key == 'D' || key == 'd')
{
std::cout << "\nEnter Lower Calibration Temp: ";
std::cin >> LoTemp;
LoCount = Vco.GetPeriod();
LoFlag = 1;
}
}
}
return 0;
}
