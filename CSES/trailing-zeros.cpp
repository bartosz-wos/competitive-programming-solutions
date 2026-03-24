#include <iostream>
using namespace std;
 
 
int pow[21], ans;
int main() {
    pow[0] = 0;
    pow[1] = 5;
 
    for(int i = 2; i < 21; ++i)
        pow[i] = pow[i - 1] * 5;
    int n;
    cin >> n;
 
    for(int i = 1; pow[i] <= n; ++i)
        ans += n / pow[i];
 
    cout << ans;
}
