#include<bits/stdc++.h>
using namespace std;
using ll=long long;
 
constexpr int BL=200;
 
int n,q,res;
int a[30005];
int ans[200000];
int freq[1000001];
 
struct Query{
	int l, r, id;
	bool operator<(const Query&b)const{
		int l1=l/BL;
		int l2=b.l/BL;
		if(l1!=l2)return l1<l2;
		return (l1&1)?(r>b.r):(r<b.r);
	}
}Q[200000];
 
void add(int x){
	if(!freq[x])++res;
	++freq[x];
}
 
void del(int x){
	if(freq[x]==1)--res;
	--freq[x];
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n;
	for(int i=1;i<=n;++i)cin>>a[i];
	cin>>q;
	for(int i=0;i<q;++i){
		cin>>Q[i].l>>Q[i].r;
		Q[i].id=i;
	}
	sort(Q,Q+q);
 
	int l=0,r=0;
 
	for(int k=0;k<q;++k){
 
		while(l<Q[k].l){
			if(l)
				del(a[l++]);
			else
				++l;
		}
		while(l>Q[k].l)add(a[--l]);
		while(r<Q[k].r)add(a[++r]);
		while(r>Q[k].r)del(a[r--]);
 
		ans[Q[k].id]=res;
	}
 
	for(int i=0;i<q;++i)
		cout<<ans[i]<<'\n';
} 
