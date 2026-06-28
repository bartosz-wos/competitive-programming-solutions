#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using Gaussian=array<ll, 2>;

ll div_round(ll a, ll b){
	ll q=a/b;
	ll r=a%b;
	if(r<<1>b)++q;
	else if(r<<1<-b)--q;
	return q;
}

Gaussian gcd(Gaussian u, Gaussian v){
	if(!v[0] and !v[1])
		return u;

	ll norm=v[0]*v[0]+v[1]*v[1];
	ll n_r=u[0]*v[0]+u[1]*v[1];
	ll n_i=u[1]*v[0]-u[0]*v[1];
	ll qr=div_round(n_r,norm);
	ll qi=div_round(n_i,norm);
	Gaussian rem;
	rem[0]=u[0]-(qr*v[0]-qi*v[1]);
	rem[1]=u[1]-(qr*v[1]+qi*v[0]);
	return gcd(v,rem);
}

void solve(){
	Gaussian u, v;
	cin>>u[0]>>u[1]>>v[0]>>v[1];
	Gaussian ret=gcd(u,v);
	cout<<ret[0]<<' '<<ret[1]<<'\n';
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int t;
	cin>>t;
	while(t--)solve();
}
