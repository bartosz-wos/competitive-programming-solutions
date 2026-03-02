#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int a[1000005];
int p[1000005];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int n;
	cin>>n;
	for(int i=0;i<n;++i)cin>>a[i];
	memset(p,-1,sizeof p);
	stack<int>s;
	for(int i=0;i<n;++i){
		int lst=-1;
		while(!s.empty() and a[s.top()]>a[i]){
			lst=s.top();
			s.pop();
		}
		if(~lst)p[lst]=i;
		if(!s.empty())p[i]=s.top();
		s.push(i);
	}
	for(int i=0;i<n;++i){
		if(!~p[i])p[i]=i;
		cout<<p[i]<<' ';
	}
	cout<<'\n';
}
