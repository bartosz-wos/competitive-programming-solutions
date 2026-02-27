#include<bits/stdc++.h>
using namespace std;
using ll=long long;

struct node{
	int lc=0,rc=0;
	int lz=0;
	int mn=0,cnt=0;
}st[20000005];

int rt=1,cnt=1;

void pull(int k, ll l, ll r){
	ll mid=(l+r)>>1;
	int lm=st[k].lc?st[st[k].lc].mn:0;
	int lc=st[k].lc?st[st[k].lc].cnt:(mid-l+1ll);
	int rm=st[k].rc?st[st[k].rc].mn:0;
	int rc=st[k].rc?st[st[k].rc].cnt:r-mid;
	int m,c;
	m=c=0;
	if(lm<rm){
		m=lm;
		c=lc;
	}else if(rm<lm){
		m=rm;
		c=rc;
	}else{
		m=lm;
		c=lc+rc;
	}
	st[k].mn=m+st[k].lz;
	st[k].cnt=c;
}

void upd(int &k, ll l, ll r, ll ql, ll qr, int x){
	if(l>r or r<ql or l>qr or ql>qr)return;
	if(!k){
		if(cnt+1>=20000005){
			cout<<"nah\n";
			exit(0);
		}
		k=++cnt;
		st[k].cnt=r-l+1ll;
	}
	if(ql<=l and r<=qr){
		st[k].lz+=x;
		st[k].mn+=x;
		return;
	}
	ll mid=(l+r)>>1;
	upd(st[k].lc,l,mid,ql,qr,x);
	upd(st[k].rc,mid+1,r,ql,qr,x);
	pull(k,l,r);
}

struct event{
	ll t,x,y0,y1;
	bool operator<(const event&b)const{
		if(x==b.x)return t<b.t;
		return x<b.x;
	}
};

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	ll off=1e9+5;
	ll mx=2e9+10;
	st[rt].cnt=mx+2;
	int q;
	cin>>q;
	vector<event>e;
	for(ll i=0,x0,y0,x1,y1;i<q;++i){
		cin>>x0>>y0>>x1>>y1;
		if(x0>=x1 or y0>=y1)continue;
		y0+=off;
		y1+=off;
		e.push_back({1,x0,y0,y1-1});
		e.push_back({-1,x1,y0,y1-1});
	}
	sort(e.begin(),e.end());
	ll res=0;
	upd(rt,0,mx+1,e[0].y0,e[0].y1,1);
	for(int i=1;i<e.size();++i){
		ll cnt2=0;
		if(!st[1].mn)cnt2=mx+2ll-st[1].cnt;
		else cnt2=mx+2ll;
		res+=cnt2*(ll)(e[i].x-e[i-1].x);
		upd(rt,0,mx+1,e[i].y0,e[i].y1,e[i].t);
	}
	cout<<res<<'\n';
}
