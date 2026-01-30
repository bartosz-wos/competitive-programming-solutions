#include<bits/stdc++.h>
using namespace std;
using ll=long long;

constexpr int mod=998244353;

int f(char x){
    if(x>='a' and x<='z')return x-'a';
    if(x>='A' and x<='Z')return x-'A'+26;
    return x-'0'+52;
}

int cnt[11][62][62];
ll dp[11][62][62][62];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin>>n;
    set<string>sets;
    for(int i=1;i<=n;++i){
        string s;
        cin>>s;
        if(!sets.count(s)){
            string t=s;
            reverse(t.begin(),t.end());
            ++cnt[s.size()][f(s[0])][f(s.back())];
            if(s!=t)++cnt[s.size()][f(s.back())][f(s[0])];
            sets.insert(s);
            sets.insert(t);
        }
    }
    for(int i=3;i<=10;++i)
        for(int j=0;j<62;++j)
            for(int k=0;k<62;++k)
                for(int l=0;l<62;++l){
                    for(int m=0;m<62;++m)
                        dp[i][j][k][l]+=1ll*cnt[i][j][m]*cnt[i][k][m]*cnt[i][l][m];
                    dp[i][j][k][l]%=mod;
                }
    ll res=0;
    for(int i=3;i<=10;++i)
        for(int j=0;j<62;++j)
            for(int k=0;k<62;++k)
                for(int l=0;l<62;++l){
                    ll tmp=0;
                    for(int m=0;m<62;++m)
                        tmp+=dp[i][j][k][m]*dp[i][j][l][m]%mod*dp[i][k][l][m]%mod;
                    res+=tmp*dp[i][j][k][l]%mod;
                    res%=mod;
                }
    cout<<res<<'\n';
}
