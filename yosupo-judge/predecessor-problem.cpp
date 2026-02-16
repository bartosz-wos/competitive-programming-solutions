#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int n,q;
	cin>>n>>q;
	set<int>s;
	string ss;
	cin>>ss;
	for(int i=0;i<n;++i)
		if(ss[i]-48)
			s.insert(i);
	while(q--){
		int t,k;
		cin>>t>>k;
		if(!t)s.insert(k);
		else if(t==1) s.erase(k);
		else if(t==2) cout<<s.count(k)<<'\n';
		else if(t==3){
			auto it=s.lower_bound(k);
			cout<<(it==s.end()?-1:*it)<<'\n';
		}else{
			auto it=s.upper_bound(k);
			cout<<(it==s.begin()?-1:*prev(it))<<'\n';
		}
	}
}
