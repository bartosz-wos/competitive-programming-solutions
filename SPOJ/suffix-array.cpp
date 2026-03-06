#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pi=pair<int,int>;
 
int mod(const int&x, const int&n){
    return x>=n?x-n:x;
}
 
vector<int>SCS(const string&s){
	int n=s.size();
	int alphabet=125;
	vector<int>p(n),pn(n),c(n),cn(n),cnt(max(alphabet,n),0);
	for(int i=0;i<n;++i)
		++cnt[s[i]];
	for(int i=1;i<alphabet;++i)
		cnt[i]+=cnt[i-1];
	for(int i=0;i<n;++i)
		p[--cnt[s[i]]]=i;
	c[p[0]]=0;
	int classes=1;
	for(int i=1;i<n;++i){
		if(s[p[i]]!=s[p[i-1]])
			++classes;
		c[p[i]]=classes-1;
	}
	for(int h=0;(1<<h)<n;++h){
		for(int i=0;i<n;++i){
			pn[i]=p[i]-(1<<h);
			if(pn[i]<0)pn[i]+=n;
		}
		fill(cnt.begin(),cnt.begin()+classes,0);
		for(int i=0;i<n;++i)
			++cnt[c[pn[i]]];
		for(int i=1;i<classes;++i)
			cnt[i]+=cnt[i-1];
		for(int i=n-1;i>=0;--i)
			p[--cnt[c[pn[i]]]]=pn[i];
		cn[p[0]]=0;
		classes=1;
		for(int i=1;i<n;++i){
			pi a={c[p[i]],c[mod(p[i]+(1<<h),n)]};
			pi b={c[p[i-1]],c[mod(p[i-1]+(1<<h),n)]};
			if(a!=b)++classes;
			cn[p[i]]=classes-1;
		}
		c.swap(cn);
	}
	return p;
}
 
vector<int>SA(string s){
	s+='$';
	vector<int>ret=SCS(s);
	return ret;
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	string s;
	cin>>s;
	vector<int>ret=SA(s);
	for(int i=1;i<=s.size();++i)cout<<ret[i]<<'\n';
}
