#include<bits/stdc++.h>
using namespace std;
using ll=long long;
#define fi first
#define se second
#define pb push_back
 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n;
	if(!(cin>>n))return 0;
	ll smax=LLONG_MIN,smin=LLONG_MAX;
	ll dmax=LLONG_MIN,dmin=LLONG_MAX;
	for(int i=0;i<n;i++){
		ll x,y;cin>>x>>y;
		ll s=x+y;
		ll d=x-y;
		if(s> smax)smax=s;
		if(s< smin)smin=s;
		if(d> dmax)dmax=d;
		if(d< dmin)dmin=d;
		ll ans=max(smax-smin,dmax-dmin);
		cout<<ans<<"\n";
	}
	return 0;
}
