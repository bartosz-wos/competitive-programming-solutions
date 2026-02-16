#include<bits/stdc++.h>
using namespace std;
using ll=long long;

ll p[500005];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int n,q;
	cin>>n>>q;
	for(int i=0;i<n;++i){
		cin>>p[i];
		if(i)p[i]+=p[i-1];
	}
	while(q--){
		int l,r;
		cin>>l>>r;
		--r;
		cout<<p[r]-(l?p[l-1]:0)<<'\n';
	}
}
