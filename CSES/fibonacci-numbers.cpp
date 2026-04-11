#include <iostream>
using namespace std;
constexpr int MOD = 1000000007;
using ull = unsigned long long;
 
ull M[2][2]{ {1, 1}, {1, 0} };
 
void multiply(ull F[2][2], ull M[2][2]) {
	ull x = ( ( F[0][0] * M[0][0] ) % MOD + ( F[0][1] * M[1][0] ) % MOD ) % MOD;
	ull y = ( ( F[0][0] * M[0][1] ) % MOD + ( F[0][1] * M[1][1] ) % MOD ) % MOD;
	ull w = ( ( F[1][0] * M[0][0] ) % MOD + ( F[1][1] * M[1][0] ) % MOD ) % MOD;
	ull z = ( ( F[1][0] * M[0][1] ) % MOD + ( F[1][1] * M[1][1] ) % MOD ) % MOD;
 
	F[0][0] = x;
	F[0][1] = y;
	F[1][0] = w;
	F[1][1] = z;
}
 
void matrixpow(ull F[2][2], ull n) {
	if (n == 0 || n == 1)
		return;
	matrixpow(F, n >> 1);
	multiply(F, F);
 
	if (n & 1)
		multiply(F, M);
}
 
ull get_fib(ull n) {
	if (n == 0)
		return 0;
	ull F[2][2]{ {1, 1}, {1, 0} };
	matrixpow(F, n - 1);
 
	return F[0][0];
}
 
int main() {
	ull n;
	cin >> n;
 
	cout << get_fib(n);
}
