#include<bits/stdc++.h>
using namespace std;
using ll=long long;
#define lc (k<<1)
#define rc (k<<1|1)
 
ll T[1<<21];
ll lazy[1<<21];
ll lazy2[1<<21];
 
int n,q;
 
void build(int k=1, int l=1, int r=n){
	if(l==r){
		cin>>T[k];
		return;
	}
	int mid=(l+r)>>1;
	build(lc,l,mid);
	build(rc,mid+1,r);
	T[k]=T[lc]+T[rc];
}
 
void push(int k, int l, int r, int mid){
	if(!lazy[k])
		return;
	T[lc]+=(lazy[k]+lazy[k]+(mid-l)*lazy2[k])*(mid-l+1)/2;
	lazy[lc]+=lazy[k];
	lazy2[lc]+=lazy2[k];
 
	T[rc]+=(lazy[k]+(mid+1-l)*lazy2[k]+lazy[k]+(r-l)*lazy2[k])*(r-mid)/2;
	lazy[rc]+=(lazy[k]+(mid+1-l)*lazy2[k]);
	lazy2[rc]+=lazy2[k];
	lazy[k]=lazy2[k]=0;
}
 
void upd(int ql, int qr, int k=1, int l=1, int r=n){
	if(l>qr or r<ql)
		return;
	if(ql<=l and r<=qr){
		T[k]+=1LL*(l+r-ql-ql+2)*(r-l+1)/2;
		lazy[k]+=l-ql+1;
		lazy2[k]++;
		return;
	}
	int mid=(l+r)>>1;
	push(k,l,r,mid);
	upd(ql,qr,lc,l,mid);
	upd(ql,qr,rc,mid+1,r);
	T[k]=T[lc]+T[rc];
}
 
ll query(int ql, int qr, int k=1, int l=1, int r=n){
	if(l>qr or r<ql)
		return 0;
	if(ql<=l and r<=qr)
		return T[k];
	int mid=(l+r)>>1;
	push(k,l,r,mid);
	return query(ql,qr,lc,l,mid)+query(ql,qr,rc,mid+1,r);
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n>>q;
	build();
	while(q--){
		int k,a,b;
		cin>>k>>a>>b;
		if(k==1)
			upd(a,b);
		else
			cout<<query(a,b)<<'\n';
	}
}
