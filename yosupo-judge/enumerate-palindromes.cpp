#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	string s2,s;
	cin>>s2;
	for(const char&c:s2)
		s+=string("#")+c;
	s+='#';
	int n=s.size();
	s='1'+s+'2';
	vector<int>p(n+2);
	for(int i=1,l=0,r=1;i<=n;++i){
		p[i]=min(r-i,p[l+r-i]);
		while(s[i-p[i]]==s[i+p[i]])++p[i];
		if(i+p[i]>r){
			l=i-p[i];
			r=i+p[i];
		}
		if(i!=1 and i!=n)cout<<p[i]-1<<' ';
	}
}
