#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pi=array<ll, 2>;

vector<pi>g[50005];
int ptr[16][50005];
int dep[50005];
ll sum[50005];
int tin[50005];
int tr;

void dfs(int v=0, int e=-1){
	tin[v]=tr++;
	for(int i=1;i<16;++i)
		ptr[i][v]=ptr[i-1][ptr[i-1][v]];
	for(const auto&[u, w]:g[v]){
		if(u==e)continue;
		dep[u]=dep[ptr[0][u]=v]+1;
		sum[u]=sum[v]+w;
		dfs(u,v);
	}
}

int jump(int v, int k){
	int j=0;
	while(k){
		if(k&1)
			v=ptr[j][v];
		++j;
		k>>=1;
	}
	return v;
}

int lca(int a, int b){
	if(dep[a]<dep[b])
		swap(a,b);
	a=jump(a,dep[a]-dep[b]);
	if(a==b)return a;
	for(int i=15;i>=0;--i)
		if(ptr[i][a]^ptr[i][b])
			a=ptr[i][a],b=ptr[i][b];
	return ptr[0][a];
}

ll dist(int a, int b){
	return sum[a]+sum[b]-2*sum[lca(a,b)];
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int n;
	cin>>n;
	for(int i=1,a,b,w;i<n;++i){
		cin>>a>>b>>w;
		g[a].push_back({b,w});
		g[b].push_back({a,w});
	}

	dfs();

	int q;
	cin>>q;
	while(q--){
		vector<int>v(5);
		for(int&i:v)cin>>i;
		sort(v.begin(),v.end(),[&](int a, int b){return tin[a]<tin[b];});
		ll ret=0;
		int cur=0;
		for(int _=0;_<5;++_,++cur)
			ret+=dist(v[cur],v[(cur+1)%5]);
		cout<<ret/2<<'\n';
	}
}
