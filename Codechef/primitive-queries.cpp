#include <bits/stdc++.h>
using namespace std;
typedef long long LL; 
typedef long double LD;
typedef pair<int,int> pii;
typedef pair<LL, LL> pll;

#define inchar          getchar_unlocked
#define outchar(x)      putchar_unlocked(x)

template<typename T> void inpos(T &x) {
	x = 0; register T c = inchar();
	while(((c < 48) || (c > 57)) && (c != '-')) c = inchar();
	for(; c < 48 || c > 57; c = inchar()) ;
	for(; c > 47 && c < 58; c = inchar()) x = (x<<3) + (x<<1) + (c&15);
}

template<typename T> void outpos(T n) {
	char snum[65]; int i = 0; 
	do {
		snum[i++] = n % 10 + '0';
		n /= 10;
	} while(n);
	i = i - 1;
	while (i >= 0) outchar(snum[i--]); outchar('\n');
}

const int MAX = 1e5 + 2;
const int LN = 18;

int n, q;
vector<int> adj[MAX];
bool vis[MAX];
vector<int> order;
int color[MAX], use[MAX], ans[MAX];
int st[MAX], en[MAX], pool, inv[MAX*2];
int par[MAX][LN], depth[MAX];

void walk() {
	int pool = 0;
	for(auto &elem: order) {
		if(st[elem] > 0) {
			en[elem] = ++pool;
		} else {
			st[elem] = ++pool;
		}
		inv[pool] = elem;
	}
}

void lca_dfs(int node = 1, int prev = -1, int d = 0) {
	depth[node] = d;
	par[node][0] = prev;
	order.push_back(node);
	int sz = int(adj[node].size());
	for(int i = 0; i < sz; i++) {
		if(adj[node][i] == prev)	continue;
		lca_dfs(adj[node][i], node, d+1);
	}
	order.push_back(node);
}

void preprocess_lca() {
	fill(&par[0][0], &par[0][0] + MAX*LN, -1);
	lca_dfs();
	for(int j = 1; j < LN; j++) {
		for(int i = 1; i <= n; i++) {
			if(par[i][j-1] != -1) {
				par[i][j] = par[par[i][j-1]][j-1];
			}
		}
	}
	walk();
}

int LCA(int u, int v) {
	if(depth[u] < depth[v]) swap(u,v);
	int diff = depth[u]-depth[v];
	for(int i = 0; i < LN; i++) if((diff>>i)&1) u = par[u][i];
	if(u == v) return u;
	for(int i = LN-1; i > -1; i--) if(par[u][i] != par[v][i])
		u = par[u][i], v = par[v][i];
	return par[u][0];
}

int BLK_SIZE;
struct _query {
	int t, l, r, lca;
	bool flag;
	int idx;
	bool operator<(const _query &other) const {
		if(l/BLK_SIZE == other.l/BLK_SIZE) {
			if(r/BLK_SIZE == other.r/BLK_SIZE) {
				return t < other.t;
			}
			return r < other.r;
		}
		return l < other.l;
	}
} qs[MAX];

struct _update {
	int t, u, now, before;
} up[MAX];

vector<int> mp;
bool is_q[MAX];
int freq[MAX*2];
int unique_cnt = 0;

void toggle(int node) {
	if(vis[node]) {
		freq[use[node]] -= 1;
		if (freq[use[node]] == 0) {
			unique_cnt -= 1;
		}
	}
	else {
		freq[use[node]] += 1;
		if (freq[use[node]] == 1) {
			unique_cnt += 1;
		}
	}
	vis[node] ^= true;
}

int main() {
	int type, a, b, c;
	inpos(n), inpos(q);
	BLK_SIZE = pow(n, 2./3.);
	for(int i = 1; i <= n; i++) {
		inpos(color[i]);
		use[i] = color[i];
		mp.push_back(color[i]);
	}
	for(int i = 1; i < n; i++) {
		inpos(a), inpos(b);
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	preprocess_lca();
	int num_q = 0, num_up = 0;
	for(int i = 0; i < q; i++) {
		inpos(type), inpos(a), inpos(b);
		if(type == 2) {			
			mp.push_back(b);
			num_up++;
			up[num_up] = {num_up, a, b, use[a]};
			use[a] = b;
		}
		else {
			int l = LCA(a, b);
			if(l == a or l == b) {
				qs[num_q++] = {num_up, min(st[a], st[b]), max(st[a], st[b]), l, false, i};
			}
			else {
				qs[num_q++] = {num_up, min(en[a], en[b]), max(st[a], st[b]), l, true, i};
			}
			is_q[i] = true;
		}
	}

	sort(mp.begin(), mp.end());
	mp.erase(unique(mp.begin(), mp.end()), mp.end());
	for(int i = 1; i <= n; ++i) {
		color[i] = lower_bound(mp.begin(), mp.end(), color[i]) - mp.begin();
	}
	for(int i = 1; i <= num_up; ++i) {
		up[i].now = lower_bound(mp.begin(), mp.end(), up[i].now) - mp.begin();
		up[i].before = lower_bound(mp.begin(), mp.end(), up[i].before) - mp.begin();
	}
	sort(qs, qs + num_q);
	for(int i = 1; i <= n; i++) {
		use[i] = color[i];
	}
	int curr_l = 1, curr_r = 0, now = 0;
	for(int i = 0; i < num_q; i++) {
		while(now < qs[i].t) {
			now++;
			if(vis[up[now].u]) {
				toggle(up[now].u);
				use[up[now].u] = up[now].now;
				toggle(up[now].u);
			}
			else {
				use[up[now].u] = up[now].now;
			}
		}
		while(now > qs[i].t) {
			if(vis[up[now].u]) {
				toggle(up[now].u);
				use[up[now].u] = up[now].before;
				toggle(up[now].u);
			}
			else {
				use[up[now].u] = up[now].before;
			}
			now--;
		}
		while(curr_l < qs[i].l) {
			toggle(inv[curr_l]);
			curr_l++;
		}
		while(curr_l > qs[i].l) {
			curr_l--;
			toggle(inv[curr_l]);
		}
		while(curr_r < qs[i].r) {
			curr_r++;
			toggle(inv[curr_r]);
		}
		while(curr_r > qs[i].r) {
			toggle(inv[curr_r]);
			curr_r--;
		}
		ans[qs[i].idx] = unique_cnt;
		if(qs[i].flag) {
			assert(!vis[qs[i].lca]);
			if (freq[use[qs[i].lca]] == 0) {
				ans[qs[i].idx] += 1;
			}
		}
	}
	for(int i = 0; i < q; i++) {
		if(is_q[i]) {
			outpos(ans[i]);
		}
	}
	return 0;
}
