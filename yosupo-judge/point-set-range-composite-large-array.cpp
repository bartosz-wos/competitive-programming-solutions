#include<bits/stdc++.h>
using namespace std;
using ll=long long;
constexpr int mod=998244353;

struct node{
	int l,r;
	ll c,d;
	node(ll c=1,ll d=0):c(c),d(d),l(0),r(0){}
};

node op(const node&a, const node&b){
	return node(a.c*b.c%mod,(b.c*a.d+b.d)%mod);
}

int n,q,cnt=1;
node st[40000005];

void upd(int k, int l, int r, int p, node x){
	if(l==r){
		st[k]=x;
		return;
	}
	int mid=(l+r)>>1;
	if(p<=mid){
		if(!st[k].l){
			st[k].l=++cnt;
			st[cnt]=node();
		}
		upd(st[k].l,l,mid,p,x);
	}else{
		if(!st[k].r){
			st[k].r=++cnt;
			st[cnt]=node();
		}
		upd(st[k].r,mid+1,r,p,x);
	}
	node lef=st[k].l?st[st[k].l]:node();
	node rig=st[k].r?st[st[k].r]:node();
	node res=op(lef,rig);
	st[k].c=res.c;
	st[k].d=res.d;
}

node get(int k, int l, int r, int ql, int qr){
	if(!k)return node();
	if(l>r or r<ql or l>qr)return node();
	if(ql<=l and r<=qr)return st[k];
	int mid=(l+r)>>1;
	return op(get(st[k].l,l,mid,ql,qr),get(st[k].r,mid+1,r,ql,qr));
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n>>q;
	st[1]=node();
	while(q--){
		int t;
		ll a,b,c;
		cin>>t>>a>>b>>c;
		if(!t)upd(1,0,n-1,a,node(b,c));
		else{
			node nd=get(1,0,n-1,a,b-1);
			cout<<(nd.c*c%mod+nd.d)%mod<<'\n';
		}
	}
}
