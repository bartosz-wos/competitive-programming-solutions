#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using lll=__int128;

bool chk(int x){
	if(x<=1)return 0;
	if(x==2)return 1;
	for(int i=2;i*i<=x;++i)
		if(x%i==0)return 0;
	return 1;
}

ll exp(ll a, ll w, ll m){
	a%=m;
	ll res=1;
	while(w){
		if(w&1)res=(lll)res*a%m;
		a=(lll)a*a%m;
		w>>=1;
	}
	return res;
}

vector<int>pr;

bool not_comp(ll n, ll a, ll d, ll s){
	ll x=exp(a,d,n);
	if(x==1 or x==n-1)return 0;
	for(int i=1;i<s;++i){
		x=(lll)x*x%n;
		if(x==n-1)return 0;
	}
	return 1;
}

bool prime(ll n){
	if(n<=5)return n==2 or n==3 or n==5;
	ll s=0;
	ll d=n-1;
	while(~d&1){
		++s;
		d>>=1;
	}
	for(const int&i:pr){
		if(n==i)return 1;
		if(not_comp(n,i,d,s))return 0;
	}
	return 1;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	for(int i=1;i<=37;++i)
		if(chk(i))pr.push_back(i);
	int q;
	cin>>q;
	while(q--){
		ll n;
		cin>>n;
		cout<<(prime(n)?"Yes\n":"No\n");
	}
}
