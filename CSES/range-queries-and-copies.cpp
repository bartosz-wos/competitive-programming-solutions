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
 
struct node{
	ll val;
	node *l,*r;
 
	node(ll x):val(x),l(nullptr),r(nullptr){}
	node(node*ll, node*rr){
		l=ll;
		r=rr;
		val=0;
		if(l)val+=l->val;
		if(r)val+=r->val;
	}
	node(node*p):val(p->val),l(p->l),r(p->r){}
};
 
int n,q,cnt=1;
int a[200001];
node *roots[200001];
 
node *build(int l=1, int r=n){
	if(l==r) return new node(a[l]);
	int mid=(l+r)>>1;
	return new node(build(l,mid),build(mid+1,r));
}
 
node *upd(node *t, int i, int x, int l=1, int r=n){
	if(l==r) return new node(x);
	int mid=(l+r)>>1;
	if(i<=mid)
		return new node(upd(t->l,i,x,l,mid),t->r);
	else
		return new node(t->l,upd(t->r,i,x,mid+1,r));
}
 
ll query(node *t, int ql, int qr, int l=1, int r=n){
	if(l>qr or r<ql) return 0;
	if(ql<=l and r<=qr)
		return t->val;
	int mid=(l+r)>>1;
	return query(t->l,ql,qr,l,mid)+query(t->r,ql,qr,mid+1,r);
}
 
void solve(){
	cin>>n>>q;
	REP(i,1,n)cin>>a[i];
	roots[cnt++]=build();
	while(q--){
		int t;
		cin>>t;
		if(t==1){
			int k,i,x;
			cin>>k>>i>>x;
			roots[k]=upd(roots[k],i,x);
		}
		else if(t==2){
			int k,l,r;
			cin>>k>>l>>r;
			cout<<query(roots[k],l,r)<<'\n';
		}
		else{
			int k;
			cin>>k;
			roots[cnt++]=new node(roots[k]);
		}
	}
}
 
//#define MNBVCXZ123
signed main(){
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
        int t=1;//cin>>t;
        clock_t time=clock();
        while(t--) solve();
        #ifdef MNBVCXZ123
        db tm=(db)(clock()-time)/CLOCKS_PER_SEC;
        cout<<"\n\nTime taken: ";
        cout<<fixed<<setprecision(8)<<tm<<'\n';
        #endif
}

