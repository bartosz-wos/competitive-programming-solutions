#include <iostream>
using namespace std;
 
unsigned long long n;
void solve() {
    while( n != 1) {
        cout << n << ' ';
        if( !(n & 1) )
            n >>= 1;
        else
        n = n * 3 + 1;
    }
    cout << 1;
}
 
int main() {
    cin >> n;
    solve();
 
    return 0;
}
