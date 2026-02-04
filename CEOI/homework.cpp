#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#define MASK(i) (1LL << (i))
#define GETBIT(mask, i) (((mask) >> (i)) & 1)
#define ALL(v) (v).begin(), (v).end()

ll max(ll a, ll b){return (a > b) ? a : b;}
ll min(ll a, ll b){return (a < b) ? a : b;}

ll gcd(ll a, ll b){return __gcd(a, b);}
ll LASTBIT(ll mask){return (mask) & (-mask);}
int pop_cnt(ll mask){return __builtin_popcountll(mask);}
int ctz(ll mask){return __builtin_ctzll(mask);}
int logOf(ll mask){return __lg(mask);}

mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
ll rngesus(ll l, ll r){return l + (ull) rng() % (r - l + 1);}

template <class T1, class T2>
    bool maximize(T1 &a, T2 b){
        if (a < b) {a = b; return true;}
        return false;
    }

template <class T1, class T2>
    bool minimize(T1 &a, T2 b){
        if (a > b) {a = b; return true;}
        return false;
    }

template <class T>
    void printArr(T& container, string separator = " ", string finish = "\n"){
        for(auto item: container) cout << item << separator;
        cout << finish;
    }


template <class T>
    void remove_dup(vector<T> &a){
        sort(ALL(a));
        a.resize(unique(ALL(a)) - a.begin());
    }

int pos = 0;
string s; 

array<int, 3> dfs(){
    if (s[pos] == 'm'){
        bool type = (s[pos+1] == 'a');
        pos += 3;

        pos++;
        array<int, 3> L = dfs();
        pos++;
        array<int, 3> R = dfs();
        pos++;

        if (type == false){
            return {{min(L[0], R[0]), L[1] + R[1] - 1, L[2] + R[2]}};
        }
        else{
            return {{L[0] + R[0], max(L[1] + R[2], R[1] + L[2]), L[2] + R[2]}};
        }
    }
    else{
        pos++;
        return {{1, 1, 1}};
    }
}

int main(void){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    clock_t start = clock();
    
    cin >> s;
    array<int, 3> ans = dfs();
    cout << ans[1] - ans[0] + 1 << "\n";

    cerr << "Time elapsed: " << clock() - start << "ms!\n";
    return 0;
}

