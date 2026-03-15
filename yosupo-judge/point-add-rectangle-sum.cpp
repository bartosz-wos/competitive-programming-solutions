#include<bits/stdc++.h>
using namespace std;
using ll=long long;

struct bit{
	int n;
	vector<ll>st;
	bit(int n):n(n),st(n+1,0){}
	void add(int i, ll x){
		for(;i<=n;i+=i&-i)
			st[i]+=x;
	}
	ll get(int i){
		ll ret=0;
		for(;i;i-=i&-i)
			ret+=st[i];
		return ret;
	}
};

struct event{
	int t,x,y;
	ll val;
	int id;
};

struct point{
	int x,y;
	ll c;
};

struct query{
	int t,a,b,c,d;
};

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int n,q;
	cin>>n>>q;
	vector<point>pts(n);
	vector<ll>ys;
	for(int i=0;i<n;++i){
		cin>>pts[i].x>>pts[i].y>>pts[i].c;
		ys.push_back(pts[i].y);
	}
	vector<query>qrs(q);
	for(int i=0;i<q;++i){
		cin>>qrs[i].t;
		if(!qrs[i].t){
			cin>>qrs[i].a>>qrs[i].b>>qrs[i].c;
			ys.push_back(qrs[i].b);
		}else{
			cin>>qrs[i].a>>qrs[i].b>>qrs[i].c>>qrs[i].d;
			ys.push_back(qrs[i].b);
			ys.push_back(qrs[i].d);
		}
	}
	sort(ys.begin(),ys.end());
	ys.erase(unique(ys.begin(),ys.end()),ys.end());
	auto get_y=[&](ll i){
		return (int)(lower_bound(ys.begin(),ys.end(),i)-ys.begin()+1);
	};
	int cnt=0;
	for(const auto&i:qrs)cnt+=i.t==1;
	vector<ll>res(cnt);
	vector<event>events;
	events.reserve(n+4*q);
	for(int i=0;i<n;++i)
		events.push_back({0,pts[i].x,get_y(pts[i].y),pts[i].c,0});
	int qr=0;
	for(int i=0;i<q;++i){
		if(!qrs[i].t)events.push_back({0,qrs[i].a,get_y(qrs[i].b),qrs[i].c,0});
		else{
			int l=qrs[i].a,d=get_y(qrs[i].b);
			int r=qrs[i].c,u=get_y(qrs[i].d);
			events.push_back({1,r,u,1,qr});
			events.push_back({1,l,u,-1,qr});
			events.push_back({1,r,d,-1,qr});
			events.push_back({1,l,d,1,qr});
			++qr;
		}
	}
	bit st(ys.size());

	auto cdq=[&](auto&self, int l, int r){	
		if(l>=r)return;
		int mid=(l+r)>>1;
		self(self,l,mid);
		self(self,mid+1,r);
		vector<event*>upd,qry;
		for(int i=l;i<=mid;++i)
			if(!events[i].t)upd.push_back(&events[i]);
		for(int i=mid+1;i<=r;++i)
			if(events[i].t==1)qry.push_back(&events[i]);
		sort(upd.begin(),upd.end(),[&](const auto&a, const auto&b){return a->x < b->x;});
		sort(qry.begin(),qry.end(),[&](const auto&a, const auto&b){return a->x < b->x;});
		int j=0;
		for(const auto*p:qry){
			while(j<upd.size() and upd[j]->x<p->x)
				st.add(upd[j]->y,upd[j]->val),++j;
			res[p->id]+=p->val*st.get(p->y-1);
		}
		for(int i=0;i<j;++i)
			st.add(upd[i]->y,-upd[i]->val);
	};
	cdq(cdq,0,events.size()-1);
	for(const ll&i:res)cout<<i<<'\n';
}
