#include <bits/stdc++.h>
using namespace std;
using ll=long long;

ll gcd(ll a, ll b){
    if(!b)return a;
    return gcd(b,a%b);
}

void solve(){
    int n;
    cin>>n;
    vector<int>a(n);
    ll g=0;
    for(int&i:a){
        cin>>i;
        g=gcd(i,g);
    }
    int cnt=0;
    for(int&i:a)if(i==g)++cnt;
    cout<<n-cnt<<'\n';
}

int main() {
	int t;
	cin>>t;
	while(t--)
	    solve();
}

