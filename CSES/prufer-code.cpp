#include<bits/stdc++.h>
using namespace std;
using ll=long long;
 
ll n;
vector<ll> v;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n;
	v.resize(n-2);
	set<ll>S;
	for(int i=1;i<=n;++i)
		S.insert(i);
	int a[n+1]{0};
	for(ll& i:v){
		cin>>i;
		++a[i];
		if(S.count(i))
			S.erase(i);
	}
	for(int i=0;i<n-2;++i){
		int x=*S.begin();
		S.erase(x);
		cout<<x<<' '<<v[i]<<'\n';
		--a[v[i]];
		if(a[v[i]]==0)
			S.insert(v[i]);
	}
	cout<<*S.begin()<<' '<<*S.rbegin();
}
