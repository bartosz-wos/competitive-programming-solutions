#include<bits/stdc++.h>
using namespace std;
using ll=long long;
 
int n,j,res[1000001];
ll K;
deque<int>Q;
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n>>K;
	for(int i=1;i<=n;++i)
		Q.push_back(i);
	for(int k=n-1;k>=0;--k){
		if(k<=K){
			res[++j]=Q.back();
			Q.pop_back();
			K-=k;
		}
		else{
			res[++j]=Q.front();
			Q.pop_front();
		}
	}
	for(int i=1;i<=n;++i)
		cout<<res[i]<<' ';
}
