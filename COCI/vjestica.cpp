#include<bits/stdc++.h>
using namespace std;
using ll=long long;

constexpr int N=16;

int n;
string s[N];
int cnt[N][26],mn[26];
int f[1<<N];

int val(int mask){
    int ret=0;
    for(int c=0;c<26;++c){
        mn[c]=1e9;
        for(int i=0;i<n;++i)
            if(mask&(1<<i))
                mn[c]=min(mn[c],cnt[i][c]);
        ret+=mn[c];
    }
    return ret;
}

int go(int mask){
    if(!mask)return 0;
    if(~f[mask])return f[mask];
    int pref=val(mask);
    if(__builtin_popcount(mask)==1)return f[mask]=pref;
    int ret=1e9;
    for(int i=(mask-1)&mask;i;i=(i-1)&mask)
        ret=min(ret,go(i)+go(mask^i)-pref);
    return f[mask]=ret;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n;
    for(int i=0;i<n;++i){
        cin>>s[i];
        for(char c:s[i])
            ++cnt[i][c-97];
    }
    memset(f,-1,sizeof f);
    cout<<go((1<<n)-1)+1<<'\n';
}
