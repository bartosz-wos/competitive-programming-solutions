#include <bits/stdc++.h>
using namespace std;
int n, m, a, b;
vector<int> g[100007];
bitset<100007> vis;
bitset<100007> flg;
stack<int> S;
 
bool dfs(int v)
{
    vis[v] = true;
    S.push(v);
    flg[v] = true;
    for(const int& i: g[v]) {
        if(!vis[i] && dfs(i))
            return 1;
 
        if(flg[i]) {
            S.push(i);
            return 1;
        }
    }
    S.pop();
    flg[v] = 0;
    return 0;
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> m;
    while(m--)
        cin >> a >> b, g[a].push_back(b);
    for(int i = 1; i <= n; ++i)
        if(!vis[i] && dfs(i))
            break;
 
    if(S.empty()) {
        cout << "IMPOSSIBLE";
        exit(0);
    }
 
    vector<int> ans;
    int temp = S.top();
    while(!S.empty()) {
        ans.push_back(S.top());
        S.pop();
        if (ans.back() == temp and ans.size() != 1)
            break;
    }
    cout << ans.size() << '\n';
    for(int i = ans.size() - 1; i >= 0; --i)
        cout << ans[i] << ' ';
}
