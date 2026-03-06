#include<bits/stdc++.h>
using namespace std;
using ll=long long;
 
constexpr int MAXA=1e7;
 
int n;
int t[MAXA+5];
 
void add(int i, int x){
	for(;i<=MAXA;i+=i&-i)
		t[i]+=x;
}
 
int get(int i){
	int ret=0;
	for(;i>0;i-=i&-i)
		ret+=t[i];
	return ret;
}
 
void solve(){
	cin>>n;
	vector<int>a(n);
	for(int&i:a)cin>>i;
	ll ret=0;
	for(const int&i:a)
		add(i,1),ret+=get(MAXA)-get(i);
	for(const int&i:a)
		add(i,-1);
	cout<<ret<<'\n';
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int t;
	cin>>t;
	while(t--)
		solve();
} 
