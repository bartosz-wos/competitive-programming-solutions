#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using cd=complex<double>;

constexpr int N=1e5+5;
constexpr double PI=acos(-1.0);

string s;

void fft(vector<cd>&a,bool inv){
    int n=a.size();
    if(n==1)return;
    vector<cd>a0(n/2),a1(n/2);
    for(int i=0;2*i<n;++i){
        a0[i]=a[2*i];
        a1[i]=a[2*i+1];
    }
    fft(a0,inv);
    fft(a1,inv);
    double ang=2*PI/n*(inv?-1:1);
    cd w(1),wn(cos(ang),sin(ang));
    for(int i=0;2*i<n;++i){
        cd u=a0[i];
        cd v=w*a1[i];
        a[i]=u+v;
        a[i+n/2]=u-v;
        w*=wn;
        if(inv){
            a[i]/=2;
            a[i+n/2]/=2;
        }
    }
}

vector<int>mul(vector<int>&a,vector<int>&b){
    vector<cd>A(a.begin(),a.end());
    vector<cd>B(b.begin(),b.end());
    int sz=1;
    while(sz<A.size()+B.size())sz<<=1;
    A.resize(sz);
    B.resize(sz);
    fft(A,0);
    fft(B,0);
    for(int i=0;i<sz;++i)
        A[i]*=B[i];
    fft(A,1);
    vector<int>res(sz);
    for(int i=0;i<sz;++i)
        res[i]=floor(A[i].real()+0.5);
    return res;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>s;
    int n=s.size();
    vector<int>a(n+1),b(n+1);
    for(int i=1;i<=n;++i){
        if(s[i-1]=='A')a[i]=1;
        else b[n-i]=1;
    }
    vector<int>c=mul(a,b);
    for(int i=1;i<n;++i)
        cout<<c[i+n]<<'\n';
}
