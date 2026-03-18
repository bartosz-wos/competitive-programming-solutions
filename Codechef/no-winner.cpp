#include<bits/stdc++.h>
using namespace std;
using ll=long long;

#define fi first
#define se second

void __solve(){
    int a,b,c,m;
    cin>>a>>b>>c>>m;
    if(abs(a-b)<=m or abs(c-a)<=m or abs(c-b)<=m)cout<<"YES\n";
    else cout<<"NO\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int tc=1;
    cin>>tc;
    while(tc--)__solve();
}
