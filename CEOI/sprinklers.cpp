#include <iostream>
#include <algorithm>

using namespace std;
const int N = 2e5;
int a[N], b[N], Mx[N], Par[N], type[N], dir[N], n, m;

void update(int i, int j, int val, int tp){
	if (Mx[j] >= val)
		return;
	Mx[j] = val;
	Par[j] = i;
	type[j] = tp;
}

bool check(int K, bool print = 0){
	for (int i=1;i<=n + 1;i++)
		Mx[i] = 1;

	for (int i=1;i<=n;i++){
		update(i-1, i, Mx[i-1], 1);

		if (Mx[i] < m + 1 and a[i] - K <= b[Mx[i]]){
			int u = upper_bound(b, b + m + 1, a[i]) - b;
			update(i, i + 1, u, 1);
		}

		if (Mx[i] < m + 1 and b[Mx[i]] >= a[i]){
			int u = upper_bound(b, b + m + 1, a[i] + K) - b;
			update(i, i + 1, u, 2);
		}

		if (Mx[i] < m + 1 and i < n and a[i + 1] - K <= b[Mx[i]]){
			int u = upper_bound(b, b + m + 1, a[i] + K) - b;
			update(i, i + 2, u, 2);
		}
	}
	update(n, n + 1, Mx[n], 1);


	if (print){
		int nn = n + 1;
		while (nn){
			if (type[nn] > 1)
				dir[Par[nn]] = 1;
			nn = Par[nn];
		}
		if (K < 0 or K > 1e9)
			cout<<1 / 0;
		cout<<K<<'\n';
		for (int i=1;i<=n;i++)
			cout<<(dir[i] ? 'R' : 'L');
		cout<<'\n';
		exit(0);
	}

	return Mx[n + 1] == m + 1;
}

int main(){
	cin>>n>>m;

	for (int i=1;i<=n;i++)
		cin>>a[i];
	
	for (int i=1;i<=m;i++)
		cin>>b[i];

	if (n == 1 and a[1] > b[1] and a[1] < b[m])
		return cout<<"-1\n", 0;

	int l = -1, r = 1e9;

	while (l + 1 < r){
		int mid = (l + r) / 2;
		if (check(mid))
			r = mid;
		else
			l = mid;
	}
	check(r, 1);
}
