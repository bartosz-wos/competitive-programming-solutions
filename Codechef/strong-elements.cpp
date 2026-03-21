#include <bits/stdc++.h>
using namespace std;
using ll=long long;

ll gcd(ll a, ll b){
    if(!a and !b)return 1;
    if(!b)return a;
    if(!a)return b;
    return gcd(b,a%b);
}

void solve(){
    int n;
    cin>>n;
    vector<int>a(n+1),p(n+2,0),s(n+2,0);
    for(int i=1;i<=n;++i){
        cin>>a[i];
        p[i]=gcd(a[i],p[i-1]);
    }
    int cnt=0;
    for(int i=n;i>=1;--i){
        s[i]=gcd(a[i],s[i+1]);
        ll a=p[i-1],b=s[i+1];
        if(gcd(a,b)!=1)++cnt;
    }
    cout<<cnt<<'\n';
}

int main() {
	int t;
	cin>>t;
	while(t--)
	    solve();
}

