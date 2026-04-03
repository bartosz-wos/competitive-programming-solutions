#include <bits/stdc++.h>
using namespace std;
 
int par[100007];
int dist[100007];
int ind[100007];
vector<int> edge[100007];
vector<int> backEdge[100007];
 
int N, M, a, b;
 
void solve() {
    queue<int> Q;
    for(int i = 0; i < N; i++)
        if(!ind[i])
            Q.push(i);
 
    int u = 0;
    while(!Q.empty()) {
        u = Q.front();
        Q.pop();
 
        for(const int& i : edge[u])
            if(--ind[i] == 0)
                Q.push(i);
 
        int mx = -999999999;
        int mx_node = -1;
        for(int prev : backEdge[u]) {
            if(dist[prev] + 1 > mx) {
                mx = dist[prev] + 1;
                mx_node = prev;
            }
        }
 
        dist[u] = mx;
        if(u == 0) dist[u] = 1;
        par[u] = mx_node;
    }
 
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> N >> M;
    for(int i = 0; i < N; ++i) {
        dist[i] = -999999999;
        par[i] = -1;
    }
 
    while(M--) {
        cin >> a >> b;
        a--, b--;
        ind[b]++;
        edge[a].push_back(b);
        backEdge[b].push_back(a);
    }
 
    solve();
 
    stack<int> ans;
    int temp = N - 1;
 
    bool contains = false;
    if(temp == 0) contains = true;
 
    while(temp != -1 && dist[temp] >= 0) {
        ans.push(temp);
        temp = par[temp];
        if(temp == 0) contains = true;
    }
 
    if(contains) {
        cout << dist[N - 1] << "\n";
        while(!ans.empty()) {
            cout << ans.top() + 1 << ' ';
            ans.pop();
        }
    }
    else
        cout << "IMPOSSIBLE\n";
}

