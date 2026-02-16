#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int n,q;
	cin>>n>>q;
	multiset<int>ms;
	for(int i=0,x;i<n;++i)
		cin>>x,ms.insert(x);
	while(q--){
		int t;
		cin>>t;
		if(!t){
			int x;
			cin>>x;
			ms.insert(x);
		}else if(t==1){
			cout<<*ms.begin()<<'\n';
			ms.erase(ms.begin());
		}else{
			cout<<*prev(ms.end())<<'\n';
			ms.erase(prev(ms.end()));
		}
	}
}
