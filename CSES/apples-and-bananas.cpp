#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using db=double;
using cd=complex<db>;
constexpr db PI=acos(-1);
constexpr int SZ=1<<19;
 
void fft(vector<cd>&a,bool f){
    int n=a.size();
    if(n==1)return;
    vector<cd>nig(n/2),ger(n/2);
    for(int i=0;2*i<n;++i){
        nig[i]=a[2*i];
        ger[i]=a[2*i+1];
    }
    fft(nig,f);
    fft(ger,f);
    db ang=2*PI/n*(f?-1:1);
    cd wn(cos(ang),sin(ang));
    cd w(1);
    for(int i=0;2*i<n;++i){
        cd u=nig[i];
        cd v=w*ger[i];
        a[i]=u+v;
        a[i+n/2]=u-v;
        w*=wn;
        if(f)
            a[i]/=2,a[i+n/2]/=2;
    }
}
 
void solve(vector<cd>&a,vector<cd>&b,const int&k){
    fft(a,0);
    fft(b,0);
    for(int i=0;i<SZ;++i)
        a[i]*=b[i];
    fft(a,1);
    for(int i=2;i<=2*k;++i)
        cout<<llround(a[i].real())<<' ';
}
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int k,n,m;
    cin>>k>>n>>m;
    vector<cd>a(SZ),b(SZ);
    while(n--){
        int x;
        cin>>x;
        a[x]+=1;
    }
    while(m--){
        int x;
        cin>>x;
        b[x]+=1;
    }
    solve(a,b,k);
}
