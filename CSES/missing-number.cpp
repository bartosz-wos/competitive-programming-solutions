#include <iostream>
using namespace std;
 
unsigned long long n, p, sum;
 
int main() {
    cin >> n;
 
    for(int i = 1; i < n; ++i) {
        cin >> p;
        sum += p;
    }
 
    cout << (n * (n + 1) / 2) - sum;

