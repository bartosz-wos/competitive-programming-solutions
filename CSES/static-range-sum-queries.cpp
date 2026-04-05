#include <iostream>
using namespace std;
using ull = unsigned long long;
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
 
    int n, q, p, a , b;
    cin >> n >> q;
 
    ull tab[n + 1];
    tab[0] = 0;
 
    for(int i = 1; i <= n; ++i) {
        cin >> p;
        tab[i] = tab[i - 1] + p;
    }
 
    while(q--) {
        cin >> a >> b;
        cout << tab[b] - tab[a - 1] << '\n';
    }
}
