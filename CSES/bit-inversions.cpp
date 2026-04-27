#include<bits/stdc++.h>
using namespace std;
using ll=long long;
 
int n;
struct node{
    int mx[2],pref[2],suf[2],cnt;
    friend void merge(node&e, const node&a, const node&b){
        e.mx[0]=max({a.mx[0],b.mx[0],a.suf[0]+b.pref[0]});
        e.mx[1]=max({a.mx[1],b.mx[1],a.suf[1]+b.pref[1]});
        if(a.pref[0]==a.cnt)
            e.pref[0]=a.pref[0]+b.pref[0];
        else
            e.pref[0]=a.pref[0];
        if(a.pref[1]==a.cnt)
            e.pref[1]=a.pref[1]+b.pref[1];
        else
            e.pref[1]=a.pref[1];
        if(b.suf[0]==b.cnt)
            e.suf[0]=b.suf[0]+a.suf[0];
        else
            e.suf[0]=b.suf[0];
        if(b.suf[1]==b.cnt)
            e.suf[1]=b.suf[1]+a.suf[1];
        else
            e.suf[1]=b.suf[1];
        e.cnt=a.cnt+b.cnt;
    }
}T[1<<20];
 
string s;
 
void build(int k=1, int l=1, int r=n){
    if(l==r){
        if(s[l]=='0'){
            T[k].mx[0]=T[k].pref[0]=T[k].suf[0]=1;
            T[k].mx[1]=T[k].pref[1]=T[k].suf[1]=0;
            T[k].cnt=r-l+1;
        }else{
            T[k].mx[0]=T[k].pref[0]=T[k].suf[0]=0;
            T[k].mx[1]=T[k].pref[1]=T[k].suf[1]=1;
            T[k].cnt=r-l+1;
        }
        return;
    }
    int mid=(l+r)>>1;
    build(k<<1,l,mid);
    build(k<<1|1,mid+1,r);
    merge(T[k],T[k<<1],T[k<<1|1]);
}
 
void upd(int i, int k=1, int l=1, int r=n){
    if(l==r){
        if(s[l]=='0'){
            T[k].mx[0]=T[k].pref[0]=T[k].suf[0]=1;
            T[k].mx[1]=T[k].pref[1]=T[k].suf[1]=0;
            T[k].cnt=r-l+1;
        }else{
           T[k].mx[0]=T[k].pref[0]=T[k].suf[0]=0;
            T[k].mx[1]=T[k].pref[1]=T[k].suf[1]=1;
            T[k].cnt=r-l+1;
        }
        return;
    }
    int mid=(l+r)>>1;
    if(i<=mid)
        upd(i,k<<1,l,mid);
    else
        upd(i,k<<1|1,mid+1,r);
    merge(T[k],T[k<<1],T[k<<1|1]);
}
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>s;
    n=s.size();
    s='0'+s;
    build();
    int q;
    cin>>q;
    while(q--){
        int x;
        cin>>x;
        s[x]=s[x]=='0'?'1':'0';
        upd(x);
        cout<<max(T[1].mx[0],T[1].mx[1])<<' ';
    }
}
