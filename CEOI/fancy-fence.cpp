#include<bits/stdc++.h>
using namespace std;
using ll=long long;

constexpr int mod=1e9+7;

vector<int>fnxt(vector<ll>&v){
    int n=v.size();
    vector<int>res(n,n);
    stack<int>s;
    for(int i=n-1;i>=0;--i){
        while(!s.empty() and v[i]<=v[s.top()])s.pop();
        if(!s.empty())res[i]=s.top();
        s.push(i);
    }
    return res;
}

vector<int>fprev(vector<ll>&v){
    int n=v.size();
    vector<int>res(n,0);
    stack<int>s;
    for(int i=0;i<n;++i){
        while(!s.empty() and v[i]<v[s.top()])s.pop();
        if(!s.empty())res[i]=s.top();
        s.push(i);
    }
    return res;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin>>n;
    vector<ll>h(n+1),w(n+1),p(n+1);
    for(int i=1;i<=n;++i)cin>>h[i];
    for(int i=1;i<=n;++i){
        cin>>w[i];
        p[i]=p[i-1]+w[i];
    }
    vector<int>nxt=fnxt(h),prev=fprev(h);
    ll res=0;
    for(int i=1;i<=n;++i){
        ll ver=h[i]*(h[i]+1ll)/2%mod;
        ll before=(p[i-1]-p[prev[i]])%mod;
        ll after=(p[nxt[i]-1]-p[i])%mod;
        res+=after*before%mod*ver%mod;
        res+=w[i]*before%mod*ver%mod;
        res%=mod;
        res+=w[i]*after%mod*ver%mod;
        res+=w[i]*(w[i]+1)/2%mod*ver%mod;
        res%=mod;
    }
    cout<<res<<'\n';
}
