#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int n, m;
    cin >> n >> m;
    vector<pair<int,int>> edges(m);
    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        --a; --b;
        edges[i] = {a,b};
    }
 
    int N = 1<<n;
    vector<char> indep(N, 1);
    for(int mask = 0; mask < N; mask++){
        for(auto &e: edges){
            int u = e.first, v = e.second;
            if( (mask & (1<<u)) && (mask & (1<<v)) ){
                indep[mask] = 0;
                break;
            }
        }
    }
 
    const int INF = 1e9;
    vector<int> dp(N, INF), prev(N, 0);
    dp[0] = 0;
 
    for(int mask = 1; mask < N; mask++){
        for(int sub = mask; sub; sub = (sub-1) & mask){
            if(!indep[sub]) continue;
            int cand = dp[mask ^ sub] + 1;
            if(cand < dp[mask]){
                dp[mask] = cand;
                prev[mask] = sub;
            }
        }
    }
 
    int full = N-1;
    int k = dp[full];
    cout << k << "\n";
 
    vector<int> color(n, 0);
    int curMask = full;
    int c = k;
    while(curMask){
        int S = prev[curMask];
        for(int i = 0; i < n; i++){
            if(S & (1<<i)) color[i] = c;
        }
        curMask ^= S;
        c--;
    }
 
    for(int i = 0; i < n; i++){
        cout << color[i] << (i+1<n? ' ':'\n');
    }
    return 0;
}
