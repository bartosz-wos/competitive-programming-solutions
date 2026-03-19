#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define hi ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define pb push_back
#define xx first
#define yy second
#define mem(a,d) memset(a,d,sizeof a)
#define memc(a,d) memcpy(a,d,sizeof a)
#define Maxn 1e18
#define PI 2*acos(0.0)
#define endl "\n"
#define test cout<<" mike_testing "
#define N 100009
long long mod=1e9+7;
long long bigmod( long long l,  long long r)
{
    if(r == 0)
        return 1LL;
    long long res = bigmod(l, r / 2)% mod;
    res = (res * res) % mod;
    if(r & 1)
        res = (res * l)% mod;
    return res% mod;
}

void solve()
{
    int n;
    cin>>n;
    long long cnt=0;
    int x[n+5];
    set<int>st;
    map<int,int>mp1;
    for(int i=1; i<=n; i++){cin>>x[i];st.insert(x[i]);}
    int id=1;
    for(auto it:st){
        mp1[it]=id;
        id++;
    }
    for(int i=1;i<=n;i++)x[i]=mp1[x[i]];
    for(int i=1; i<=n; i++)
    {    int mp[n+5]={0};
        for(int j=i; j<=n; j++)
        {
            mp[x[j]]++;
            long long a=0;
            for(int k=j+1; k<=n; k++)
            {
                if(mp[x[k]])
                {
                    if(a)
                    {
                        a=(a*(a+1))/2;
                        cnt+=a;
                    }
                    a=0;
                }
                else  a++;
            }
            if(a)
            {
                a=(a*(a+1))/2;
                cnt+=a;
            }
            //  cout<<i<<" "<<j<<" "<<cnt<<endl;
        }
    }
    cout<<cnt<<endl;
}
signed main()
{   hi;
    long long t,i;
    t=1;
    cin>>t;
    while(t--) solve();
    return 0;
}
