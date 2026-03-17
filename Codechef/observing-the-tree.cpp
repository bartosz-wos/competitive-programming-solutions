#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <cmath>
#include <iomanip>

using namespace std;

typedef long long ll;

const int MAXN = 100005;

namespace SegmentTree
{
	struct Node
	{
		int lch,rch;
		int mark;
		ll sum,laz1,laz2;
	}node[22000005];

	int n,tot;
	int cur,id;
	int root[MAXN];

	inline int copy(int o)
	{
		if (node[o].mark == cur)
			return o;
		id++;
		node[id].lch = node[o].lch;
		node[id].rch = node[o].rch;
		node[id].mark = cur;
		node[id].sum = node[o].sum;
		node[id].laz1 = node[o].laz1;
		node[id].laz2 = node[o].laz2;
		return id;
	}

	inline void add(int o,ll size,ll a,ll b)
	{
		node[o].sum += size * a + (((size - 1) * size) >> 1) * b;
		node[o].laz1 += a;
		node[o].laz2 += b;
	}

	void pushdown(int o,int size)
	{
		if (node[o].laz1 || node[o].laz2)
		{
			node[o].lch = copy(node[o].lch);
			node[o].rch = copy(node[o].rch);
			add(node[o].lch,(size + 1) >> 1,node[o].laz1,node[o].laz2);
			node[o].laz1 += ((size + 1) >> 1) * node[o].laz2;
			add(node[o].rch,size >> 1,node[o].laz1,node[o].laz2);
			node[o].laz1 = node[o].laz2 = 0;
		}
	}

	int buildtree(int l,int r)
	{
		id++;
		if (l == r)
			return id;
		int mid = (l + r) >> 1;
		node[id].lch = buildtree(l,mid);
		node[id].rch = buildtree(mid + 1,r);
		return id;
	}

	int update(int o,int l,int r,int x,int y,ll a,ll b)
	{
		if (x > y)
			return o;
		o = copy(o);
		if (l >= x && r <= y)
		{
			add(o,r - l + 1,a,b);
			return o;
		}
		pushdown(o,r - l + 1);
		int mid = (l + r) >> 1;
		if (mid < x)
			node[o].rch = update(node[o].rch,mid + 1,r,x,y,a,b);
		else if (mid + 1 > y)
			node[o].lch = update(node[o].lch,l,mid,x,y,a,b);
		else
		{
			node[o].lch = update(node[o].lch,l,mid,x,y,a,b);
			node[o].rch = update(node[o].rch,mid + 1,r,mid + 1,y,a + (mid - x + 1) * b,b);
		}
		node[o].sum = node[node[o].lch].sum + node[node[o].rch].sum;
		return o;
	}

	ll query(int o,int l,int r,int x,int y)
	{
		if (x > y)
			return 0;
		o = copy(o);
		if (l >= x && r <= y)
			return node[o].sum;
		pushdown(o,r - l + 1);
		int mid = (l + r) >> 1;
		if (mid < x)
			return query(node[o].rch,mid + 1,r,x,y);
		if (mid + 1 > y)
			return query(node[o].lch,l,mid,x,y);
		return query(node[o].lch,l,mid,x,y) + query(node[o].rch,mid + 1,r,x,y);
	}

	inline void buildtree(int size){root[cur = 0] = buildtree(1,n = size);}
	inline void update(int l,int r,ll a,ll b){root[cur] = update(root[cur],1,n,l,r,a,b);}
	inline ll query(int l,int r){return query(root[cur],1,n,l,r);}
	inline void forward(){tot++;root[tot] = copy(root[cur]);cur = tot;}
	inline void reset(int tim){cur = tim;}
};

struct Edge
{
	int to;
	int next;
}edge[MAXN << 1];

int n,m,id,x,y;
int pos[MAXN];
int top[MAXN];
int fa[MAXN][20];
int first[MAXN];
int depth[MAXN];
int belong[MAXN];

char type;

ll a,b,lastans;

vector<int> chain[MAXN];

void addE(int u,int v)
{
	edge[++id] = (Edge){v,first[u]};
	first[u] = id;
}

int dfs(int now)
{
	for (int i = 1;i < 20;i++)
		fa[now][i] = fa[fa[now][i - 1]][i - 1];
	int MAX = 0,apd = 0,size = 1;
	for (int i = first[now];i;i = edge[i].next)
		if (edge[i].to != fa[now][0])
		{
			fa[edge[i].to][0] = now;
			depth[edge[i].to] = depth[now] + 1;
			int ret = dfs(edge[i].to);
			if (ret > MAX)
			{
				MAX = ret;
				apd = edge[i].to;
			}
			size += ret;
		}
	chain[belong[now] = (apd ? belong[apd] : ++id)].push_back(now);
	return size;
}

int LCA(int u,int v)
{
	if (depth[u] < depth[v])
		swap(u,v);
	int diff = depth[u] - depth[v];
	for (int i = 19;i >= 0;i--)
		if (diff & (1 << i))
			u = fa[u][i];
	if (u == v)
		return u;
	for (int i = 19;i >= 0;i--)
		if (fa[u][i] != fa[v][i])
			u = fa[u][i],v = fa[v][i];
	return fa[u][0];
}

inline void opr1(int x,int y,ll a,ll b)
{
	int lca = LCA(x,y);
	SegmentTree::forward();
	while (belong[x] != belong[lca])
	{
	//	cout << "update:" << pos[x] << ',' << pos[top[x]] << ',' << a << ',' << b << endl;
		SegmentTree::update(pos[x],pos[top[x]],a,b);
		a += (pos[top[x]] - pos[x] + 1) * b;
		x = fa[top[x]][0];
	}
//	cout << "update:" << pos[x] << ',' << pos[lca] << ',' << a << ',' << b << endl;
	SegmentTree::update(pos[x],pos[lca],a,b);
	a += (pos[lca] - pos[x]) * b;
	a += (depth[y] - depth[lca]) * b;
	while (belong[y] != belong[lca])
	{
	//	cout << "update:" << pos[y] << ',' << pos[top[y]] << ',' << a << ',' << -b << endl;
		SegmentTree::update(pos[y],pos[top[y]],a,-b);
		a -= (pos[top[y]] - pos[y] + 1) * b;
		y = fa[top[y]][0];
	}
//	cout << "update:" << pos[y] << ',' << pos[lca] - 1 << ',' << a << ',' << -b << endl;
	SegmentTree::update(pos[y],pos[lca] - 1,a,-b);
}

inline void opr2(int x,int y)
{
	int lca = LCA(x,y);
	ll ret = 0;
	while (belong[x] != belong[lca])
	{
	//	cout << "query:" << pos[x] << ',' << pos[top[x]] << endl;
		ret += SegmentTree::query(pos[x],pos[top[x]]);
		x = fa[top[x]][0];
	}
//	cout << "query:" << pos[x] << ',' << pos[lca] << endl;
	ret += SegmentTree::query(pos[x],pos[lca]);
	while (belong[y] != belong[lca])
	{
	//	cout << "query:" << pos[y] << ',' << pos[top[y]] << endl;
		ret += SegmentTree::query(pos[y],pos[top[y]]);
		y = fa[top[y]][0];
	}
//	cout << "query:" << pos[y] << ',' << pos[lca] - 1 << endl;
	ret += SegmentTree::query(pos[y],pos[lca] - 1);
	cout << (lastans = ret) << endl;
}

inline void opr3(int tim)
{
	SegmentTree::reset(tim);
}

int main()
{
//	freopen("D.inp","r",stdin);
//	freopen("D.ans","w",stdout);
	ios::sync_with_stdio(false);
	cin >> n >> m;
	for (int u,v,i = 1;i < n;i++)
	{
		cin >> u >> v;
		addE(u,v);
		addE(v,u);
	}
	SegmentTree::buildtree(n);
	id = 0;
	dfs(1);
	int t = id;
	id = 0;
	for (int i = 1;i <= t;i++)
		for (int j = 0;j < chain[i].size();j++)
		{
			pos[chain[i][j]] = ++id;
			top[chain[i][j]] = chain[i].back();
		}
//	for (int i = 1;i <= n;i++)
//		cout << pos[i] << ' ' << belong[i] << ' ' << top[i] << endl;
	for (int i = 1;i <= m;i++)
	{
		cin >> type;
		if (type == 'c')
		{
			cin >> x >> y >> a >> b;
			x = (x + lastans) % n + 1;
			y = (y + lastans) % n + 1;
		//	cout << "real:x=" << x << "y=" << y << "a=" << a << "b=" << b << endl;
			opr1(x,y,a,b);
		}
		if (type == 'q')
		{
			cin >> x >> y;
			x = (x + lastans) % n + 1;
			y = (y + lastans) % n + 1;
		//	cout << "real:x=" << x << "y=" << y << endl;
			opr2(x,y);
		}
		if (type == 'l')
		{
			cin >> x;
			x = (x + lastans) % (SegmentTree::tot + 1);
		//	cout << "real:x=" << x << endl;
			opr3(x);
		}
	}
}
