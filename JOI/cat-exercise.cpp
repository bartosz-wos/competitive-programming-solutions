

#include <bits/stdc++.h>
#define Loop(x,l,r) for (ll x = (l); x < (ll)(r); ++x)
#define LoopR(x,l,r) for (ll x = (r)-1; x >= (ll)(l); --x)
typedef long long ll;
typedef std::pair<int, int> pii;
typedef std::pair<ll , ll > pll;
using namespace std;
 
const int N = 200'010;
const int lg = 20;
vector<int> A[N];
int val[N];
int anc[N][lg];
int height[N];
 
void dfs1(int v, int p, int h)
{
	anc[v][0] = p;
	Loop (i,0,lg-1)
		anc[v][i+1] = anc[anc[v][i]][i];
	height[v] = h;
	for (int u : A[v])
		if (u != p)
			dfs1(u, v, h+1);
}
 
int lca(int v, int u)
{
	if (height[v] < height[u])
		swap(v, u);
	int diff = height[v] - height[u];
	Loop (i,0,lg)
		if ((diff>>i)&1)
			v = anc[v][i];
	if (v == u)
		return v;
	LoopR (i,0,lg) {
		if (anc[v][i] != anc[u][i]) {
			v = anc[v][i];
			u = anc[u][i];
		}
	}
	return anc[v][0];
}
 
int dis(int v, int u)
{
	return height[v] + height[u] - 2 * height[lca(v, u)];
}
 
namespace dsu {
	int par[N];
	int p2[N];
 
	void init(int n) {
		fill(par, par+n, -1);
		fill(p2, p2+n, -1);
	}
 
	int rt(int v) { return p2[v] == -1? v: (p2[v] = rt(p2[v])); }
 
	void unite(int v, int u) {
		v = rt(v);
		u = rt(u);
		par[u] = v;
		p2[u] = v;
	}
}
 
vector<int> A2[N];
ll ans;
 
void dfs(int v, ll h)
{
	ans = max(ans, h);
	for (int u : A2[v])
		dfs(u, h + dis(v,u));
}
 
int main()
{
	cin.tie(0) -> sync_with_stdio(false);
	int n;
	cin >> n;
	Loop (i,0,n)
		cin >> val[i];
	Loop (i,1,n) {
		int v, u;
		cin >> v >> u;
		v = val[v-1]-1;
		u = val[u-1]-1;
		A[v].push_back(u);
		A[u].push_back(v);
	}
	dfs1(0, 0, 0);
	dsu::init(n);
	Loop (v,0,n) {
		for (int u : A[v]) {
			if (v > u)
				dsu::unite(v, u);
		}
	}
	int rt = -1;
	Loop (i,0,n) {
		if (dsu::par[i] == -1)
			rt = i;
		else
			A2[dsu::par[i]].push_back(i);
	}
	dfs(rt, 0);
	cout << ans << '\n';
}
