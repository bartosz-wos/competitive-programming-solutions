#pragma GCC optimize("Ofast","unroll-all-loops")
#include <bits/stdc++.h>
using namespace std;

#define int long long

typedef complex<int> point;

int cross_product(point a,const point &b) {
    a.imag(-a.imag());
    return (a*b).imag();
}

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N,M;
    cin >> N >> M;
    vector<pair<point,int>> dragons(N);
    for(auto&[a,b]:dragons) {
        int u,v;cin>>u>>v>>b;
        a = {u,v};
    }
    point d1,d2;
    {
        int a,b;cin>>a>>b;
        d1 = {a,b};
        cin>>a>>b;
        d2 = {a,b};
    }
    vector<vector<point>> left(M+1),right(M+1);
    for(auto&[a,b]:dragons) {
        if(cross_product(d2-d1,a-d1)<0)left[b].emplace_back(a);
        else right[b].emplace_back(a);
    }
    map<pair<int,int>,int> lookup;
    int Q;
    cin >> Q;
    for(int i=1;i<=Q;i++) {
        int u,v;cin>>u>>v;
        if(lookup.count({u,v})) {
            cout << lookup[{u,v}] << '\n';
            continue;
        }
        int ans = 0;
        for(point&x:left[u]) {
            for(point&y:left[v]) {
                if(cross_product(y-x,d1-x)>0 and cross_product(y-x,d2-x)<0)ans++;
            }
            for(point&y:right[v]) {
                if(cross_product(y-x,d1-x)>0 and cross_product(y-x,d2-x)<0)ans++;
            }
        }
        for(point&x:right[u]) {
            for(point&y:left[v]) {
                if(cross_product(y-x,d1-x)<0 and cross_product(y-x,d2-x)>0)ans++;
            }
            for(point&y:right[v]) {
                if(cross_product(y-x,d1-x)<0 and cross_product(y-x,d2-x)>0)ans++;
            }
        }
        cout << ans << '\n';
        lookup[{u,v}]=ans;
    }
}
