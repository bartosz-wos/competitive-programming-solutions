#include<bits/stdc++.h>
int n;
int g[1505][1505];

struct DSU{
	int p[1505];
	void init(){memset(p,-1,sizeof(p));}
	int find(int x){
		if(p[x]<0)return x;
		return p[x]=find(p[x]);
	}
	void unite(int a, int b){
		a=find(a);
		b=find(b);
		if(a==b)return;
		p[a]+=p[b];
		p[b]=a;
	}
	int get(int x){return -p[find(x)];}
}dsu;

void initialize(int N){
	n=N;
	dsu.init();
}

int hasEdge(int a, int b){
	a=dsu.find(a);
	b=dsu.find(b);
	++g[a][b],++g[b][a];
	if(g[a][b]==dsu.get(a)*dsu.get(b)){
		dsu.unite(a,b);
		for(int i=0;i<n;++i){
			g[a][i]+=g[b][i];
			g[i][a]+=g[i][b];
		}
		return 1;
	}
	return 0;
}	

