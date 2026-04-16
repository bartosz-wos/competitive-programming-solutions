#include<bits/stdc++.h>
using namespace std;
using ll=long long;
constexpr int maxn=2e6+5;
int y[100001];
array<int,2>ver[100001];
ll bit[maxn];
void upd(int i, int x){
	for(;i<=maxn;i+=i&-i)
		bit[i]+=x;
}
 
ll get(int i){
	ll res=0;
	for(;i>0;i-=i&-i)
		res+=bit[i];
	return res;
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int n;
	cin>>n;
	vector<array<int,3>>p;
	for(int i=0,x1,y1,x2,y2;i<n;++i){
		cin>>x1>>y1>>x2>>y2;
		if(x1==x2){
			p.push_back({x1,1,i});
			ver[i]={y1,y2};
		}
		else{
			p.push_back({x1,0,i});
			p.push_back({x2,2,i});
			y[i]=y1;
		}
	}
	sort(p.begin(),p.end());
	ll res=0;
	for(const auto&[x,t,i]:p){
		if(t==0)upd(y[i]+1e6+1,1);
		else if(t==2)upd(y[i]+1e6+1,-1);
		else res+=get(ver[i][1]+1e6+1)-get(ver[i][0]+1e6);
	}
	cout<<res;
}
