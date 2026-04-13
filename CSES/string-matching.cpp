#include<bits/stdc++.h>
using namespace std;
using ll=long long;
constexpr int mod=1e9+7;
constexpr ll p[]={29,31,37,41,43,47,53,59,61,67,71,73,79,83,89};
 
struct hsh{
	string s;
	vector<ll>h[15];
	vector<ll>pot[15];
	hsh(string s):s(s){
		for(int i=0;i<15;++i){
			h[i].resize(s.size()+1);
			h[i][0]=0;
		}
		for(int i=0;i<15;++i){
			pot[i].resize(s.size()+1);
			pot[i][0]=1;
		}
		for(int i=1;i<=s.size();++i)
			for(int j=0;j<15;++j){
				h[j][i]=(h[j][i-1]*p[j]+s[i-1]-96)%mod;
				pot[j][i]=pot[j][i-1]*p[j]%mod;
			}
	}
	vector<int> get(int l, int r){
		vector<int>ret(15,0);
		for(int i=0;i<15;++i){
			ret[i]=(h[i][r]-h[i][l-1]*pot[i][r-l+1]%mod+mod);
			if(ret[i]>=mod)ret[i]-=mod;
		}
		return ret;
	}
};
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	string t,p;
	cin>>t>>p;
	hsh txt(t);
	hsh pat(p);
	int cnt=0;
	for(int i=1;i+p.size()-1<=t.size();++i)
		if(txt.get(i,i+p.size()-1)==pat.get(1,p.size()))
			++cnt;
	cout<<cnt<<'\n';
}

