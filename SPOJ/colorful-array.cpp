#include<bits/stdc++.h>
using namespace std;
using ll=long long;
 
constexpr int MAXN=2e5+5;
constexpr int MAXQ=2e5+5;
 
int l[MAXQ],r[MAXQ],c[MAXQ];
int dsu[MAXN];
int ans[MAXN];
 
void init(){
    iota(dsu,dsu+MAXN,0);
}
 
int find(int x){
    if(dsu[x]==x)return x;
    return dsu[x]=find(dsu[x]);
}
 
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    init();
    int n,q;
    cin>>n>>q;
    for(int i=0;i<q;++i)
        cin>>l[i]>>r[i]>>c[i];
    for(int i=q-1;i>=0;--i){
        for(int v=find(l[i]);v<=r[i];v=find(v)){
            ans[v]=c[i];
            dsu[v]=v+1;
        }
    }
    for(int i=1;i<=n;++i)
        cout<<ans[i]<<'\n';
} 
