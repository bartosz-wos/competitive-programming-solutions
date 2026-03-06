#include<bits/stdc++.h>
using namespace std;
using ll=long long;
 
mt19937 rng(time(nullptr));
 
ll mul(ll a,ll b, ll m){
	a%=m;
	b%=m;
	ll res=0;
	while(a){
		if(a&1)
			res=(res+b)%m;
		a>>=1;
		b<<=1;
		b%=m;
	}
	return res;
}
 
ll exp(ll a, ll w, ll m){
	ll res=1;
	a%=m;
	while(w){
		if(w&1)
			res=mul(res,a,m);
		a=mul(a,a,m);
		w>>=1;
	}
	return res;
}
 
bool check_composite(ll n, ll a, ll d, ll s){
	ll x=exp(a,d,n);
	if(x==1 or x==n-1)return 0;
	for(int r=1;r<s;++r){
		x=mul(x,x,n);
		if(x==n-1)return 0;
	}
	return 1;
}
 
bool MillerRabin(ll n, int iter=1){
	if(n<4)return n==2 or  n==3;
	int s=0;
	ll d=n-1;
	while((d&1)==0){
		++s;
		d>>=1;
	}
	while(iter--){
		ll a=2+rng()%(n-3);
		if(check_composite(n,a,d,s))return 0;
	}
	return 1;
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int t;
	cin>>t;
	while(t--){
		ll x;
		cin>>x;
		cout<<(MillerRabin(x)?"YES\n":"NO\n");
	}
}
