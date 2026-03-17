#include<bits/stdc++.h>
using namespace std;
using ll=long long;

#define fi first
#define se second

int n;
int a[100005];
ll p[100005];
ll s[100005];

void __solve(){
    cin>>n;
    p[0]=0;
    for(int i=1;i<=n;++i){
        cin>>a[i];
        p[i]=a[i]+p[i-1];
    }
    s[n+1]=0;
    for(int i=n;i>=1;--i){
        s[i]=a[i]+s[i+1];
    }
    int cnt=0;
    for(int i=1;i<=n;++i)
        if(!a[i]){
            if(p[i]==s[i])cnt+=2;
            if(p[i]==s[i]+1 or s[i]==p[i]+1)++cnt;
        }
    cout<<cnt<<'\n';
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int tc=1;
    cin>>tc;
    while(tc--)__solve();
}
