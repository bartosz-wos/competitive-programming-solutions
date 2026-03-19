#include <bits/stdc++.h>
using namespace std;

void solve(){
    int x,y;
    cin>>x>>y;
    if(x>y+1 or y>x+2)cout<<"NO\n";
    else cout<<"YES\n";
}

int main() {
    int t=1;
    cin>>t;
    while(t--)solve();
}

