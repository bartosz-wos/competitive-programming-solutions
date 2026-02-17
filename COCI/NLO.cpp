#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define int long long
#define ll long long
#define pb push_back
#define fi first
#define se second
#define lf (id<<1)
#define rg ((id<<1)|1)
#define md ((l+r)>>1)
using namespace std;
typedef pair<int,int> pii;
typedef pair<int,pii> ipii;
const int MAXN = 115;
const int MAXK = 1e5+10;
const int INF = 1e18+10;
void chmn(int &a, int b){ a = min(a, b); }

int n, m, k;
int x[MAXN], y[MAXN], r[MAXN];

struct seg {
	int st[4*MAXK]; pii laz[4*MAXK];
	void bd(int id,int l,int r){
		laz[id] = {-1, 0};
		if(l==r) return;
		bd(lf, l, md); bd(rg, md+1, r);
	}
	void bnc(int id, int l, int r){
		if(laz[id] == pii(-1, 0)) return;
		if(laz[id].fi == -1){ // add
			st[lf] += laz[id].se * (md-l+1);
			laz[lf].se += laz[id].se;
			st[rg] += laz[id].se * (r-md);
			laz[rg].se += laz[id].se;
		} else { // ganti
			st[lf] = laz[id].se * (md-l+1);
			laz[lf] = laz[id];
			st[rg] = laz[id].se * (r-md);
			laz[rg] = laz[id];
		}
		laz[id] = {-1, 0};
	}
	int que(int id, int l, int r, int x, int y){
		if(x<=l && r<=y) return st[id];
		if(r<x || y<l) return 0;
		bnc(id, l, r);
		return que(lf,l,md,x,y) + que(rg,md+1,r,x,y);
	}
	int add(int id, int l, int r, int x, int y){
		if(x<=l && r<=y){
			laz[id].se++;
			return st[id] += (r-l+1);
		}
		if(r<x || y<l) return st[id];
		bnc(id, l, r);
		return st[id] = add(lf,l,md,x,y) + add(rg,md+1,r,x,y);
	}
	int upd(int id, int l, int r, int x, int y, int p){
		if(x<=l && r<=y){
			laz[id] = {0, p};
			return st[id] = (r-l+1) * p;
		}
		if(r<x || y<l) return st[id];
		bnc(id, l, r);
		return st[id] = upd(lf,l,md,x,y,p) + upd(rg,md+1,r,x,y,p);
	}
} A;

signed main(){
    // ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    cin >> k;
    for(int i=1; i<=k; i++) cin >> x[i]>> y[i] >> r[i];
    int ans = 0;
	
	A.bd(1,1,m);
    for(int i=1; i<=n; i++){
    	A.upd(1,1,m,1,m,0);
    	// cout << i << " i\n";
    	for(int j=1; j<=k; j++){
    		A.add(1,1,m,1,m);
    		int te = r[j]*r[j] - (x[j]-i)*(x[j]-i);
    		if(te<0) continue;
    		int le = max(1ll, -(int)sqrt(te) + y[j]);
    		int ri = min(m, (int)sqrt(te) + y[j]);
    		A.upd(1,1,m,le,ri,0);
    		// cout << j << ' ' << le << ' ' << ri << " leri\n";
    		// cout << j << " j\n";
    		// for(int p=1; p<=n; p++) cout << A.que(1,1,n,p,p) << ' ';
    		// 	cout << "xx\n";
    	}
    	ans += A.que(1,1,m,1,m);
    	// cout << i << ' ' << A.que(1,1,m,1,m) << " pp\n";
    	// 	for(int p=1; p<=m; p++) cout << A.que(1,1,m,p,p) << ' ';
    	// 		cout << "xx\n";
    }

    cout << ans << '\n';
}
