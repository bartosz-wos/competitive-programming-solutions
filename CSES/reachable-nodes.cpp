#include<iostream>
#include<bitset>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
using ll = long long;
constexpr int maxN = 5e4 + 1;
 
static int n, m;
static bitset<maxN> ans[maxN];
static vector<int> g[maxN];
static bitset<maxN> vis;
static vector<int> order;
static int ind[maxN];
 
void toposort() {
    queue<int> Q;
    for (int i = 1; i <= n; ++i)
        if (!ind[i])
            Q.push(i);
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        order.push_back(u);
        for (const int& i : g[u])
            if (--ind[i] == 0)
                Q.push(i);
    }
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> m;
    while (m--) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        ++ind[b];
    }
    for (int i = 1; i <= n; ++i)
        ans[i].set(i);
    toposort();
    for (int i = order.size() - 1; i >= 0; --i)
        for (const int& j : g[order[i]])
            ans[order[i]] |= ans[j];
    for (int i = 1; i <= n; ++i)
        cout << ans[i].count() << ' ';
}
