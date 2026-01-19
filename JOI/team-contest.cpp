#include <bits/stdc++.h>
 
using namespace std;
    
typedef long long ll;
#define int ll
const int  N = 2e5 + 2, MOD = 998244353;
 
int a[N],b[N],c[N],n;
set<pair<int,int>> x,y,z;
void del(int i) {
    x.erase({a[i],i});
    y.erase({b[i],i});
    z.erase({c[i],i});
}
void test() {
    cin >> n;
    for(int i = 1;i <= n;i++) {
        cin >> a[i] >> b[i] >> c[i];
        x.insert({a[i],i});
        y.insert({b[i],i});
        z.insert({c[i],i});
    }
    while(true) {
        if(x.empty()) {
            cout << -1;
            return;
        }
        auto [v,i] = (*x.rbegin());
        auto [v1,j] = (*y.rbegin());
        auto [v2,k] = (*z.rbegin());
        auto bad = [&](int id)->bool{
            int col = 0;
            if(a[id] == (*x.rbegin()).first) col++;
            if(b[id] == (*y.rbegin()).first) col++;
            if(c[id] == (*z.rbegin()).first) col++;
            if(col > 1) return 1;
            return 0;
        };
        if(i == j && j == k) {
            del(i);
            continue;
        }
        if(i == j || i == k) {
            del(i);
            continue;
        } else if(j == k) {
            del(j);
            continue;
        }
        bool ok = 1;
        if(bad(i)) {
            ok = false;
            del(i);
        }
        if(bad(j)) {
            ok = false;
            del(j);
        }
        if(bad(k)) {
            ok = false;
            del(k);
        }
        if(ok) {
            cout << v + v1 + v2;
            return;
        }
    }
}
signed main() {
    ios_base::sync_with_stdio(false);cin.tie(0);
    int t = 1; 
    // cin >> t;
    while(t--) {
        test();
    }
}  
