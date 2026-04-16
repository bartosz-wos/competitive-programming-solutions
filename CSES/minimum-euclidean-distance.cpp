#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using ar=array<ll,2>;
ll res=LLONG_MAX;
vector<ar>t;
set<ar>S;
 
ll dist(ar a, ar b){
	return (b[0]-a[0])*(b[0]-a[0])+(b[1]-a[1])*(b[1]-a[1]);
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int n;
	cin>>n;
	t.resize(n);
	for(int i=0;i<n;++i)
		cin>>t[i][0]>>t[i][1];
	sort(t.begin(),t.end());
	S.insert({t[0][1],t[0][0]});
	for(int i=1,j=0;i<n;++i){
		ll d=ceil(sqrt(res));
		while(j<i and t[j][0]+d<t[i][0])
			S.erase({t[j][1],t[j][0]}),++j;
		auto l=S.lower_bound({t[i][1]-d,(ll)-1e18});
		auto r=S.upper_bound({t[i][1]+d,(ll)-1e18});
		for(auto it=l;it!=r;it++)
			res=min(res,dist(t[i],{(*it)[1],(*it)[0]}));
		S.insert({t[i][1],t[i][0]});
	}
	cout<<res;
}
