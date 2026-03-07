#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using db=double;
using cd=complex<db>;
constexpr db PI=acos(-1);
 
void fft(vector<cd>&a,bool f){
	int n=a.size();
	if(n==1)
		return;
	vector<cd>a0(n/2),a1(n/2);
	for(int i=0;2*i<n;++i){
		a0[i]=a[2*i];
		a1[i]=a[2*i+1];
	}
	fft(a0,f);
	fft(a1,f);
	db ang=2*PI/n*(f?-1:1);
	cd w(1,0),wn(cos(ang),sin(ang));
	for(int i=0;2*i<n;++i){
		a[i]=a0[i]+w*a1[i];
		a[i+n/2]=a0[i]-w*a1[i];
		if(f){
			a[i]/=2;
			a[i+n/2]/=2;
		}
		w*=wn;
	}
}
 
vector<ll>DFT(const vector<ll>&a, const vector<ll>&b){
	vector<cd>fa(a.begin(),a.end()),fb(b.begin(),b.end());
	ll n=1;
	while(n<a.size()+b.size())
		n<<=1;
	fa.resize(n);
	fb.resize(n);
	fft(fa,0);
	fft(fb,0);
	for(int i=0;i<n;++i)
		fa[i]*=fb[i];
	fft(fa,1);
	vector<ll>res(n);
	for(int i=0;i<n;++i)
		res[i]=round(fa[i].real());
	return res;
}
 
void solve(){
	string sa,sb;
	cin>>sa>>sb;
	vector<ll>a(sa.length()),b(sb.length());
	for(int i=sa.length()-1;i>=0;--i)
		a[sa.length()-i-1]=(sa[i]-48);
	for(int i=sb.length()-1;i>=0;--i)
		b[sb.length()-i-1]=(sb[i]-48);
	vector<ll>res=DFT(a,b);
	ll carry=0;
	for(int i=0;i<res.size();++i){
		res[i]+=carry;
		carry=res[i]/10;
		res[i]%=10;
	}
	int i=res.size()-1;
	while(i>=0 and res[i]==0)
		--i;
	if(i==-1)
		cout<<0;
	for(;i>=0;--i)
		cout<<res[i];
	cout<<'\n';
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
