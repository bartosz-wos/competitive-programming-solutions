#include <bits/stdc++.h>

using namespace std;

struct fenwick_tree{
    vector<int> bit;
    fenwick_tree(int n) : bit(n + 1, 0) {}

    void update(int i, int v){
        for(; i < (int)bit.size(); i += i & (-i)) bit[i] += v;
    }

    int query(int i){
        int sum = 0;
        for(; i > 0; i -= i & (-i)) sum += bit[i];
        return sum;
    }

    int walk(int x){
        int pos = 0;
        int L = 31 - __builtin_clz((int)bit.size());
        for(int i = L; i >= 0; --i){
            if(pos + (1 << i) < (int)bit.size() && x > bit[pos + (1 << i)]){
                pos += (1 << i);
                x -= bit[pos];
            }
        }
        return pos + 1;
    }
};

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);

    int N, M;
    cin >> N >> M;

    vector<int> A(N + M), B(N);
    for(int i = 0; i < N; ++i){
        cin >> B[i];
        --B[i];
        A[B[i]] = i;
    }

    for(int i = N; i < N + M; ++i){
        cin >> A[i];
    }

    vector<int> L(N, -1), R(N, -1);

    fenwick_tree ft(N);
    for(int i = 0; i < N; ++i){
        int cur = ft.query(A[i]);
        if(cur > 0){
            L[i] = B[ft.walk(cur) - 1];
        }

        if(cur < i){
            R[i] = B[ft.walk(cur + 1) - 1];
        }

        ft.update(A[i] + 1, +1);
        B[A[i]] = i;
    }

    function<bool(int, int)> isomorphic = [&](int j, int i){
        if(j == N) return false;
        if(L[j] != -1 && A[i - j + L[j]] >= A[i]) return false;
        if(R[j] != -1 && A[i - j + R[j]] <= A[i]) return false;
        return true;
    };

    vector<int> ans;
    vector<int> pi(N + M);
    for(int i = 1, j = 0; i < N + M; ++i){
        while(j > 0 && !isomorphic(j, i)) j = pi[j - 1];
        if(isomorphic(j, i)) ++j;

        if(j == N && i - 2 * N + 2 >= 1){
            ans.push_back(i - 2 * N + 2);
        }

        pi[i] = j;
    }

    cout << (int)ans.size() << '\n';
    for(int i : ans) cout << i << ' ';

    return 0;
}

