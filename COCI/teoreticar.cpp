#include <bits/stdc++.h>
#define PB push_back
#define ST first
#define ND second
#define _ ios_base::sync_with_stdio(0); cin.tie(0);
//mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

using namespace std;

using ll = long long;
using pi = pair<int,int>;
using vi = vector<int>;

const int nax = 1000 * 1000 + 10;
int l, r, m;
int deg[nax][2];
pi edge[nax];
vector<pi> V[nax][2];
int I[nax][2];
bool vis[nax];
int col[nax];
int nr;

vi cycle;

void eulerCycle(int x, bool turn) {
	while(I[x][turn] < (int)V[x][turn].size()) {
		auto nbh = V[x][turn][I[x][turn]++];
		if(!vis[nbh.ND]) {
			vis[nbh.ND] = true;
			eulerCycle(nbh.ST, turn^1);
			cycle.PB(nbh.ND);
		}
	}
}

vector<pi>V2[nax][2];

void add(int a, int b) {
	nr++;
	V[a][0].PB({b, nr});
	V[b][1].PB({a, nr});
	edge[nr] = {a, b};
}
	

void rec(int a, int b, vi use_l, vi use_r) {
	if(a == b) {
		for(int i : use_l) {
			if((int)V[i][0].size() > 0) {
				col[V[i][0][0].ND] = a;
			}
		}
		return;
	}
	V[max(l,r) + 1][0].clear();
	V[max(l,r) + 1][1].clear();
	nr = m;
	for(int i : use_l) {
		I[i][0] = 0;
		if((int)V[i][0].size() % 2 == 1) {
			add(i, max(l,r) + 1);
		}
		for(auto nbh : V[i][0]) vis[nbh.ND] = false;
	}
	for(int i : use_r) {
		I[i][1] = 0;
		if((int)V[i][1].size() % 2 == 1) {
			add(max(l,r) + 1, i);
		}
	}
	I[max(l,r)+1][0] = I[max(l,r)+1][1] = 0;
	if((int)V[max(l,r) + 1][0].size() % 2 == 1) {
		add(max(l,r)+1, max(l,r)+1);
	}
	for(auto nbh : V[max(l,r) + 1][0]) vis[nbh.ND] = false;
	//for(int i : use_l) {
		//cout << i << ": ";
		//for(auto x : V[i][0]) cout << x.ST << " " << x.ND << ", ";
		//cout << "\n";
	//}
	//for(int i : {max(l,r)+1}) {
		//cout << i << ": ";
		//for(auto x : V[i][0]) cout << x.ST << " " << x.ND << ", ";
		//cout << "\n";
	//}
	cycle.clear();
	for(int i : use_l) {
		eulerCycle(i, 0);
	}
	eulerCycle(max(l,r) + 1, 0);
	vi cyc = cycle;
	//for(int c : cyc) {
		//cout << c << " ";
	//}
	//cout << "\n----\n";
	for(int i = 0; i < (int)cyc.size(); i += 2) {
		if(cyc[i] <= m) {
			V2[edge[cyc[i]].ST][0].PB({edge[cyc[i]].ND, cyc[i]});
			V2[edge[cyc[i]].ND][1].PB({edge[cyc[i]].ST, cyc[i]});
		}
	}
	vi ul = {}, ur = {};
	for(int i : use_l) {
		V[i][0].swap(V2[i][0]);
		if((int)V[i][0].size() > 0) ul.PB(i);
		V2[i][0].clear();
	}
	for(int i : use_r) {
		V[i][1].swap(V2[i][1]);
		if((int)V[i][1].size() > 0) ur.PB(i);
		V2[i][1].clear();
	}
	rec(a, (a + b) / 2, ul, ur);
	ul.clear();
	ur.clear();
	for(int i = 1; i < (int)cyc.size(); i += 2) {
		if(cyc[i] <= m) {
			V2[edge[cyc[i]].ST][0].PB({edge[cyc[i]].ND, cyc[i]});
			V2[edge[cyc[i]].ND][1].PB({edge[cyc[i]].ST, cyc[i]});
		}
	}
	for(int i : use_l) {
		V[i][0].swap(V2[i][0]);
		if((int)V[i][0].size() > 0) ul.PB(i);
		V2[i][0].clear();
	}
	for(int i : use_r) {
		V[i][1].swap(V2[i][1]);
		if((int)V[i][1].size() > 0) ur.PB(i);
		V2[i][1].clear();
	}
	rec((a + b) / 2 + 1, b, ul, ur);
}

int main() {
	cin >> l >> r >> m;
	for(int a, b, i = 1; i <= m; ++i) {
		cin >> a >> b;
		edge[i] = {a, b};
		deg[a][0]++;
		deg[b][1]++;
		V[a][0].PB({b, i});
		V[b][1].PB({a, i});
	}
	int mx = 0;
	for(int i = 1; i <= l; ++i) {
		mx = max(mx, deg[i][0]);	
	}
	for(int i = 1; i <= r; ++i) {
		mx = max(mx, deg[i][1]);	
	}
	int pt = 1;
	while(pt < mx) pt *= 2;
	vi a(l), b(r);
	for(int i = 0; i < l; ++i) a[i] = i + 1;
	for(int i = 0; i < r; ++i) b[i] = i + 1;
	rec(1, pt, a, b);
	cout << pt << "\n";
	for(int i = 1; i <= m; ++i) {
		cout << col[i] << "\n";
	}
	
}
