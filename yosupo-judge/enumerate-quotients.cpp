#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	ll n;
	cin>>n;
	vector<ll>v;
	for(ll i=1;i<=n;){
		v.push_back(n/i);
		i=n/(n/i)+1;
	}
	reverse(v.begin(),v.end());
	cout<<v.size()<<'\n';
	for(const ll&i:v)
		cout<<i<<' ';
}
