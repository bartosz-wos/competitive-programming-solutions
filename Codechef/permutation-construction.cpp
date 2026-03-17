#include<bits/stdc++.h>
using namespace std;
using ll=long long;

#define fi first
#define se second

void __solve(){
    int n;
    cin>>n;
    int i=1,j=n;
    while(i<j){
        cout<<i<<' '<<j<<' ';
        ++i;
        --j;
    }
    if(n&1)cout<<i;
    cout<<'\n';
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int tc=1;
    cin>>tc;
    while(tc--)__solve();
}
