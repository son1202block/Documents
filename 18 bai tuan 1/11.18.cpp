#include <iostream>
#include <cmath> 
using namespace std;

int main() {
    const double EPS = 0.001; // sai so yeu cau
    double pi = 0.0;
    double term;
    double denom = 1.0;
    int sign = 1;
    long long steps = 0;

    do {
        term = sign * (4.0 / denom); 
        pi += term;
        denom += 2.0;
        sign = -sign;
        ++steps;
    } while (fabs(term) >= EPS);

    cout.setf(ios::fixed);
    cout.precision(6);
    cout << "Pi xap xi = " << pi << "\n";
    cout << "so hang da cong: " << steps << "\n";
    
    return 0;
}