#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int n,q;
vector<int>oc[500005];
map<int,int>mp;
vector<int>a;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n>>q;
	a.resize(n);
	int cnt=0;
	for(int i=0;i<n;++i){
		cin>>a[i];
		if(!mp.count(a[i]))mp[a[i]]=++cnt;
		oc[mp[a[i]]].push_back(i);
	}
	while(q--){
		int l,r,x;
		cin>>l>>r>>x;
		--r;
		if(!mp.count(x)){
			cout<<0<<'\n';
			continue;
		}
		int p=mp[x];
		int it1=upper_bound(oc[p].begin(),oc[p].end(),r)-oc[p].begin();
		if(!it1){
			cout<<0<<'\n';
			continue;
		}
		--it1;
		int it2=lower_bound(oc[p].begin(),oc[p].end(),l)-oc[p].begin();
		if(it1<it2){
			cout<<0<<'\n';
			continue;
		}
		cout<<it1-it2+1<<'\n';
	}
}
