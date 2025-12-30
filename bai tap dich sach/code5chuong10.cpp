#include <conio.h>
#include <stdio.h>
#include "dac.h"
#include "vco.h"

int main()
{
    DAC dacController;
    VCO vcoController;
    bool programRunning = true;
    int keyPressed;
    unsigned char currentDACValue;
    
    // Initialize DAC
    dacController.SendData(0);
    
    // Main program loop
    while(programRunning)
    {
        // Display pulse period measurement
        long periodValue = vcoController.MeasurePeriod();
        printf("\rThe pulse period is %10lu   ", periodValue / 1000);
        fflush(stdout);
        
        // Check for keyboard input (non-blocking)
        if(kbhit())
        {
            currentDACValue = dacController.GetLastOutput();
            keyPressed = getch();
            
            switch(keyPressed)
            {
                case 27:  // ESC pressed
                    programRunning = false;
                    break;
                    
                case 72:  // Up Arrow (getch may return 224 then code)
                    {
                        unsigned char newValue = currentDACValue + 8;
                        if(currentDACValue > 247)  // Prevent overflow
                            newValue = 247;
                        dacController.SendData(newValue);
                    }
                    break;
                    
                case 80:  // Down Arrow
                    {
                        unsigned char newValue = currentDACValue - 8;
                        if(currentDACValue < 8)   // Prevent underflow
                            newValue = 8;
                        dacController.SendData(newValue);
                    }
                    break;
                    
                default:
                    // Ignore other keys
                    break;
            }
        }
    }
    return 0;
}
