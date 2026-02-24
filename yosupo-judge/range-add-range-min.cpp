#include<bits/stdc++.h>
using namespace std;
using ll=long long;

ll st[2000005];
ll lz[2000005];

void build(int k, int l, int r){
	if(l==r){
		cin>>st[k];
		return;
	}
	int mid=(l+r)>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	st[k]=min(st[k<<1],st[k<<1|1]);
}

void push(int k){
	if(!lz[k])return;
	lz[k<<1]+=lz[k];
	lz[k<<1|1]+=lz[k];
	st[k<<1]+=lz[k];
	st[k<<1|1]+=lz[k];
	lz[k]=0;
}

void upd(int k, int l, int r, int ql, int qr, ll x){
	if(l>r or l>qr or r<ql)return;
	if(ql<=l and r<=qr){
		st[k]+=x;
		lz[k]+=x;
		return;
	}
	push(k);
	int mid=(l+r)>>1;
	upd(k<<1,l,mid,ql,qr,x);
	upd(k<<1|1,mid+1,r,ql,qr,x);
	st[k]=min(st[k<<1],st[k<<1|1]);
}

ll get(int k, int l, int r, int ql, int qr){
	if(l>r or l>qr or r<ql)return 1e18;
	if(ql<=l and r<=qr)
		return st[k];
	push(k);
	int mid=(l+r)>>1;
	return min(get(k<<1,l,mid,ql,qr),get(k<<1|1,mid+1,r,ql,qr));
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int n,q;
	cin>>n>>q;
	build(1,0,n-1);
	while(q--){
		int t,l,r;
		cin>>t>>l>>r;
		if(!t){
			ll x;
			cin>>x;
			upd(1,0,n-1,l,r-1,x);
		}else
			cout<<get(1,0,n-1,l,r-1)<<'\n';
	}
}
