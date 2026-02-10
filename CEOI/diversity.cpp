#include<iostream>
#include<stack>
#include<map>
#include<vector>
#include<string>
#include<cassert>
#include<unordered_map>
#include <queue>
#include <cstdint>
#include<cstring>
#include<limits.h>
#include<cmath>
#include<set>
#include<algorithm>
#include <iomanip>
#include<numeric>
#include<bitset>
using namespace std;
#define ll long long
#define f first
#define s second
#define pii pair<int,int>
#define ppii pair<int,pii>
#define vi vector<int>
#define pb push_back
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define F(n) for(int i=0;i<n;i++)
#define lb lower_bound
#define ub upper_bound
#define fastio ios::sync_with_stdio(false);cin.tie(NULL);
#pragma GCC optimize ("03,unroll-lopps")
#define int long long
using namespace std;
const int mod=1e9+7,mxn=3e5+5,inf=1e18,minf=-1e18,lg=30,base=191;
//#undef int
int n,q;
int val[mxn+10];
int root=600,cursz[mxn+10],ans[mxn+10];
int get(int x){return (x*(x+1))/2;}
int get2(int x){return (x*(x+1)*(2*x+1))/6;}
bool cmp(pair<pii,int> a,pair<pii,int> b){
    if((a.f.f/root)==(b.f.f/root))return a.f.s<b.f.s;
    return (a.f.f/root)<(b.f.f/root);
}
int have[mxn+10],sz=0,cnt[mxn+10],where[mxn+10];
vector<int>batch;
void add(int x,int y){
    if(cursz[x])cnt[cursz[x]]--;
    if(cursz[x]&&cnt[cursz[x]]==0){
        have[where[cursz[x]]]=0;
        batch.pb(where[cursz[x]]);
        //batch size should be <= sqrt
    }
    if(batch.size()>root)assert(0);
    cursz[x]+=y;
    if(cursz[x])cnt[cursz[x]]++;
    if(cursz[x]&&cnt[cursz[x]]==1){
        if(batch.size())where[cursz[x]]=batch.back(),batch.pop_back();
        else where[cursz[x]]=sz++;
        have[where[cursz[x]]]=cursz[x];
    }
}
/*
mo's algo would this pass??
*/
int l=-1,r=-1;
int solveodd(int sum,int x,int t){
    if(t==0)return 0;
    int add=(get(t)*x+t*sum-x*t)*(r-l+1);
    add+=(x)*((get(t)*x+t*sum));
    add-=(sum*sum*t);
    add-=(get(t)*2*x*sum);
    add-=(get2(t)*x*x);
    return add;
}
void getans(int x){
    vector<pii>bro;
    for(int i=0;i<sz;i++)if(have[i]){
        bro.pb({have[i],cnt[have[i]]});
    }
    sort(all(bro));
    int even=0,odd=0,at=0;
    for(auto i:bro){
        //2 inside
        ans[x]+=i.s*(i.f*(i.f+1))/2;
        //1 inside
        ans[x]+=(r-l+1-i.f)*(i.f)*i.s;
        //2 outside
        int te=(i.s+(at%2))/2,to=(i.s+!(at%2))/2;
        ans[x]+=solveodd(odd,i.f,to)+solveodd(even,i.f,te);
        even+=i.f*te;
        odd+=i.f*to;
        at+=i.s;
    }
}
int32_t main(){
    fastio
    cin>>n>>q;
    for(int i=1;i<=n;i++)cin>>val[i];
    vector<pair<pii,int>>qry(q);
    for(int i=0;i<q;i++)cin>>qry[i].f.f>>qry[i].f.s,qry[i].s=i;
    sort(all(qry),cmp);
    for(int i=0;i<q;i++){
        if(l==-1){
            for(int c=qry[i].f.f;c<=qry[i].f.s;c++)add(val[c],1);
            l=qry[i].f.f,r=qry[i].f.s;
        }
        while(r<qry[i].f.s){
            add(val[r+1],1);
            r++;
        }
        while(r>qry[i].f.s){
            add(val[r],-1);
            r--;
        }
        while(l>qry[i].f.f){
            add(val[l-1],1);
            l--;
        }
        while(l<qry[i].f.f){
            add(val[l],-1);
            l++;
        }
        getans(qry[i].s);
    }
    for(int i=0;i<q;i++)cout<<ans[i]<<"\n";
}
