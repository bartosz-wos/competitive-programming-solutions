#include<bits/stdc++.h>
using namespace std;
using ll=long long;
vector<int>num;
ll dp[30][12][12][2];

ll get(int pos, int p1, int p2, int f){
        if(pos==num.size())
                return 1;
        if(dp[pos][p1][p2][f]!=-1)
                return dp[pos][p1][p2][f];
        int lim=9;
        if(!f)
                lim=num[pos];
        ll res=0;
        for(int dgt=0;dgt<=lim;++dgt){
                if(p1==11 and p2==11)
                        res+=get(pos+1,dgt==0?11:dgt,11,(f or dgt<lim));
                else if(dgt!=p1 and dgt!=p2)
                        res+=get(pos+1,dgt,p1,(f or dgt<lim));
        }
        return dp[pos][p1][p2][f]=res;
}

ll solve(ll n){
        if(n<0)
                return 0;
        if(n==0)
                return 1;
        num.clear();
        while(n){
                num.emplace_back(n%10);
                n/=10;
        }
        reverse(num.begin(),num.end());
        memset(dp,-1,sizeof(dp));
        return get(0,11,11,0);
}

int main(){
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
        ll a,b;
        cin>>a>>b;
        cout<<solve(b)-solve(a-1);
}

