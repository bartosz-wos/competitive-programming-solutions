#include <bits/stdc++.h>
using namespace std;

#define int long long

const int NM = 2000, LIM = 100, inf = 1e9+7;

namespace subtask4{
	int N, A, B, Y[LIM+5], pref[LIM+5];
	bool dp[LIM+5][LIM+5];
	void solve(int _N, int _A, int _B){
		N = _N, A = _A, B = _B;
		for (int i = 1; i <= N; i++){
			cin >> Y[i];
			pref[i] = pref[i-1]+Y[i];
		}
		int msk = 0;
		for (int t = 36; t >= 0; t--){
			memset(dp, 0, sizeof(dp));
			dp[0][0] = 1;
			for (int i = 0; i < N; i++)
				for (int k = i+1; k <= N; k++){
					if ((pref[k]-pref[i])&(msk+(1LL<<t))) continue;
					for (int j = 0; j <= i; j++) dp[k][j+1] |= dp[i][j];
			}
			for (int i = A; i <= B; i++)
				if (dp[N][i]){
					msk += 1LL<<t;
					break;
				}
		}
		cout << (1LL<<37)-1-msk;
	}
}

namespace subtask5{
	int N, A, B, Y[NM+5], pref[NM+5];
	int dp[NM+5];
	void solve(int _N, int _A, int _B){
		N = _N, A = _A, B = _B;
		for (int i = 1; i <= N; i++){
			cin >> Y[i];
			pref[i] = pref[i-1]+Y[i];
		}
		int msk = 0;
		for (int t = 40; t >= 0; t--){
			dp[0] = 0;
			for (int i = 1; i <= N; i++) dp[i] = +inf;
			for (int i = 0; i < N; i++){
				if (dp[i] == +inf) continue;
				for (int k = i+1; k <= N; k++){
					if ((pref[k]-pref[i])&(msk+(1LL<<t))) continue;
					dp[k] = min(dp[k], dp[i]+1);
				}
			}
			if (dp[N] <= B) msk += 1LL<<t;
		}
		cout << (1LL<<41)-1-msk;
	}
}

int N, A, B;

signed main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	cin >> N >> A >> B;
	if (N <= 100) subtask4::solve(N, A, B);
	else subtask5::solve(N, A, B);
	return 0;
}
