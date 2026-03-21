#include <bits/stdc++.h>
using namespace std;
using ll=long long;

const int maxn = 1e6 + 5;

int par[maxn];

int get(int v){
    return par[v] == v ? v : get(par[v]);
}

void uni(int a, int b){
    a = get(a);
    b = get(b);
    par[b] = a;
}

set<pair<int, int>> obj[4 * maxn];

void add(int x, int y, int c, int v = 1, int l = -maxn, int r = maxn){
    obj[v].insert({y, c});
    if(r - l == 1)
        return;
    int m = (l + r) / 2;
    if(x < m)
        add(x, y, c, 2 * v, l, m);
    else
        add(x, y, c, 2 * v + 1, m, r);
}

int get(int x1, int x2, int y1, int y2, int v = 1, int l = -maxn, int r = maxn){
    if(x1 <= l && r <= x2){
        auto it = obj[v].lower_bound({y1, 0});
        if(it != end(obj[v]) && it->first < y2)
            return it->second;
        else
            return -1;
    }
    if(r <= x1 || x2 <= l)
        return -1;
    int m = (l + r) / 2;
    return max(get(x1, x2, y1, y2, 2 * v, l, m), get(x1, x2, y1, y2, 2 * v + 1, m, r));
}


signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    iota(par, par + maxn, 0);
    int q, r;
    cin >> q >> r;
    int dx[] = {2 * r, 2 * r, 0, 0};
    int dy[] = {0, 2 * r, 0, 2 * r};
    for(int i = 0; i < q; i++)
    {
        char t;
        cin >> t;
        int x, y;
        cin >> x >> y;
        if(t == '+')
        {
            tie(x, y) = make_tuple(x + y, x - y);
            for(int z = 0; z < 4; z++)
            {
                int cx = x - dx[z], cy = y - dy[z];
                int c = get(cx, cx + 2 * r + 1, cy, cy + 2 * r + 1);
                if(c >= 0)
                    uni(c, i);
            }
            add(x, y, i);
        }
        else
        {
            x--, y--;
            cout << (get(x) == get(y) ? "DA" : "NET") << endl;
        }
    }
 }

