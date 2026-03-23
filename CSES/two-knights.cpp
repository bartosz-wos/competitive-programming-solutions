#include <iostream>
using namespace std;
using ull = unsigned long long;
 
ull n;
int main() {
    cin >> n;
    for (ull i = 1; i <= n; ++i)
        cout << (((i * i) * ((i * i) - 1)) >> 1) - (4 * (i - 1) * (i - 2)) << '\n';
}
