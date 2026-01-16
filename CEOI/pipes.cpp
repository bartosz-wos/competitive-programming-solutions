#include <bits/stdc++.h>
using namespace std;
mt19937 rng(time(0));

const int mxN=1e5+2;
vector<int>adj[mxN];
int ln[mxN],dp[mxN],vv[mxN];

int finde(int&x){
	return x==ln[x]?x:ln[x]=finde(ln[x]);
}

void merge(int u,int v){
	ln[finde(u)]=finde(v);
}

void dfs(int&u,int&p){
	vv[u]=1;
	for(int&v:adj[u]){
		if(!(v^p))
			continue;
		dfs(v,u);
		dp[u]^=dp[v];
	}
}

void res(int&u,int&p){
	vv[u]=1;
	for(int&v:adj[u]){
		if(!(v^p))
			continue;
		res(v,u);
		if(!dp[v])
			cout<<u<<' '<<v<<'\n';
	}
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int n,m;
    cin>>n>>m;

    iota(ln,ln+n+1,0);

    for(int i=0,u,v;i<m;++i){
    	cin>>u>>v;
    	if(finde(u)==finde(v)){
    		int xx=rng();
    		dp[u]^=xx;
    		dp[v]^=xx;
    	}else{
    		merge(u,v);
    		adj[u].push_back(v);
    		adj[v].push_back(u);
    	}
    }

    fill(vv,vv+n+1,0);
    for(int fi=1,u,p;fi<=n;++fi){
    	if(vv[fi])
    		continue;
    	u=fi,p=0;
    	dfs(u,p);
    }

    fill(vv,vv+n+1,0);
    for(int fi=1,u,p;fi<=n;++fi){
    	if(vv[fi])
    		continue;
    	u=fi,p=0;
    	res(u,p);
    }
}
