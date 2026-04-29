#include<bits/stdc++.h>
using namespace std;
using ll=long long;
 
int n,m;
int dsu[100001];
 
int find(int x){
	if(dsu[x]<0)return x;
	return dsu[x]=find(dsu[x]);
}
 
void onion(int a, int b){
	a=find(a);
	b=find(b);
	if(a==b)return;
	if(dsu[a]>dsu[b])swap(a,b);
	dsu[a]+=dsu[b];
	dsu[b]=a;
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n>>m;
	memset(dsu,-1,sizeof(dsu));
	while(m--){
		int a,b;
		cin>>a>>b;
		onion(a,b);
	}
	vector<int>c;
	for(int i=1;i<=n;++i)if(find(i)==i)c.push_back(-dsu[i]);
 
	bitset<100001>b;
	b[0]=1;
	for(const int&i:c)b|=(b<<i);
	for(int i=1;i<=n;++i)cout<<b[i];
}
