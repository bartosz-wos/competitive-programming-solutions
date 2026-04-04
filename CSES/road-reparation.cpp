#include<bits/stdc++.h>
using namespace std;
using ll = long long;
int n, m;
ll ans;
struct Edge {
    int src = 0, dest = 0, weight = 0;
    bool operator<(Edge other) {
        return weight < other.weight;
    }
};
vector<Edge> g;
 
struct DSU {
    vector<int> tab;
    void init(int x) { tab.resize(x + 1, -1); }
    int get(int x) {return tab[x] < 0 ? x : tab[x] = get(tab[x]);}
    bool sameSet(int a, int b) {return get(a) == get(b);}
    int size(int a) {return -tab[get(a)];}
    bool Union(int a, int b) {
        a = get(a);
        b = get(b);
        if(a == b) return 0;
        if(tab[a] > tab[b])
            swap(a, b);
        tab[a] += tab[b];
        tab[b] = a;
        return 1;
    }
};
 
bool kruskal() {
    sort(g.begin(), g.end());
    int cnt = 0;
    DSU d;
    d.init(n + 1);
    for(const Edge& i : g) {
        if(d.Union(i.src, i.dest)) {
            ans += i.weight;
            ++cnt;
        }
    }
    return cnt == n - 1;
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> m;
    g.resize(m);
    for(int i = 0; i < m; ++i)
        cin >> g[i].src >> g[i].dest >> g[i].weight;
 
    if(kruskal())
        cout << ans;
    else
        cout << "IMPOSSIBLE";
}
