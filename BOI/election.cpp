#include<bits/stdc++.h>
using namespace std;
using ll=long long;

struct Node{
    int l,r,s,a;
    Node operator+(const Node&other)const{
        Node ans;
        ans.l=max(l,s+other.l);
        ans.r=max(other.r,other.s+r);
        ans.s=s+other.s;
        ans.a=max({a+other.s,s+other.a,l+other.r});
        return ans;
    }
};

struct seg{
    vector<Node>it;
    int n;
    seg(int _n=0){
        n=_n;
        it.resize(4*n+5);
    }
    void build(string&s, int k, int l, int r){
        if(l==r){
            if(s[l-1]=='C') it[k]={0,0,-1,0};
            else it[k]={1,1,1,1};
            return;
        }
        int mid=(l+r)>>1;
        build(s,k<<1,l,mid);
        build(s,k<<1|1,mid+1,r);
        it[k]=it[k<<1]+it[k<<1|1];
    }
    Node get(int k, int l, int r, int ql, int qr){
        if(r<ql or l>qr or l>r)return {0,0,0,0};
        if(ql<=l and r<=qr)return it[k];
        int mid=(l+r)>>1;
        return get(k<<1,l,mid,ql,qr)+get(k<<1|1,mid+1,r,ql,qr);
    }
    int get(int l, int r){
        Node t=get(1,1,n,l,r);
        return t.a;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin>>n;
    string s;
    cin>>s;
    seg it(n);
    it.build(s,1,1,n);
    int q;
    cin>>q;
    while(q--){
        int l,r;
        cin>>l>>r;
        cout<<it.get(l,r)<<'\n';
    }
}
