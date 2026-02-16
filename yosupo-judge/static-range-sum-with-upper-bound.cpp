#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pi=array<ll,2>;

int n,q;
pi a[500005];
pi st[2000005];

void upd(int k, int l, int r, int p, ll val){
	if(l==r){
		st[k][0]+=val;
		++st[k][1];
		return;
	}
	int mid=(l+r)>>1;
	if(p<=mid)upd(k<<1,l,mid,p,val);
	else upd(k<<1|1,mid+1,r,p,val);
	st[k][0]=st[k<<1][0]+st[k<<1|1][0];
	st[k][1]=st[k<<1][1]+st[k<<1|1][1];
}

pi get(int k, int l, int r, int ql, int qr){
	if(l>r or r<ql or l>qr)return {0,0};
	if(ql<=l and r<=qr)return st[k];
	int mid=(l+r)>>1;
	pi lef=get(k<<1,l,mid,ql,qr);
	pi rig=get(k<<1|1,mid+1,r,ql,qr);
	return {lef[0]+rig[0],lef[1]+rig[1]};
}

struct query{
	int l,r,x,id;
}qr[500005];

bool cmp(const query&a, const query&b){
	return a.x<b.x;
}

pi ans[500005];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n>>q;
	for(int i=0;i<n;++i){
		cin>>a[i][0];
		a[i][1]=i;
	}
	for(int i=0;i<q;++i){
		cin>>qr[i].l>>qr[i].r>>qr[i].x;
		qr[i].id=i;
	}
	sort(a,a+n);
	sort(qr,qr+q,cmp);
	for(int i=0,j=0;i<q;++i){
		while(j<n and a[j][0]<=qr[i].x)
			upd(1,0,n-1,a[j][1],a[j][0]),++j;
		ans[qr[i].id]=get(1,0,n-1,qr[i].l,qr[i].r-1);
		swap(ans[qr[i].id][0],ans[qr[i].id][1]);
	}
	for(int i=0;i<q;++i)
		cout<<ans[i][0]<<' '<<ans[i][1]<<'\n';
}
