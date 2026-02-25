#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int n;
	cin>>n;
	vector<int>a(n);
	for(int&i:a)cin>>i;
	vector<int>dp,ids,prev(n,-1);
	for(int i=0;i<n;++i){
		int idx=lower_bound(dp.begin(),dp.end(),a[i])-dp.begin();
		if(idx==dp.size()){
			dp.push_back(a[i]);
			ids.push_back(i);
		}else{
			dp[idx]=a[i];
			ids[idx]=i;
		}
		if(idx)prev[i]=ids[idx-1];
	}
	cout<<dp.size()<<'\n';
	dp.clear();
	int v=ids.back();
	while(~v){
		dp.push_back(v);
		v=prev[v];
	}
	reverse(dp.begin(),dp.end());
	for(const int&i:dp)
		cout<<i<<' ';
	cout<<'\n';
}
