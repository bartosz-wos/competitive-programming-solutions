#include <bits/stdc++.h>
using namespace std;

#define int long long
#define pii pair <int, int>
#define fi first
#define se second
#define mp make_pair

const int NM = 30000, MM = 30000, inf = 1e18;

int N, M, B[MM+5], P[MM+5];
vector <int> arr[NM+5];
int d[NM+5];
priority_queue <pii, vector <pii>, greater <pii> > pq;

void dijkstra(){
	for (int i = 0; i < N; i++) d[i] = +inf;
	d[B[0]] = 0;
	while (!pq.empty()) pq.pop();
	pq.push(mp(0, B[0]));
	
	while (!pq.empty()){
		int u = pq.top().se;
		if (d[u] != pq.top().fi){
			pq.pop();
			continue;
		}
		pq.pop();
		for (int x : arr[u]){
			for (int v = u-x, w = 1; v >= 0; v -= x, w++){
				if (d[u]+w >= d[v]) continue;
				d[v] = d[u]+w;
				pq.push(mp(d[v], v));
			}
			for (int v = u+x, w = 1; v < N; v += x, w++){
				if (d[u]+w >= d[v]) continue;
				d[v] = d[u]+w;
				pq.push(mp(d[v], v));
			}
		}
	}
}

signed main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	cin >> N >> M;
	for (int i = 0; i < M; i++){
		cin >> B[i] >> P[i];
		arr[B[i]].push_back(P[i]);
	}
	for (int i = 0; i < N; i++){
		sort(arr[i].begin(), arr[i].end());
		arr[i].erase(unique(arr[i].begin(), arr[i].end()), arr[i].end());
	}
	dijkstra();
	if (d[B[1]] == +inf) cout << -1;
	else cout << d[B[1]];
	
	return 0;
}
