#include <bits/stdc++.h>
using namespace std;
using pii = pair<int,int>;
struct Node {
	int u,v;
	int minu,maxu,minv,maxv;
	int left,right;
} ;
 
vector<Node> tr;
vector<int> idx;
vector<pii> pts;
int nodeCnt=0;
 
int build(int l,int r,int depth){
	if(l>r) return -1;
	int mid=(l+r)>>1;
	int axis = depth&1;
	nth_element(idx.begin()+l, idx.begin()+mid, idx.begin()+r+1,
		[&](int a,int b){
			return axis==0 ? pts[a].first < pts[b].first : pts[a].second < pts[b].second;
		});
	int id = idx[mid];
	int cur = nodeCnt++;
	if((int)tr.size()<=cur) tr.emplace_back();
	tr[cur].u = pts[id].first;
	tr[cur].v = pts[id].second;
	tr[cur].minu = tr[cur].maxu = tr[cur].u;
	tr[cur].minv = tr[cur].maxv = tr[cur].v;
	tr[cur].left = tr[cur].right = -1;
	int L = build(l, mid-1, depth+1);
	int R = build(mid+1, r, depth+1);
	tr[cur].left = L; tr[cur].right = R;
	auto relax = [&](int node){
		if(node==-1) return;
		tr[cur].minu = min(tr[cur].minu, tr[node].minu);
		tr[cur].maxu = max(tr[cur].maxu, tr[node].maxu);
		tr[cur].minv = min(tr[cur].minv, tr[node].minv);
		tr[cur].maxv = max(tr[cur].maxv, tr[node].maxv);
	};
	relax(L); relax(R);
	return cur;
}
 
inline int cheb_point_point(int u1,int v1,int u2,int v2){
	int du = abs(u1-u2);
	int dv = abs(v1-v2);
	return max(du,dv);
}
inline int cheb_point_box(int qu,int qv, const Node &node){
	int du = 0;
	if(qu < node.minu) du = node.minu - qu;
	else if(qu > node.maxu) du = qu - node.maxu;
	int dv = 0;
	if(qv < node.minv) dv = node.minv - qv;
	else if(qv > node.maxv) dv = qv - node.maxv;
	return max(du,dv);
}
 
void query_nearest(int root, int qu,int qv, int &best){
	if(root==-1) return;
	int dpt = cheb_point_point(qu,qv, tr[root].u, tr[root].v);
	if(dpt < best) best = dpt;
	int L = tr[root].left;
	int R = tr[root].right;
	int dl = (L==-1?INT_MAX:cheb_point_box(qu,qv, tr[L]));
	int dr = (R==-1?INT_MAX:cheb_point_box(qu,qv, tr[R]));
	if(dl < dr){
		if(dl < best) query_nearest(L,qu,qv,best);
		if(dr < best) query_nearest(R,qu,qv,best);
	}else{
		if(dr < best) query_nearest(R,qu,qv,best);
		if(dl < best) query_nearest(L,qu,qv,best);
	}
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n,m;
	if(!(cin>>n>>m)) return 0;
	vector<pair<int,int>> reserved(n);
	for(int i=0;i<n;i++) cin>>reserved[i].first>>reserved[i].second;
	vector<pair<int,int>> freep(m);
	for(int i=0;i<m;i++) cin>>freep[i].first>>freep[i].second;
	pts.resize(n);
	for(int i=0;i<n;i++){
		int x=reserved[i].first, y=reserved[i].second;
		pts[i].first = x + y;
		pts[i].second = x - y;
	}
	idx.resize(n);
	for(int i=0;i<n;i++) idx[i]=i;
	tr.clear();
	tr.reserve(n*1.1);
	nodeCnt=0;
	int root = build(0,n-1,0);
	int ans = 0;
	for(int i=0;i<m;i++){
		int x=freep[i].first, y=freep[i].second;
		int qu = x + y;
		int qv = x - y;
		int best = INT_MAX;
		query_nearest(root, qu, qv, best);
		if(best > ans) ans = best;
	}
	cout<<ans<<"\n";
	return 0;
}
