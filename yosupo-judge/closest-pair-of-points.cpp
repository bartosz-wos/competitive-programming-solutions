#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pi=array<ll,3>;

ll sq(ll x){
	return x*x;
}

ll dist(const pi&a, const pi&b){
	return sq(a[0]-b[0])+sq(a[1]-b[1]);
}

void solve(){
	int n;
	cin>>n;
	vector<pi>a(n);
	for(int i=0;i<n;++i){
		cin>>a[i][0]>>a[i][1];
		a[i][2]=i;
	}
	sort(a.begin(),a.end());
	for(int i=1;i<n;++i)
		if(a[i][0]==a[i-1][0] and a[i][1]==a[i-1][1]){
			if(a[i][2]<a[i-1][2])swap(a[i],a[i-1]);
			cout<<a[i-1][2]<<' '<<a[i][2]<<'\n';
			return;
		}
	ll res=dist(a[0],a[1]);
	set<pi>s={{a[0][1],a[0][0],a[0][2]}};
	pi ans={a[0][2],a[1][2],-1};
	for(int i=1,j=0;i<n;++i){
		ll d=ceil(sqrt(res));
		while(j<i and a[j][0]+d<a[i][0])
			s.erase({a[j][1],a[j][0],a[j][2]}),++j;
		auto l=s.lower_bound({a[i][1]-d,(ll)-1e18,-1});
		auto r=s.upper_bound({a[i][1]+d,(ll)1e18,(ll)1e18});
		for(;l!=r;++l){
			ll d=dist(a[i],{(*l)[1],(*l)[0]});
			if(d<res){
				res=d;
				ans[0]=a[i][2];
				ans[1]=(*l)[2];
			}
		}
		s.insert({a[i][1],a[i][0],a[i][2]});
	}
	if(ans[0]>ans[1])swap(ans[0],ans[1]);
	cout<<ans[0]<<' '<<ans[1]<<'\n';
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int t;
	cin>>t;
	while(t--)
		solve();
}
