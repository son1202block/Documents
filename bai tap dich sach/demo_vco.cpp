#include <iostream>
#include "vco.h"
int main(){
    VCO vco;
    std::cout << "VCO demo OK\n";
    std::cout << "Period: " << vco.GetPeriod() << "\n";
    return 0;
}
