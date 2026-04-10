#include<bits/stdc++.h>
using namespace std;
int range[1000007], n, p;
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> p;
        ++range[p];
    }
    for(int gcd = 1e6; gcd >= 1; --gcd) {
        int multiples = 0;
        for(int ptr = gcd; ptr <= 1e6; ptr += gcd)
            multiples += range[ptr];
        if(multiples > 1) {
            cout << gcd << '\n';
            exit(0);
        }
    }
}
