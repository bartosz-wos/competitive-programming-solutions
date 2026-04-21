#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using db=double;
using cd=complex<db>;
constexpr int SZ=1<<19;
constexpr db PI=acos(-1);
 
string s;
vector<cd>A(SZ,0),B(SZ,0);
 
void fft(vector<cd>&a, bool inv){
	int n=a.size();
	for(int i=1,j=0;i<n;++i){
		int bit=n>>1;
		for(;j&bit;bit>>=1)
			j^=bit;
		j^=bit;
		if(i<j)
			swap(a[i],a[j]);
	}
 
	for(int len=2;len<=n;len<<=1){
		db ang=2*PI/len*(inv?-1:1);
		cd wn(cos(ang),sin(ang));
		for(int i=0;i<n;i+=len){
			cd w(1);
			for(int j=0;2*j<len;++j){
				cd u=a[i+j];
				cd v=w*a[i+j+len/2];
				a[i+j]=u+v;
				a[i+j+len/2]=u-v;
				w*=wn;
			}
		}
	}
	if(inv)
		for(cd&x:a)
			x/=n;
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int n,m;
	cin>>n>>m;
	for(int i=0,x;i<n;++i){
		cin>>x;
		A[i]=x;
	}
	for(int i=0,x;i<m;++i){
		cin>>x;
		B[m-i-1]=x;
	}
	fft(A,0);
	fft(B,0);
	for(int i=0;i<SZ;++i)
		A[i]*=B[i];
	fft(A,1);
	for(int i=0;i<n+m-1;++i)
		cout<<llround(A[i].real())<<' ';
}
