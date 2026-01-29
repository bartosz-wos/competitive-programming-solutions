#include <bits/stdc++.h>
using namespace std;
 
#define pi pair<int, int>
#define f first
#define s second
 
int n;
int par[1005][1005], visited[1005][1005];
bool edge[1005][1005];
 
void dfs(int a, int b){
    visited[a][b] = 1;
 
    for(int i = 1; i <= n; i++){
        if(i == a || edge[a][i] || !edge[b][i]) continue;
        
        if(visited[b][i] == 1){
            vector <int> cycle;
            cycle.push_back(b);
            cycle.push_back(a);
 
            while(a != i){
                cycle.push_back(par[a][b]);
                int tmp = par[a][b];
                b = a;
                a = tmp;
            }
 
            int sz = cycle.size();
            int l = 0, r = sz - 1;
 
            for(int j = 0; j < sz; j++){
                for(int k = j + 2; k < sz; k++){
                    if(edge[cycle[j]][cycle[k]]){
                        l = j;
                        r = k;
                        break;
                    }
                }
            }
 
            for(int j = l; j <= r; j++) cout << cycle[j] << " ";
            cout << endl;
 
            exit(0);
        }else if(!visited[b][i]){
            par[b][i] = a;
            dfs(b, i);
        }
    }
    visited[a][b] = 2;
}
 
int main(){
    int r;
    cin >> n >> r;
    vector <pi> edges;
    while(r--){
 
        int a, b; cin >> a >> b;
        edge[a][b] = true;
        edge[b][a] = true;
        edges.push_back({a, b});
    }
 
    for(auto i : edges){
        if(!visited[i.f][i.s]){
            //cout << endl;
            dfs(i.f, i.s);
        }
    }
    cout << "no"<<endl;
}
