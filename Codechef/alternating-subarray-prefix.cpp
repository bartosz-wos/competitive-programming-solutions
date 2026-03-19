#include <bits/stdc++.h>
using namespace std;

int sgn(int x){
    return (x>0)-(x<0);
}

void solve(){
    int n;
    cin>>n;
    vector<int>a(n),ans(n);
    for(int&i:a)cin>>i;
    int nxt=n-1;
    ans[n-1]=1;
    for(int i=n-2;i>=0;--i){
        if( sgn(a[i])==sgn(a[i+1]) )nxt=i;
        ans[i]=nxt-i+1;
    }
    for(const int&i:ans)cout<<i<<' ';
    cout<<'\n';
}

int main() {
    int t;
    cin>>t;
    while(t--)solve();
}

