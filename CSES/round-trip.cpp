#include<bits/stdc++.h>
using namespace std;
vector<int> g[100007], ans;
bitset<100007> vis;
int par[100007];
int n, m, a, b;
 
void dfs(int v, int e) {
    vis[v] = 1;
    par[v] = e;
    for(const int& i : g[v]) {
        if(i == e) continue;
        if(vis[i]) {
            ans.push_back(i);
            while(v != i) {
                ans.push_back(v);
                v = par[v];
            }
            ans.push_back(i);
            cout << ans.size() << '\n';
            for(const int& i : ans)
                cout << i << ' ';
            exit(0);
        }
        else
            dfs(i, v);
    }
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> m;
    while(m--) {
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    for(int i = 1; i <= n; ++i)
        if(!vis[i])
            dfs(i, -1);
    cout << "IMPOSSIBLE";
}
