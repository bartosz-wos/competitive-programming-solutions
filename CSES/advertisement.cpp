#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pi=pair<ll,ll>;
 
ll n;
ll a[200001];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n;
	stack<pi> S;
	ll mx=0;
	for(int i=0;i<n;++i)
		cin>>a[i];
	for(int i=0;i<n;++i){
		ll s=i;
		while(!S.empty() and a[i]<=S.top().second){
			pi cur=S.top();
			S.pop();
			s=cur.first;
			mx=max(mx, (i-cur.first)*cur.second);
		}
		S.push({s,a[i]});
	}
	while(!S.empty()){
		pi cur=S.top();
		S.pop();
		mx=max(mx, (n-cur.first)*cur.second);
	}
	cout<<mx;
}
