#include <stdio.h>

#define N	1000000
#define MD	1000000007

int main() {
	static int aa[N], ff[N + 1], dp[N + 1];
	int n, m, i, j;

	scanf("%d%d", &m, &n);
	for (i = 0; i < n; i++)
		scanf("%d", &aa[i]);
	ff[0] = -1, ff[1] = 0;
	for (i = -1, j = 0; j < n; i++, j++) {
		while (i >= 0 && aa[i] != aa[j])
			i = ff[i];
		ff[j + 1] = i + 1;
		dp[j + 1] = j == 0 ? m : ((long long) (dp[j] - dp[ff[j]] + MD) * m + dp[i + 1]) % MD;
		printf("%d\n", dp[j + 1]);
	}
	return 0;
}
