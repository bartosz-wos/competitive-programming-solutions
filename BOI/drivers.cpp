#include <bits/stdc++.h>
using namespace std;

int p[200005];

int parent(int n) {
    if (p[n] == n) return n;
    return p[n] = parent(p[n]);
}

void merge(int x, int y) {
    x = parent(x); y = parent(y);
    if (x == y) return;
    p[x] = y;
}

int main() {
    int n, m, u; cin >> n >> m >> u;
    vector <pair<int, pair<int, int>>> edges;
    for (int i = 0; i < m; i++) {
        int x, y, w; cin >> x >> y >> w;
        edges.push_back({w, {x, y}});
    }
    sort(edges.begin(), edges.end());
    for (int i = 1; i <= n; i++) p[i] = i;
    vector <pair<pair<int, int>, pair<int, int>>> query;
    int ans[u];
    for (int i = 0; i < u; i++) {
        int x, y, dist; cin >> x >> y >> dist;
        query.push_back({{dist, i}, {x, y}});
    }
    sort(query.begin(), query.end());
    int idx = 0;
    for (int i = 0; i < u; i++) {
        while (idx < m and edges[idx].first <= query[i].first.first) {
            merge(edges[idx].second.first, edges[idx].second.second);
            idx++;
        }
        if (parent(query[i].second.first) == parent(query[i].second.second)) ans[query[i].first.second] = 1;
        else ans[query[i].first.second] = 0;
    }
    for (int i = 0; i < u; i++) {
        if (ans[i] == 0) cout << "NE" << '\n';
        else cout << "TAIP" << '\n';
    }
}
