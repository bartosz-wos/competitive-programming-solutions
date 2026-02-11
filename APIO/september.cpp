#include <bits/stdc++.h>
// #include "september.h"	

using namespace std;

const int MAXN = 2e5 + 11;

int l[MAXN], r[MAXN];

vector < int > g[MAXN];

void dfs(int v){
	for(int u : g[v]){ 
		dfs(u); 
		if(v && l[v] <= r[u])
			l[v] = min(l[v], l[u]), r[v] = max(r[v], r[u]);	
	}
}

int solve(int N, int M, vector<int> F, vector<vector<int>> S) {
	for(int i = 0; i < N; i++) g[i].clear(), r[i] = -1, l[i] = 1e9;
	for(int i = 1; i < N; i++) g[F[i]].push_back(i);
	for(int i = 0; i < M; i++)
		for(int j = 0; j < N - 1; j++)
			l[S[i][j]] = min(l[S[i][j]], j),
			r[S[i][j]] = max(r[S[i][j]], j);
	dfs(0);
	vector < pair < int, int > > vec;
	for(int i = 1; i < N; i++) vec.push_back({l[i], r[i]});
	sort(vec.begin(), vec.end());
	int cnt = 1, L = vec[0].first, R = vec[0].second;
	for(int i = 1; i < N - 1; i++){
		if(L <= vec[i].first && vec[i].first <= R) R = max(R, vec[i].second);
		else cnt++, L = vec[i].first, R = vec[i].second;
	}
	return cnt;
}
