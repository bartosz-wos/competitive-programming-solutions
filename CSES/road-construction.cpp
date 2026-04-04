#include<bits/stdc++.h>
using namespace std;
int n, q;
 
struct SCC {
    int comps, bigcomp = 1;
    vector<int> tab;
    void init() {
        comps = n;
        tab.resize(n+1, -1);
    }
    int Find(int a) {
        if(tab[a] < 0)
            return a;
        return tab[a] = Find(tab[a]);
    }
    bool same(int a, int b) {
        return Find(a) == Find(b);
    }
    int size(int a) {
        return -tab[Find(a)];
    }
 
    bool Union(int a, int b) {
        a = Find(a), b = Find(b);
        if(a == b) return false;
        if(tab[a] > tab[b]) swap(a, b);
        tab[a] += tab[b];
        bigcomp = max(bigcomp, -tab[a]);
        --comps;
        tab[b] = a;
        return 1;
    }
} graph;
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> q;
    graph.init();
    while(q--) {
        int a, b;
        cin >> a >> b;
        graph.Union(a, b);
        cout << graph.comps << ' ' << graph.bigcomp << '\n';
    }
}
