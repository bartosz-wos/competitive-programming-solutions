#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define F first
#define S second

const int N=5e5+10;
const ll mod=998244353;
const ll LINF=1e18+7;

pll operator +(pll a, pll b){return {a.F*b.F%mod, (b.F*a.S%mod+b.S)%mod};}
pll operator *(pll x, int k){
    pll res=make_pair(1, 0);
    while(k){
        if (k&1) res=res+x;
        x=x+x;
        k>>=1;
    }
    return res;
}

pll t[N<<2], tag[N<<2];

void update(int v, int l, int r, pll k){
    t[v]=k*(r-l+1);
    tag[v]=k;
}
void push(int v, int l, int r){
    if (tag[v]!=make_pair(LINF, LINF)){
        int m=l+r>>1;
        update(v<<1, l, m, tag[v]);
        update(v<<1|1, m+1, r, tag[v]);
        tag[v]=make_pair(LINF, LINF);
    }
}
void build(int v, int l, int r){
    tag[v]=make_pair(LINF, LINF);
    if (l==r){
        cin >> t[v].F >> t[v].S;
        return;
    }
    int m=l+r>>1;
    build(v<<1, l, m);
    build(v<<1|1, m+1, r);
    t[v]=t[v<<1]+t[v<<1|1];
}
void modify(int v, int l, int r, int ql, int qr, pll k){
    if (ql<=l&&r<=qr){
        update(v, l, r, k);
        return;
    }
    int m=l+r>>1;
    push(v, l, r);
    if (ql<=m) modify(v<<1, l, m, ql, qr, k);
    if (qr>m) modify(v<<1|1, m+1, r, ql, qr, k);
    t[v]=t[v<<1]+t[v<<1|1];
}
pll query(int v, int l, int r, int ql, int qr){
    if (ql<=l&&r<=qr) return t[v];
    int m=l+r>>1;
    push(v, l, r);
    pll res={1, 0};
    if (ql<=m) res=res+query(v<<1, l, m, ql, qr);
    if (qr>m) res=res+query(v<<1|1, m+1, r, ql, qr);
    return res;
}

void _solve(){
    int n, q;
    cin >> n >> q;
    build(1, 1, n);
    while(q--){
        int op, l, r;
        cin >> op >> l >> r;
        l++;
        if (op){
            ll x;
            cin >> x;
            pll res=query(1, 1, n, l, r);
            cout << (res.F*x%mod+res.S)%mod << '\n';
        }else{
            pll k;
            cin >> k.F >> k.S;
            modify(1, 1, n, l, r, k);
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int _t=1;
    //cin >> _t;
    while(_t--) _solve();
}
