include<bits/stdc++.h>
using namespace std;
int n, q, a, b;
int tab[200007];
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> q;
    for(int i = 1; i <= n; ++i)
        cin >> tab[i], tab[i] = tab[i-1] ^ tab[i];
    while(q--) {
        cin >> a >> b;
        cout << (tab[b] ^ tab[a-1]) << '\n';
    }
}
