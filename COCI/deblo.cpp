//#pragma GCC optimize("O3,unroll-loops,Ofast")
//#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")
#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
//using namespace __gnu_pbds;
 
#define MAX 200007
#define pb push_back
#define mp make_pair 
#define int long long
#define f first
#define s second
#define vi vector<int>
#define pii pair<int,int>
#define si set<int>
#define vpii vector<pair<int,int>> 
const int mod = 1e9+7;
const int INF = 1e18;
// myMap.begin()->first :  key
// myMap.begin()->second : value
 
int epow(int a,int b){int ans=1;while(b){if(b&1) ans*=a;a*=a;;b>>=1;}return ans;}
int gcd(int a,int b) {if(a<b)swap(a,b);while(b){int tmp=b;b=a%b;a=tmp;}return a;}
int mul(int a,int b){return ((a%mod)*(b%mod))%mod;}
int sum(int a,int b){return ((a%mod)+(b%mod))%mod;}
 
//typedef tree<pii,null_type,less<pii>,rb_tree_tag,tree_order_statistics_node_update>ordered_set;
vi dead(MAX),v(MAX);
vi adj[MAX];
int ans=0;
vector<vi> cnt(4,vi(25));
vi vr;
int sz[MAX];

void dfs(int node,int par){
	sz[node]=1;
	for(auto u : adj[node]){
		if(u==par || dead[u]) continue;
		dfs(u,node);
		sz[node]+=sz[u];
	}
}

int find_centroid(int node,int par,int val){
	for(auto u : adj[node]){
		if(u==par || dead[u]) continue;
		if(sz[u]>val/2) return find_centroid(u,node,val);
	}
	return node;
}


void check(int node,int par,int val){
	ans+=val;
	for(int i=0;i<=22;i++){
		int k = val&(1LL<<i);
		ans += cnt[!k][i] * (1LL<<i);
	}

	vr.pb(val);

	for(auto u : adj[node]){
		if(u==par || dead[u]) continue;
		check(u,node,val^v[u]);
	}


}

void solve(int x){
	dfs(x,x);
	x = find_centroid(x,x,sz[x]);
	dead[x]=true;
	ans+=v[x];

	for(int i=0;i<=22;i++) cnt[0][i]=cnt[1][i]=0;
	for(auto u : adj[x]){
		if(dead[u]) continue;
		vr.clear();
		check(u,x,(v[x]^v[u]));

		for(auto u : vr){
			int k = (u^v[x]);
			for(int i=0;i<=22;i++){
				int e = k&(1LL<<i);
		//		cout<<e<<endl;
				cnt[!!e][i]++;
			}
		}


	}

	for(auto u : adj[x]){
		if(dead[u]) continue;
		solve(u);
	}

	
	return;
}
 
int32_t main() {
//	freopen("hayfeast.in", "r", stdin);
//	freopen("hayfeast.out", "w", stdout);
	ios_base::sync_with_stdio(0);cin.tie(0);   
 
   int t=1;
 //   cin >> t;
 //   while (t--) solve();
 	int n; cin>>n;
	for(int i=1;i<=n;i++) cin>>v[i];

	for(int i=1;i<n;i++){
		int a,b; cin>>a>>b;
		adj[a].pb(b); adj[b].pb(a);
	}

	solve(1);
	cout<<ans<<endl;

    return 0;
}

