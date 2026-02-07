#include<bits/stdc++.h>
using namespace std;
int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n, m;
    cin>>n>>m;
    vector<bitset<1001>>E(n+1);
    while(m--){
        int u, v;
        cin>>u>>v;
        E[u][v]=E[v][u]=1;
    }
    E[1][1]=1;
    for(int i=1;i<=n;i++)
        for(int j=1;j<i;j++)
            if((E[1][i]^E[1][j])==E[i][j])
                return cout<<"NE", 0;
    cout<<"DA";
}

