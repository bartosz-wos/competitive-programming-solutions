#include<bits/stdc++.h>
using namespace std;
using ll = long long;
int n, q;
int tab[200001];
 
struct Node {
	ll sum, pref, suf, mx;
	friend Node operator + (const Node& a, const Node& b) {
		return {
			a.sum + b.sum,
			max(a.pref, a.sum + b.pref),
			max(b.suf, b.sum + a.suf),
			max({a.mx, b.mx, a.suf + b.pref})
		};
	}
} T[1 << 22];
 
void build(int k = 1, int l = 1, int r = n) {
	if(l == r) {
		T[k] = {
			tab[l],
			max(0, tab[l]),
			max(0, tab[l]),
			max(0, tab[l])
		};
		return;
	}
	int mid = (l + r) >> 1;
	build(k << 1, l, mid);
	build(k << 1 | 1, mid + 1, r);
	T[k] = T[k << 1] + T[k << 1 | 1];
}
 
void upd(int i, int x, int k = 1, int l = 1, int r = n) {
	if(l == r) {
		T[k] = {
			x,
			max(0, x),
			max(0, x),
			max(0, x)
		};
		return;
	}
	int mid = (l + r) >> 1;
	if(i <= mid)
		upd(i, x, k << 1, l, mid);
	else
		upd(i, x, k << 1 | 1, mid + 1, r);
	T[k] = T[k << 1] + T[k << 1 | 1];
}
 
Node get(int ql, int qr, int k=1, int l=1, int r=n){
    if(l>r or r<ql or l>qr)return Node();
    if(ql<=l and r<=qr)
        return T[k];
    int mid=(l+r)>>1;
    return get(ql,qr,k<<1,l,mid)+get(ql,qr,k<<1|1,mid+1,r);
}
 
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> n >> q;
	for(int i = 1; i <= n; ++i)
		cin >> tab[i];
	build();
	while(q--) {
		int a, b;
		cin >> a >> b;
		cout << max(0ll, get(a,b).mx) << '\n';
	}
}
