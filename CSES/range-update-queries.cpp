#include<bits/stdc++.h>
using namespace std;
int n, q, p, a, b, w;
long long T[200007];
 
void add(int a, int val) {
    while(a <= n) {
        T[a] += val;
        a += (a & -a);
    }
}
 
void range_add(int l, int r, int val) {
    add(l, val);
    add(r + 1, -val);
}
 
long long query(int index) {
    long long ans = 0;
    while(index) {
        ans += T[index];
        index -= (index & -index);
    }
    return ans;
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> q;
    for(int i = 1; i <= n; ++i)
        cin >> p, range_add(i, i, p);
    while(q--) {
        cin >> p;
        if(p == 1) {
            cin >> a >> b >> w;
            range_add(a, b, w);
        }
        else {
            cin >> a;
            cout << query(a) << '\n';
        }
    }
}
