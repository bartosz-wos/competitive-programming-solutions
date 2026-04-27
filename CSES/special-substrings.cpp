#include<bits/stdc++.h>
using namespace std;
using ll=long long;
 
int n,t;
string s;
bool oc[26];
map<char,int>mp;
map<vector<int>,ll>dp;
 
bool check(vector<int>&v){
    for(int i=0;i<v.size();++i)
        if(v[i]<=0)return 0;
    return 1;
}
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>s;
    n=s.size();
    for(int i=0;i<n;++i){
        int c=s[i]-97;
        if(!oc[c]){
            oc[c]=1;
            mp[s[i]]=t++;
        }
    }
    ll res=0;
    vector<int>f(t,0);
    ++dp[f];
    for(int i=0;i<n;++i){
        int c=mp[s[i]];
        ++f[c];
        if(check(f))
            for(int j=0;j<t;++j)
                --f[j];
        res+=dp[f];
        ++dp[f];
    }
    cout<<res<<'\n';
}
