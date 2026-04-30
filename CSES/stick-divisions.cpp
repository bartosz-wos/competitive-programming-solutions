#include<bits/stdc++.h>
using namespace std;
using ll=long long;
 
int n,x,d;
ll sum;
priority_queue<int,vector<int>,greater<int>>Q;
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin>>x>>n;
	for(int i=0;i<n;++i){
		cin>>d;
		Q.push(d);
	}
	while(Q.size()>1){
		int a=Q.top();
		Q.pop();
		int b=Q.top();
		Q.pop();
		Q.push(a+b);
		sum+=a+b;
	}
	cout<<sum;
}
