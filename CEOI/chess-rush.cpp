#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
const ll MOD = 1'000'000'007;

int R, C, Q;
ll inv[1010];

typedef vector<vector<ll>> matrix;
matrix A, E;
matrix prod(matrix A) {
    matrix B = vector<vector<ll>> (C+1, vector<ll>(C+1, 0));
    for (int i = 1; i <= C; i++) {
        for (int j = 1; j <= C; j++) {
            for (int k = -1; k <= 1; k++) {
                if (j+k < 1 || j+k > C) continue;
                B[i][j] += A[i][j+k];
                B[i][j] %= MOD;
            }
        }
    }
    return B;
}
matrix square(matrix A) {
    matrix B = vector<vector<ll>> (C+1, vector<ll>(C+1, 0));
    for (int i = 1; i <= C; i++) {
        for (int k = 1; k <= C; k++) {
            B[i][1] += A[i][k] * A[k][1];
            B[i][1] %= MOD;
        }
        B[1][i] = B[i][1];
    }
    for (int i = 2; i <= C; i++) {
        for (int j = 2; j <= C; j++) {
            if (i+j-1 <= C) {
                B[i][j] = B[i-1][j-1] + B[1][i+j-1];
                B[i][j] %= MOD;
            }
        }
    }
    for (int i = C; i >= 2; i--) {
        for (int j = C; j >= 2; j--) {
            if (i+j-1 >= C) B[i][j] = B[C+1-i][C+1-j];
        }
    }
    return B;
}
matrix myPow(int x) {
    if (x == 0) return E;
    matrix B = myPow(x/2);
    B = square(B);
    if (x % 2 == 0) return B;
    else return prod(B);
}
int myPow(int a, int x) {
    if (x == 0) return 1;
    ll b = myPow(a, x/2);
    b = b*b%MOD;
    if (x % 2 == 0) return b;
    else return b*a%MOD;
}
void init() {
    A = vector<vector<ll>> (C+1, vector<ll>(C+1, 0));
    E = vector<vector<ll>> (C+1, vector<ll>(C+1, 0));
    for (int i = 1; i <= C; i++) {
        for (int j = 1; j <= C; j++) {
            if (abs(i-j) <= 1) A[i][j] = 1;
            if (i == j) E[i][j] = 1;
        }
    }
    A = myPow(R-1);
    for (int i = 1; i <= C; i++) {
        inv[i] = myPow(i, MOD-2);
    }
}

pll PAWN(int a, int b) {
    if (a == b) return {R-1, 1};
    return {0, 0};
}
pll ROOK(int a, int b) {
    if (a == b) return {1, 1};
    return {2, 2};
}
pll QUEEN(int a, int b) {
    if (a == b || abs(a-b) == R-1) return {1, 1};
    vector<pll> st, ed;
    for (int j = 1; j <= C; j++) if (j != a) st.push_back({1, j});
    for (int i = 2; ; i++) {
        int j = a + i-1;
        if (j > C) break;
        st.push_back({i, j});
    }
    for (int i = 2; ; i++) {
        int j = a + 1-i;
        if (j < 1) break;
        st.push_back({i, j});
    }
    for (int j = 1; j <= C; j++) if (j != b) ed.push_back({R, j});
    for (int i = 2; ; i++) {
        int j = b + i-1;
        if (j > C) break;
        ed.push_back({R-i+1, j});
    }
    for (int i = 2; ; i++) {
        int j = b + 1-i;
        if (j < 1) break;
        ed.push_back({R-i+1, j});
    }

    int cnt = 0;
    for (auto &[x, y] : st) if (y == b) cnt++;
    for (auto &[x, y] : ed) if (y == a) cnt++;
    cnt += st.size() + ed.size();
    st.insert(st.end(), ed.begin(), ed.end());
    sort(st.begin(), st.end());
    st.erase(unique(st.begin(), st.end()), st.end());
    cnt -= st.size();
    return {2, cnt};
}

pll solve(int a, int b) {
    ll t1 = ceil((double)(R-a-b+1)/(2*C-2));
    ll t2 = ceil((double)(R-a-1+b)/(2*C-2));
    pll ans;
    if (t1 < t2) ans = {2*t1+2, 2*t1*(C-1) - (R-a-b+1)};
    else ans = {2*t2+1, 2*t2*(C-1) - (R-a-1+b)};
    ll cnt = 1;
    ans.second /= 2;
    for (int i = 1; i <= ans.second; i++) {
        cnt *= (ans.first-2+i);
        cnt %= MOD;
        cnt *= inv[i];
        cnt %= MOD;
    }
    return {ans.first, cnt};
}
pll BISHOP(int a, int b) {
    if ((1+a)%2 != (R+b)%2) return {0, 0};
    pll A = solve(a, b), B = solve(C+1-a, C+1-b);
    if (A.first == B.first) return {A.first, (A.second + B.second) % MOD};
    else if (A.first < B.first) return A;
    else return B;
}

pll KING(int a, int b) {
    return {R-1, A[a][b]};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie();

    cin >> R >> C >> Q;

    init();

    while (Q--) {
        char T; int a, b; pll res;
        cin >> T >> a >> b;
        if (T == 'P') res = PAWN(a, b);
        else if (T == 'R') res = ROOK(a, b);
        else if (T == 'Q') res = QUEEN(a, b);
        else if (T == 'B') res = BISHOP(a, b);
        else if (T == 'K') res = KING(a, b);
        cout << res.first << " " << res.second << "\n";
    }

    return 0;
}
