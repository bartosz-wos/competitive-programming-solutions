#include "factories.h"
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define fi first
#define se second
#define cmin(a, b) a = min(a, b)
const int inf = 1e18;

const signed LOG=18;


signed n;
vector<pair<signed, signed>> adj[500005];
signed up[500005][LOG];
signed depth[500005];
int depth2[500005];

void dfsinit(signed u, signed p) {
	for (auto [v, w]: adj[u]) if (v!=p) {
		up[v][0]=u;
		for (int i=1; i<LOG; i++) {
			if (up[v][i-1]==-1) break;
			up[v][i]=up[up[v][i-1]][i-1];
		}
		depth[v]=depth[u]+1, depth2[v]=depth2[u]+w;
		dfsinit(v, u);
	}
}

int lca(signed a, signed b) {
	if (a==b) return a;
	if (depth[a]<depth[b]) swap(a, b);
	signed k=depth[a]-depth[b];
	for (signed i=0; i<LOG&&k; i++) if (k&(1<<i)) a=up[a][i];
	if (a==b) return a;
	for (signed i=LOG-1; i>=0; i--) if (up[a][i]!=up[b][i]) a=up[a][i], b=up[b][i];
	return up[a][0];
}

int dist(signed a, signed b) {
	return depth2[a]+depth2[b]-2*depth2[lca(a, b)];
}


signed sz[500005], par[500005];
bool centro[500005];

void dfs(signed u, signed p) {
	sz[u]=1;
	for (auto [v, w]: adj[u]) if (v!=p && !centro[v]) {
		dfs(v, u);
		sz[u]+=sz[v];
	}
}

signed centroid(signed u, signed p, signed obj) {
	for (auto [v, w]: adj[u]) if (v!=p && !centro[v]) {
		if (sz[v]*2>=obj) return centroid(v, u, obj);
	}
	return u;
}

signed decompose(signed u, signed p) {
	if (centro[u]) return u;
	dfs(u, u);
	signed c=centroid(u, u, sz[u]); centro[c]=1;
	par[c]=p;
	for (auto [v, w]: adj[c]) if (!centro[v]) decompose(v, c);
	return c;
}

int distres[500005];

void Init(signed N, signed A[], signed B[], signed D[]) {
	n=N;
	for (int i=0; i<n-1; i++) {
		adj[A[i]].push_back({B[i], D[i]});
		adj[B[i]].push_back({A[i], D[i]});
		distres[i]=inf, centro[i]=0;
	}
	distres[n-1]=inf, centro[n-1]=0;
	dfsinit(0, 0);
	decompose(0, -1);
}

int Query(signed S, signed X[], signed T, signed Y[]) {
	int ans=inf;
	for (int i=0; i<S; i++) {
		signed act=X[i];
		while (act!=-1) {
			cmin(distres[act], dist(act, X[i]));
			act=par[act];
		}
	}
	for (int i=0; i<T; i++) {
		signed act=Y[i];
		while (act!=-1) {
			cmin(ans, distres[act]+dist(act, Y[i]));
			act=par[act];
		}
	}
	for (int i=0; i<S; i++) {
		signed act=X[i];
		while (act!=-1) {
			distres[act]=inf;
			act=par[act];
		}
	}
	return ans;
}
