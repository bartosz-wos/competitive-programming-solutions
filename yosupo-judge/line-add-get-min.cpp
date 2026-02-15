#include "bits/stdc++.h"
using namespace std;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define int long long

const int BUF_SZ = 1 << 15;
inline namespace Input {
	char buf[BUF_SZ];int pos;int len;
	char next_char() {
	if (pos == len) {pos = 0;
	len = (int)fread(buf, 1, BUF_SZ, stdin);
	if (!len) { return EOF; }}
	return buf[pos++];}
	int read_int() {
	int x;char ch;int sgn = 1;
	while (!isdigit(ch = next_char())) {
	if (ch == '-') { sgn *= -1; }}
	x = ch - '0';
	while (isdigit(ch = next_char())) { x = x * 10 + (ch - '0'); }
	return x * sgn;}
}
inline namespace Output {
	char buf[BUF_SZ];int pos;
	void flush_out() {fwrite(buf, 1, pos, stdout);pos = 0;}
	void write_char(char c) {
	if (pos == BUF_SZ) { flush_out(); }
	buf[pos++] = c;}
	void write_int(int x) {
	static char num_buf[100];
	if (x < 0) {write_char('-');x *= -1;}
	int len = 0;
	for (; x >= 10; x /= 10) { num_buf[len++] = (char)('0' + (x % 10)); }
	write_char((char)('0' + x));
	while (len) { write_char(num_buf[--len]); }
	write_char('\n');}
	void init_output() { assert(atexit(flush_out) == 0); }
}

const int inf = 1e18;

namespace LICHAO {
	const int LCB = 7e6;
	int m[LCB],b[LCB],q[LCB];
	int l[LCB],r[LCB],npos = 1;
	void reset() {npos = 1;}
	int create() {
		b[npos] = inf;
		l[npos] = r[npos] = 0;
		return npos++;
	}
	void insert(int i, int cm, int cb, int id, int lo = -2e9, int hi = 2e9) {
		if (lo+1==hi) {
			if (cm*lo+cb < m[i]*lo+b[i]) {m[i] = cm, b[i] = cb, q[i] = id;}
			return;
		}
		int mid = (lo+hi)/2;
		if (cm*mid+cb < m[i]*mid+b[i]) {swap(cm,m[i]); swap(cb,b[i]); swap(id,q[i]);}
		if (cm==0 && cb==inf) return;
		if (cm*lo+cb < m[i]*lo+b[i]) {
			if (!l[i]) l[i] = create();
			insert(l[i],cm,cb,id,lo,mid);
		} else {
			if (!r[i]) r[i] = create();
			insert(r[i],cm,cb,id,mid,hi);
		}
	}
	array<int,2> query(int i, int x, int lo = -2e9, int hi = 2e9) {
		if (lo+1 == hi) {return {m[i]*x+b[i],q[i]};}
		int mid = (lo+hi)/2;
		array<int,2> res = {m[i]*x+b[i],q[i]};
		if (x < mid) {
			if (l[i]) res = min(res, query(l[i],x,lo,mid));
		} else {
			if (r[i]) res = min(res, query(r[i],x,mid,hi));
		}
		return res;
	}
}

signed main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	init_output();
	
	int n = read_int();
	int q = read_int();
		
	int rt = LICHAO::create();
	
	for (int i=0; i<n; i++) {
		int a = read_int();
		int b = read_int();
		LICHAO::insert(rt,a,b,0);
	}
	for (int i=0; i<q; i++) {
		int t = read_int();
		if (t) {
			int p = read_int();
			write_int(LICHAO::query(rt,p)[0]);
		} else {
			int a = read_int();
			int b = read_int();
			LICHAO::insert(rt,a,b,0);
		}
	}
}
