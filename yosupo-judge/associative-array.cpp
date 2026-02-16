#include<bits/stdc++.h>
using namespace std;
using ll=long long;

map<ll,ll>mp;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int q;
	cin>>q;
	while(q--){
		ll t,k;
		cin>>t>>k;
		if(!t){
			ll v;
			cin>>v;
			mp[k]=v;
		}else cout<<mp[k]<<'\n';
	}
}
