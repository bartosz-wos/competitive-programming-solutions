#include <bits/stdc++.h>
 
using namespace std;
 
#define                  fi  first
#define                  se  second
#define                left  ___left
#define               right  ___right
#define                TIME  (1.0 * clock() / CLOCKS_PER_SEC)
#define             MASK(i)  (1LL << (i))
#define           BIT(x, i)  ((x) >> (i) & 1)
#define  __builtin_popcount  __builtin_popcountll
#define              ALL(v)  (v).begin(), (v).end()
#define           REP(i, n)  for (int i = 0, _n = (n); i < _n; ++i)
#define          REPD(i, n)  for (int i = (n); i--; )
#define        FOR(i, a, b)  for (int i = (a), _b = (b); i < _b; ++i) 
#define       FORD(i, b, a)  for (int i = (b), _a = (a); --i >= _a; ) 
#define       FORE(i, a, b)  for (int i = (a), _b = (b); i <= _b; ++i) 
#define      FORDE(i, b, a)  for (int i = (b), _a = (a); i >= _a; --i) 
#define        scan_op(...)  istream & operator >> (istream &in, __VA_ARGS__ &u)
#define       print_op(...)  ostream & operator << (ostream &out, const __VA_ARGS__ &u)
#ifdef LOCAL
    #include "debug.h"
#else
    #define file(name) if (fopen(name".inp", "r")) { freopen(name".inp", "r", stdin); freopen(name".out", "w", stdout); }
    #define DB(...) 23
    #define db(...) 23
    #define debug(...) 23
#endif
 
template <class U, class V> scan_op(pair <U, V>)  { return in >> u.first >> u.second; }
template <class T> scan_op(vector <T>)  { for (size_t i = 0; i < u.size(); ++i) in >> u[i]; return in; }
template <class U, class V> print_op(pair <U, V>)  { return out << '(' << u.first << ", " << u.second << ')'; }
template <size_t i, class T> ostream & print_tuple_utils(ostream &out, const T &tup) { if constexpr(i == tuple_size<T>::value) return out << ")";  else return print_tuple_utils<i + 1, T>(out << (i ? ", " : "(") << get<i>(tup), tup); }
template <class ...U> print_op(tuple<U...>) { return print_tuple_utils<0, tuple<U...>>(out, u); }
template <class Con, class = decltype(begin(declval<Con>()))> typename enable_if <!is_same<Con, string>::value, ostream&>::type operator << (ostream &out, const Con &con) { out << '{'; for (__typeof(con.begin()) it = con.begin(); it != con.end(); ++it) out << (it == con.begin() ? "" : ", ") << *it; return out << '}'; }
 
const int MOD = 1e9 + 7;
 
namespace Mod {
 
    inline void fasterLLDivMod(unsigned long long x, unsigned y, unsigned &out_d, unsigned &out_m) {
        unsigned xh = (unsigned)(x >> 32), xl = (unsigned)x, d, m;
    #ifdef __GNUC__
        asm(
            "divl %4 \n\t"
            : "=a" (d), "=d" (m)
            : "d" (xh), "a" (xl), "r" (y)
        );
    #else
        __asm {
            mov edx, dword ptr[xh];
            mov eax, dword ptr[xl];
            div dword ptr[y];
            mov dword ptr[d], eax;
            mov dword ptr[m], edx;
        };
    #endif
        out_d = d; out_m = m;
    }
 
    template <class T> T invGeneral(T a, T b) {
        a %= b;
        if (!a) return b == 1 ? 0 : -1;
        T x = invGeneral(b, a);
        return x == -1 ? -1 : ((1 - 1LL * b * x) / a + b) % b;
    }
 
    template <int MOD>
    struct ModInt {
        
        unsigned int val;
 
        ModInt(void): val(0) {}
        ModInt(const long long &x) { *this = x; }
 
        ModInt & normalize(const unsigned int &v) {
            val = v >= MOD ? v - MOD : v;
            return *this;
        }
 
        bool operator ! (void) { return !val; }
 
        ModInt & operator = (const ModInt &x) { val = x.val; return *this; }
        ModInt & operator = (const long long &x) { return normalize(x % MOD + MOD); }
 
        ModInt operator - (void) { return ModInt(MOD - val); }
 
        ModInt & operator += (const ModInt &other) { return normalize(val + other.val); }
        ModInt & operator -= (const ModInt &other) { return normalize(val + MOD - other.val); }
        ModInt & operator /= (const ModInt &other) { return *this *= other.inv(); }
 
        ModInt & operator *= (const ModInt &other) {
            unsigned dummy;
            fasterLLDivMod((unsigned long long) val * other.val, MOD, dummy, val);
            return *this;
        }
 
        ModInt operator + (const ModInt &other) const { return ModInt(*this) += other; }
        ModInt operator - (const ModInt &other) const { return ModInt(*this) -= other; }
        ModInt operator * (const ModInt &other) const { return ModInt(*this) *= other; }
        ModInt operator / (const ModInt &other) const { return ModInt(*this) /= other; }
 
        ModInt pow(long long n) const {
            assert(n >= 0);
            ModInt res = 1, a = *this;
            for (; n; n >>= 1, a *= a) if (n & 1) res *= a;
            return res;
        }
 
        ModInt inv(void) const {
            int i = invGeneral((int) val, MOD);
            assert(~i);
            return i;
        }
 
        ModInt & operator ++ (void) { return *this += 1; }
        ModInt & operator -- (void) { return *this -= 1; }
        ModInt operator ++ (int) { ModInt old = *this; operator ++(); return old; }
        ModInt operator -- (int) { ModInt old = *this; operator --(); return old; }
 
        friend ModInt operator + (const long long &x, const ModInt &y) { return ModInt(x) + y; }
        friend ModInt operator - (const long long &x, const ModInt &y) { return ModInt(x) - y; }
        friend ModInt operator * (const long long &x, const ModInt &y) { return ModInt(x) * y; }
        friend ModInt operator / (const long long &x, const ModInt &y) { return ModInt(x) / y; }
        friend ostream & operator << (ostream &out, const ModInt &x) { return out << x.val; }
        friend istream & operator >> (istream &in, ModInt &x) { long long a; in >> a; x = a; return in; }
 
        bool operator < (const ModInt &other) const { return val < other.val; }
        bool operator > (const ModInt &other) const { return val > other.val; }
        bool operator <= (const ModInt &other) const { return val <= other.val; }
        bool operator >= (const ModInt &other) const { return val >= other.val; }
        bool operator == (const ModInt &other) const { return val == other.val; }
        bool operator != (const ModInt &other) const { return val != other.val; }
        explicit operator bool(void) const { return val; }
        explicit operator int(void) const { return val; }
 
    };  
 
    using Modular = ModInt <MOD>;
 
}
 
using namespace Mod;
 
// end of template
 
const int MAX = 5e5 + 5;
 
int N, M, L[MAX], R[MAX];
Modular dp[MAX][26], pref[MAX][27];
vector <int> add[MAX][2], rem[MAX][2];
bool used[MAX];
 
void init(void) {
	cin >> N >> M;
	REP(i, M) {
		cin >> L[i] >> R[i];
		if (L[i] < R[i]) {
			add[L[i]][0].push_back(i);
			rem[R[i]][0].push_back(i);
		} else {
            swap(L[i], R[i]);
			add[L[i]][1].push_back(i);
			rem[R[i]][1].push_back(i);
		}
	}
}
 
void process(void) {
	stack <int> st[2];
	FORE(i, 1, N) {
		REP(j, 2) while (!st[j].empty() && used[st[j].top()]) st[j].pop();
		int p0 = st[0].empty() ? 0 : L[st[0].top()];
		int p1 = st[1].empty() ? 0 : L[st[1].top()];
		REP(j, 26) {
			dp[i][j] = i == 1;
			dp[i][j] += (pref[i - 1][26] - pref[i - 1][j + 1] + pref[i - 1][j]) - (pref[max(p0, p1)][26] - pref[max(p0, p1)][j + 1] + pref[max(p0, p1)][j]);
			if (p0 < p1) dp[i][j] += pref[p1][j] - pref[p0][j];
            else if (p1 < p0) dp[i][j] += (pref[p0][26] - pref[p0][j + 1]) - (pref[p1][26] - pref[p1][j + 1]);
			pref[i][j + 1] = pref[i][j] + dp[i][j];
		}
        REP(j, 26) pref[i][j + 1] += pref[i - 1][j + 1];
		REP(j, 2) {
			for (int k: add[i][j]) st[j].push(k);
			for (int k: rem[i][j]) used[k] = true;
		}
	}
	cout << pref[N][26] << '\n';
}
 
int main(void) {
	ios_base::sync_with_stdio(false); cin.tie(nullptr); // cout.tie(nullptr);
	file("misspelling");
	init();
	process();
	cerr << "Time elapsed: " << TIME << " s.\n";
	return 0;
}
