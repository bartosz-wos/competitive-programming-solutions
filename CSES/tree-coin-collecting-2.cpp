#include<bits/stdc++.h>
using namespace std;
using ll=long long;
#define fi first
#define se second
#define pb push_back
 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n,q;
	if(!(cin>>n>>q))return 0;
	vector<int> coin(n+1);
	int C=0;
	for(int i=1;i<=n;i++){cin>>coin[i]; if(coin[i])C++;}
	vector<vector<int>> g(n+1);
	for(int i=0;i<n-1;i++){int a,b;cin>>a>>b; g[a].pb(b); g[b].pb(a);}
	vector<int> parent(n+1,0),depth(n+1,0),order;
	order.reserve(n);
	parent[1]=1; depth[1]=0;
	vector<int> st; st.pb(1);
	while(!st.empty()){
		int u=st.back(); st.pop_back();
		order.pb(u);
		for(int v:g[u]) if(v!=parent[u]){
			parent[v]=u;
			depth[v]=depth[u]+1;
			st.pb(v);
		}
	}
	vector<int> subs(n+1,0);
	for(int i=(int)order.size()-1;i>=0;i--){
		int u=order[i];
		int s=coin[u];
		for(int v:g[u]) if(v!=parent[u]) s+=subs[v];
		subs[u]=s;
	}
	vector<int> z(n+1,0), t(n+1,0);
	for(int v=2;v<=n;v++){
		z[v] = (subs[v]==0);
		t[v] = (subs[v]==C);
	}
	z[1]=0; t[1]=0;
	vector<int> accz(n+1,0), acct(n+1,0);
	accz[1]=z[1]; acct[1]=t[1];
	for(int u:order){
		for(int v:g[u]) if(v!=parent[u]){
			accz[v]=accz[u]+z[v];
			acct[v]=acct[u]+t[v];
		}
	}
	int LOG=1; while((1<<LOG)<=n)LOG++;
	vector<vector<int>> up(LOG, vector<int>(n+1));
	for(int v=1;v<=n;v++) up[0][v]=parent[v];
	for(int k=1;k<LOG;k++) for(int v=1;v<=n;v++) up[k][v]=up[k-1][ up[k-1][v] ];
	auto lca = [&](int a,int b){
		if(depth[a]<depth[b]) swap(a,b);
		int dif=depth[a]-depth[b];
		for(int k=0;k<LOG;k++) if(dif&(1<<k)) a=up[k][a];
		if(a==b) return a;
		for(int k=LOG-1;k>=0;k--) if(up[k][a]!=up[k][b]){ a=up[k][a]; b=up[k][b]; }
		return parent[a];
	};
	auto dist = [&](int a,int b)->int{
		int c=lca(a,b);
		return depth[a]+depth[b]-2*depth[c];
	};
	int total_z=0,total_t=0;
	for(int v=2;v<=n;v++){ total_z+=z[v]; total_t+=t[v]; }
	for(int i=0;i<q;i++){
		int a,b;cin>>a>>b;
		int L=lca(a,b);
		int cnt_noR = total_z - accz[a] - accz[b] + accz[L];
		bool need_a = (coin[a]==0);
		bool need_b = (coin[b]==0);
		int cnt_allR=0;
		if(!need_a && !need_b) cnt_allR = total_t;
		else if(need_a && !need_b) cnt_allR = acct[a];
		else if(!need_a && need_b) cnt_allR = acct[b];
		else cnt_allR = acct[L];
		int included = (n-1) - cnt_noR - cnt_allR;
		ll ans = 2LL*included - (ll)dist(a,b);
		cout<<ans<<"\n";
	}
	return 0;
}
