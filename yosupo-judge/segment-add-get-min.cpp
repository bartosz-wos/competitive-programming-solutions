#include<bits/stdc++.h>
using namespace std;
using ll=long long;

constexpr ll inf=1ll<<62;
constexpr int MINX=-1e9;
constexpr int MAXX=1e9+5;

struct line{
        ll a,b;
        ll eval(ll x)const{
                return a*x+b;
        }
};

struct node{
        line l={0,inf};
        int lc=-1,rc=-1;
};

vector<node>st;

int get_node(){
        st.push_back(node());
        return st.size()-1;
}

int add(int k, ll l, ll r, line nl){
        if(!~k){
                k=get_node();
                st[k].l=nl;
                return k;
        }
        ll mid=l+(r-l)/2;
        bool lef=nl.eval(l)<st[k].l.eval(l);
        bool m=nl.eval(mid)<st[k].l.eval(mid);
        if(m)swap(st[k].l,nl);
        if(r-l<=1)return k;
        if(lef!=m)st[k].lc=add(st[k].lc, l, mid, nl);
        else st[k].rc=add(st[k].rc, mid, r, nl);
        return k;
}

int add_seg(int k, ll l, ll r, ll ql, ll qr, line nl){
        if(l>=qr or r<=ql)return k;
        if(!~k)k=get_node();
        if(ql<=l and r<=qr)return add(k, l, r, nl);
        ll mid=l+(r-l)/2;
        st[k].lc=add_seg(st[k].lc,l,mid,ql,qr,nl);
        st[k].rc=add_seg(st[k].rc,mid,r,ql,qr,nl);
        return k;
}

ll get(int k, ll l, ll r, ll x){
        if(k==-1)return inf;
        ll mid=l+(r-l)/2;
        if(r-l<=1)return st[k].l.eval(x);
        if(x<mid)return min(st[k].l.eval(x),get(st[k].lc,l,mid,x));
        return min(st[k].l.eval(x), get(st[k].rc,mid,r,x));
}

int main(){
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
        st.reserve(10000000);
        int n,q;
        cin>>n>>q;
        int rt=-1;
        while(n--){
                ll l,r,a,b;
                cin>>l>>r>>a>>b;
                rt=add_seg(rt, MINX, MAXX, l, r, {a,b});
        }
        while(q--){
                int t;
                cin>>t;
                if(!t){
                        ll l,r,a,b;
                        cin>>l>>r>>a>>b;
                        rt=add_seg(rt, MINX, MAXX, l, r, {a,b});
                }else{
                        ll x;
                        cin>>x;
                        ll ret=get(rt,MINX,MAXX,x);
                        if(ret==inf)
                                cout<<"INFINITY\n";
                        else cout<<ret<<'\n';
                }
        }
}
