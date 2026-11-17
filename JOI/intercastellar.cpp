#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int n;
	cin>>n;
	vector<ll>odd(n),cnt(n);

	for(int i=0;i<n;++i){
		ll a;
		cin>>a;
		ll c=1;
		while(~a&1){
			a>>=1;
			c<<=1;
		}
		odd[i]=a;
		cnt[i]=c;
	}

	int q;
	cin>>q;

	int idx=0;
	ll pref=cnt[0];

	while(q--){
		ll x;
		cin>>x;
		while(idx+1<n and pref<x)pref+=cnt[++idx];
		cout<<odd[idx]<<'\n';
	}
}
