#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int dep[500005];
int ptr[20][500005];

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

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int n,q;
	cin>>n>>q;
	for(int i=1;i<n;++i){
		cin>>ptr[0][i];
		dep[i]=dep[ptr[0][i]]+1;
	}
	for(int i=1;i<20;++i)
		for(int j=0;j<n;++j)
			ptr[i][j]=ptr[i-1][ptr[i-1][j]];
	while(q--){
		int u,v;
		cin>>u>>v;
		cout<<lca(u,v)<<'\n';
	}
}
