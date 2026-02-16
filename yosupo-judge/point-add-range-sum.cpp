#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int n,q;
ll st[500005];

void upd(int i, ll val){
	for(;i<=n;i+=i&-i)
		st[i]+=val;
}

ll get(int i){
	ll res=0;
	for(;i;i-=i&-i)
		res+=st[i];
	return res;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n>>q;
	for(int i=1;i<=n;++i){
		ll j;
		cin>>j;
		st[i]+=j;
		j=i+(i&-i);
		if(j<=n)st[j]+=st[i];
	}
	while(q--){
		int t,l,r;
		cin>>t>>l>>r;
		if(!t)upd(l+1,r);
		else cout<<get(r)-get(l)<<'\n';
	}
}
