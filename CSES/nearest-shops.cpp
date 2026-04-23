#include <bits/stdc++.h>
using namespace std;
using pii = pair<int,int>;
struct State {
    int u, shop, dist;
};
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> shops(k);
    vector<char> isShop(n,false);
    for(int i = 0; i < k; i++){
        cin >> shops[i];
        --shops[i];
        isShop[shops[i]] = true;
    }
    vector<vector<int>> adj(n);
    for(int i = 0; i < m; i++){
        int a,b;
        cin >> a >> b;
        --a; --b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
 
    vector<array<pii,2>> best(n);
    vector<int> bestSz(n,0);
 
    vector<State> q;
    q.reserve(2*n);
    int head = 0;
 
    for(int s: shops){
        best[s][0] = {0, s};
        bestSz[s] = 1;
        q.push_back({s, s, 0});
    }
 
    while(head < (int)q.size()){
        auto [u, shop_id, dist] = q[head++];
        for(int v: adj[u]){
            if(bestSz[v] >= 2) 
                continue;
	    bool seen = false;
            for(int i = 0; i < bestSz[v]; i++){
                if(best[v][i].second == shop_id){
                    seen = true;
                    break;
                }
            }
            if(seen) 
                continue;
            best[v][ bestSz[v]++ ] = { dist+1, shop_id };
            if(bestSz[v] == 2 && best[v][0].first > best[v][1].first)
                swap(best[v][0], best[v][1]);
            q.push_back({v, shop_id, dist+1});
        }
    }
 
    vector<int> ans(n, -1);
    for(int u = 0; u < n; u++){
        if(!isShop[u]){
            if(bestSz[u] >= 1)
                ans[u] = best[u][0].first;
        } else {
            if(bestSz[u] >= 2)
                ans[u] = best[u][1].first;
        }
    }
 
    for(int i = 0; i < n; i++){
        cout << ans[i] << (i+1<n? ' ':'\n');
    }
    return 0;
}
