#include <bits/stdc++.h>
using namespace std;

void solve(){
    int x;
    cin>>x;
    int p=1;
    while(p<=x)p<<=1;
    p>>=1;
    cout<<(x-p)*2<<'\n';
}

int main() {
    int t=1;
    cin>>t;
    while(t--)solve();
}

