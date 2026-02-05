#include<bits/stdc++.h>
using namespace std;
using i64 = long long;
#define int i64
#define vi vector<int>
#define vvi vector<vi>
#define pii pair<int, int>
#define fi first
#define se second
#define sz(x) (int)(x).size()
 
const int MOD = 1e9 + 7;
 
inline int binpow(int a, int b){
    int ret = 1;
    while(b){
        if(b & 1){
            ret = (ret * a) % MOD;
        }
        a = (a * a) % MOD;
        b >>= 1;
    }
    return ret;
}
 
struct Node{
    int len, cnt;
    Node(int l, int c) : len(l), cnt(c % MOD) {}
    Node() : Node(0, 0) {}
    inline Node combine(Node &other){
        if(len == other.len) return {len, cnt + other.cnt};
        else if(len > other.len) return {len, cnt};
        else return {other.len, other.cnt};
    }
};
 
struct SegTree{
    vector<Node> st;
    SegTree(int n) : st(4 * n) {}
 
    inline void reset(){
        fill(st.begin(), st.end(), Node());
        return;
    }
 
    inline void update(int pos, Node &node, int v, int tl, int tr){
        if(tl == tr){
            st[v] = node;
            return;
        }
        int mid = (tl + tr) / 2;
        if(pos <= mid){
            update(pos, node, 2 * v, tl, mid);
        }
        else{
            update(pos, node, 2 * v + 1, mid + 1, tr);
        }
        st[v] = st[2 * v].combine(st[2 * v + 1]);
        return;
    }
 
    inline Node query(int ql, int qr, int v, int tl, int tr){
        if(ql > tr || tl > qr) return Node(LLONG_MIN, LLONG_MIN);
        if(tl >= ql && tr <= qr) return st[v];
        int mid = (tl + tr) / 2;
        Node left = query(ql, qr, 2 * v, tl, mid), right = query(ql, qr, 2 * v + 1, mid + 1, tr);
        return left.combine(right);
    }
};
 
signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n;
    cin >> n;
    vi a(n);
    for(int &i : a){
        cin >> i;
    }
    
    vi order(n);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](const int lhs, const int rhs){return a[lhs] == a[rhs] ? lhs < rhs : a[lhs] > a[rhs];} );
    SegTree st(n + 1);
    vector<Node> suff_lis(n), pref_lds(n);
    for(int &i : order){
        Node node = st.query(i + 2, n + 1, 1, 1, n + 1);
        if(++node.len == 1) node.cnt = 1;
        suff_lis[i] = node;
        st.update(i + 1, suff_lis[i], 1, 1, n + 1);
    }
    st.reset();
    sort(order.begin(), order.end(), [&](const int lhs, const int rhs){return a[lhs] == a[rhs] ? lhs < rhs : a[lhs] < a[rhs];} );
    for(int &i : order){
        Node node = st.query(i + 2, n + 1, 1, 1, n + 1);
        if(++node.len == 1) node.cnt = 1; 
        pref_lds[i] = node;
        st.update(i + 1, pref_lds[i], 1, 1, n + 1);
    }
 
    Node mx;
    for(int i = 0; i < n; i++){
        Node temp(pref_lds[i].len + suff_lis[i].len - 1, (pref_lds[i].cnt * suff_lis[i].cnt) % MOD);
        mx = mx.combine(temp);
    }
    cout << mx.len << " " << (mx.cnt * binpow(2, n - mx.len)) % MOD << "\n";
    return 0;
}
