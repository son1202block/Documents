#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "nhap so nguyen duong n: ";
    cin >> n;

    int sum = 0;
    for (int i=1; i<=n/2; i++) {
        if (n % i == 0) {
            sum += i;
        }
    }

    if (sum == n) {
        cout << n << " la so hoan hao." << endl;
    } else {
        cout << n << " khong phai la so hoan hao." << endl;
    }

    return 0;
}