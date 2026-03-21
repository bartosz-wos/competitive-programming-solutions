#include <bits/stdc++.h>
using namespace std;

void solve(){
    int n,k;
    cin>>n>>k;
    while(n%k!=0)--n;
    cout<<n*n/k/k<<'\n';
}

int main() {
    int t;
    cin>>t;
    while(t--)
        solve();
}

