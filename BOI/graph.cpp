#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const double EPS = 1e-9;
struct Edge { int to, col; };
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<vector<Edge>> adj(n);
    for(int i=0;i<m;i++){
        int u, v, c; cin >> u >> v >> c;
        u--; v--;
        adj[u].push_back({v, c});
        adj[v].push_back({u, c});
    }
    vector<int> comp(n, -1);
    vector<double> A(n, 0.0), B(n, 0.0), ans(n, 0.0);
    int compID = 0;
    bool ok = true;
    for(int i=0;i<n;i++){
        if(comp[i] != -1) continue;
        vector<int> nodes;
        vector<double> cvals;
        bool fixedFlag = false;
        double fixedT = 0;
        queue<int>q;
        comp[i] = compID;
        A[i] = 1; B[i] = 0;
        q.push(i);
        nodes.push_back(i);
        while(!q.empty() && ok){
            int u = q.front(); q.pop();
            for(auto &e: adj[u]){
                int v = e.to; int col = e.col;
                double sum = (col==1 ? 1.0 : 2.0);
                if(comp[v] == -1){
                    comp[v] = compID;
                    A[v] = -A[u];
                    B[v] = sum - B[u];
                    q.push(v);
                    nodes.push_back(v);
                } else {
                    double coeff = A[u] + A[v];
                    double sumb = B[u] + B[v];
                    if(fabs(coeff) < EPS){
                        if(fabs(sumb - sum) > 1e-6) { ok = false; break; }
                    } else {
                        double tval = (sum - sumb) / coeff;
                        if(!fixedFlag){
                            fixedFlag = true;
                            fixedT = tval;
                        } else {
                            if(fabs(fixedT - tval) > 1e-6){ ok = false; break; }
                        }
                    }
                }
            }
        }
        if(!ok) break;
        if(fixedFlag){
            for(auto u: nodes)
                ans[u] = A[u]*fixedT + B[u];
        } else {
            for(auto u: nodes){
                if(fabs(A[u]-1) < EPS)
                    cvals.push_back(-B[u]);
                else
                    cvals.push_back(B[u]);
            }
            sort(cvals.begin(), cvals.end());
            double t;
            int sz = cvals.size();
            if(sz % 2 == 1) t = cvals[sz/2];
            else t = (cvals[sz/2-1] + cvals[sz/2]) / 2.0;
            for(auto u: nodes)
                ans[u] = A[u]*t + B[u];
        }
        compID++;
    }
    if(!ok) { cout << "NO\n"; return 0; }
    cout << "YES\n";
    cout << fixed << setprecision(9);
    for(int i=0;i<n;i++){
        cout << ans[i] << (i==n-1? "\n" : " ");
    }
    return 0;
}
