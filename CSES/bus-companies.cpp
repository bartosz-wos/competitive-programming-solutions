#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;
 
typedef long long ll;
const ll INF = 1e18;
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int n, m;
    cin >> n >> m;
    vector<int> companyCost(m + 1);
    for (int i = 1; i <= m; i++) {
        cin >> companyCost[i];
    }
    
    int totalNodes = n + m;
    vector<vector<pair<int, ll>>> graph(totalNodes + 1);
 
    for (int i = 1; i <= m; i++) {
        int k;
        cin >> k; 
        vector<int> cities(k);
        for (int j = 0; j < k; j++) {
            cin >> cities[j];
        }
        int companyNode = n + i;
        for (int city : cities) {
            graph[city].emplace_back(companyNode, companyCost[i]);
            graph[companyNode].emplace_back(city, 0);
        }
    }
    
    vector<ll> dist(totalNodes + 1, INF);
    dist[1] = 0;
    priority_queue<pair<ll, int>, vector<pair<ll,int>>, greater<pair<ll,int>>> pq;
    pq.push({0, 1});
    
    while(!pq.empty()){
        auto [d, u] = pq.top();
        pq.pop();
        if(d != dist[u]) continue;
        
        for(auto &edge : graph[u]){
            int v = edge.first;
            ll w = edge.second;
            if(dist[v] > d + w){
                dist[v] = d + w;
                pq.push({dist[v], v});
            }
        }
    }
    
    for (int i = 1; i <= n; i++){
        cout << dist[i] << " ";
    }
    cout << "\n";
    
    return 0;
}
