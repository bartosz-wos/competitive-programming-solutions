#include<bits/stdc++.h>
using namespace std;
template <class T, T (*op)(T, T), T(*e)()>
struct segtree {
	vector<T> d;
	int  n;
	T a, b;
	segtree(int n = 0) : segtree(vector<T> (n, e())) {}
	segtree(const vector<T>& v) : n((int)v.size()) { 
		d.assign(n * 2, e());
		for (int i = 0; i < n; ++i) d[n + i] = v[i];
		for (int i = n - 1; i >= 1; --i) d[i] = op(d[i << 1], d[(i << 1) + 1]);
	}
	void set(int p, T x) { 
		assert(0 <= p and p < n); 
		d[p += n] = x;
		for (p >>= 1; p; p >>= 1) d[p] = op(d[p << 1], d[(p << 1) + 1]); 
	}
	T operator[](int p) { 
		assert(p >= 0 and p < n); 
		return d[p + n]; 
	}
	T operator()(int l, int r) {
		assert(0 <= l and r <= n and l <= r);
		a = e(), b = e();
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) { if(l & 1) a = op(a, d[l++]); if(r & 1) b = op(d[--r], b); }
		return op(a, b);
	}
	T all_prod() { return d[1]; }
};

constexpr long long mod = 998244353;
using S = pair<long long, long long>;
S op(S a, S b) { return S{(a.first * b.first) % mod, (b.first * a.second +  b.second) % mod}; }
S e() { return S{1, 0}; }
int main()
{
   ios_base::sync_with_stdio(false);
   cin.tie(nullptr);
   int n, q;
   cin >> n >> q;
   vector<S> a(n);
   for (int i = 0; i < n; ++i) cin >> a[i].first >> a[i].second;
   segtree<S, op, e> seg(a);
   while(q--)
   {
      int t;
      cin >> t;
      if (t == 0)
      {
         int p;
         long long c, d;
         cin >> p >> c >> d;
         seg.set(p, S{c, d});
      }
      else 
      {
         int l, r;
         long long x;
         cin >> l >> r >> x;
         S res = seg(l, r);
         cout << (res.first * x + res.second) % mod << '\n';
      }
   }
}
