#include<bits/stdc++.h>
using namespace std;
using ll=long long;

#define fi first
#define se second

int a[20],b[20];

void __solve(){
    int n=16;
    for(int i=1;i<=n;++i){
        cin>>a[i];
        b[i]=a[i];
    }
    sort(b+1,b+1+n);
    for(int i=1;i<=n;++i){
        a[i]=lower_bound(b+1,b+1+n,a[i])-b;
        cout<<(int)log2(a[i])<<' ';
    }
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
