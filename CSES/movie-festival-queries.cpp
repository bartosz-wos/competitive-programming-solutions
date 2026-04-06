#include<bits/stdc++.h>
using namespace std;
using ll=long long;
 
constexpr int MAXN=1e6;
constexpr int LGM=20;
int n,q;
int rmq[LGM][MAXN];
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n>>q;
    for(int i=0;i<MAXN;++i)
        rmq[0][i]=MAXN;
    for(int i=0;i<n;++i){
        int a,b;
        cin>>a>>b;
        --a,--b;
        rmq[0][a]=min(rmq[0][a],b);
    }
    for(int i=MAXN-2;i>=0;--i)
        rmq[0][i]=min(rmq[0][i],rmq[0][i+1]);
    for(int p=1;p<LGM;++p)
        for(int i=0;i<MAXN;++i)
            rmq[p][i]=rmq[p-1][i]!=MAXN?rmq[p-1][rmq[p-1][i]]:MAXN;
    while(q--){
        int a,b;
        cin>>a>>b;
        --a,--b;
        int ret=0;
        for(int p=LGM-1;p>=0;--p)
            if(rmq[p][a]<=b)ret+=(1<<p),a=rmq[p][a];
        cout<<ret<<'\n';
    }
}
