#include<bits/stdc++.h>
using namespace std;
using ll=long long;

vector<int>g[500005];

int dep[500005];
int ptr[20][500005];

void dfs(int v, int e){
	for(int i=1;i<20;++i)
		ptr[i][v]=ptr[i-1][ptr[i-1][v]];
	for(const int&u:g[v]){
		if(u==e)continue;
		dep[u]=dep[ptr[0][u]=v]+1;
		dfs(u,v);
	}
}

int kth(int x, int k){
        int j=0;
        while(k){
                if(k&1)x=ptr[j][x];
                ++j;
                k>>=1;
        }
        return x;
}

int lca(int u, int v){
        if(dep[u]<dep[v])swap(u,v);
        u=kth(u,dep[u]-dep[v]);
        if(u==v)return u;
        for(int i=19;i>=0;--i)
                if(ptr[i][u]!=ptr[i][v])
                        u=ptr[i][u],v=ptr[i][v];
        return ptr[0][u];
}

int dist(int u, int v){
	return dep[u]+dep[v]-(dep[lca(u,v)]<<1);
}

int main(){
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
        int n,q;
        cin>>n>>q;
        for(int i=1,a,b;i<n;++i){
		cin>>a>>b;
		g[a].push_back(b);
		g[b].push_back(a);
        }
	dfs(0,-1);
        while(q--){
                int u,v,k;
		cin>>u>>v>>k;
		if(dist(u,v)<k){
			cout<<-1<<'\n';
			continue;
		}
		int l=lca(u,v);
		if(dep[u]-dep[l]>=k)cout<<kth(u,k)<<'\n';
		else cout<<kth(v,dep[v]-(dep[l]<<1)+dep[u]-k)<<'\n';
        }
}
