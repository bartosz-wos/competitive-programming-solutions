#include <bits/stdc++.h>
using namespace std;
const int NMAX = 101;
int N,M,ans,A[NMAX],aloc[2001],W[2001];
main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	set<int>m;
	cin >> N >> M;
	for (int i = 1; i <= N;++i) m.insert(i);
	for (int i = 1; i <= N;++i)
        cin >> A[i];
    for (int i = 1; i <= M;++i)
        cin >> W[i];
    queue<int>q;
    for (int i = 1; i <= 2 * M;++i) {
        int x; cin >> x;
        if (x > 0) {
            q.push(x);
        } else {
            m.insert(aloc[-x]);
        }
        while (m.size() && q.size()) {
            auto a = *m.begin();
            auto b = q.front();
            q.pop();
            m.erase(a);
            aloc[b] = a;
            ans += A[a] * W[b];
        }
    }
    cout << ans;
}

