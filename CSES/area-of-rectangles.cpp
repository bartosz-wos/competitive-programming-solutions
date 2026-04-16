#include<bits/stdc++.h>
#define sz(x) ((int)x.size())
#define al(x) x.begin(),x.end()
#define rep(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>b;--i)
#define PER(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
using ll=long long;
using db=double;
using ld=long double;
using arint=array<int,2>;
using arll=array<ll,2>;
using arint3=array<int,3>;
using arll3=array<ll,3>;
using cll=complex<ll>;
using cdb=complex<db>;
using cld=complex<ld>;
constexpr ld PI=acos(-1);
constexpr int mod=1e9+7;
constexpr ll infll=1e18;
constexpr int infint=2e9;
 
constexpr int MX=1e6;
constexpr int MXN=2*1e6+1;
 
arint merge(const arint&a, const arint&b){
	if(a[0]<b[0]) return a;
	if(b[0]<a[0]) return b;
	return {a[0],a[1]+b[1]};
}
 
struct SegTree{
	arint T[1<<22];
	int lazy[1<<22];
	void push(int k, int lc, int rc){
		if(!lazy[k]) return;
		T[lc][0]+=lazy[k];
		lazy[lc]+=lazy[k];
		T[rc][0]+=lazy[k];
		lazy[rc]+=lazy[k];
		lazy[k]=0;
	}
	void build(int k=1, int l=0, int r=MXN){
		if(l==r){
			T[k]={0,1};
			return;
		}
		int mid=(l+r)>>1;
		build(k<<1,l,mid);
		build(k<<1|1,mid+1,r);
		T[k]=merge(T[k<<1],T[k<<1|1]);
	}
	void upd(int ql, int qr, int x, int k=1, int l=0, int r=MXN){
		if(l>qr or r<ql) return;
		if(ql<=l and r<=qr){
			T[k][0]+=x;
			lazy[k]+=x;
			return;
		}
		int mid=(l+r)>>1;
		push(k,k<<1,k<<1|1);
		upd(ql,qr,x,k<<1,l,mid);
		upd(ql,qr,x,k<<1|1,mid+1,r);
		T[k]=merge(T[k<<1],T[k<<1|1]);
	}
	int query(){
		return MXN+1-T[1][1];
	}
}Tree;
 
struct Event{
	int t,x,y0,y1;
	bool operator<(const Event&b) const{
		if(x==b.x) return t<b.t;
		return x<b.x;
	}
};
int q;
vector<Event>E;
 
void solve(){
	cin>>q;
	Tree.build();
	rep(i,0,q){
		int x0,y0,x1,y1;
		cin>>x0>>y0>>x1>>y1;
		x0+=MX,x1+=MX;
		y0+=MX,y1+=MX;
		E.push_back({1,x0,y0,y1-1});
		E.push_back({-1,x1,y0,y1-1});
	}
	sort(E.begin(),E.end());
	ll res=0;
	Tree.upd(E[0].y0,E[0].y1,1);
	rep(i,1,(q<<1)){
		res+=(ll)Tree.query()*(ll)(E[i].x-E[i-1].x);
		Tree.upd(E[i].y0,E[i].y1,E[i].t);
	}
	cout<<res;
}
 
signed main(){
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
        int t=1;//cin>>t;
        while(t--) solve();
}

