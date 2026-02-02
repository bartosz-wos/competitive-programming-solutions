#include"biscuits.h"
#include<bits/stdc++.h>
using namespace std;
using ll=long long;

ll n;
map<ll,ll>dp;
ll s[63];

ll f(ll x){
    if(x<=0)return 0;
    if(x==1)return 1;
    if(dp.count(x))return dp[x];
    int k=log2l(x-1);
    dp[x]=f(1ll<<k)+f(min(x,s[k]/n+1)-(1ll<<k));
    return dp[x];
}

ll count_tastiness(ll x, vector<ll>a){
    dp.clear();
    n=x;
    while(a.size()<63)a.push_back(0);
    for(int i=0;i<63;++i)
        s[i]=(!i?0:s[i-1])+a[i]*(1ll<<i);
    return f(s[62]+1);
}
