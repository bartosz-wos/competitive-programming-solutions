#include<bits/stdc++.h>
using namespace std;

std::vector<int> ask(int i);

const int MAXN = 2e5;

int Ans;

vector<int> A[MAXN];

int Max;

bool answered[MAXN];
bool Found;

vector<int> ASK(int x) {
    if(!answered[x]) {
        A[x] = ask(x);
        if(A[x][0] + A[x][1] == 0) {
            Ans = x;
            Found = true;
        }
        answered[x] = true;
    }
    //cerr << x << " " << A[x][0] << " " << A[x][1] << "\n";
    return A[x];
}

int sumA(int x) {
    ASK(x);
    return A[x][0] + A[x][1];
}

void solve(int l, int r) {
    if(l >= r || Found) {
        return;
    }
    int mid = (l + r) / 2, ml = mid, mr = mid;
    bool goLeft = true, goRight = true;
    while(sumA(ml) < Max) {
        if(A[ml][0] == 0) {
            goLeft = false;
            break;
        }
        ml--;
    }
    while(sumA(mr) < Max) {
        if(A[mr][1] == 0) {
            goRight = false;
            break;
        }
        mr++;
    }
    if(goLeft && A[ml][0] - A[l][0] > 0) solve(l, ml);
    if(goRight && A[r][0] - A[mr][0] > 0) solve(mr, r);
}

int find_best(int n) {
    for(int i = 0; i < MAXN; i++) {
        A[i].resize(2);
    }
    for(int i = 0; i < min(500, n); i++) {
        Max = max(Max, sumA(i));
        if(Max > 50) break;
    }
    int l = 0, r = n - 1;
    while(sumA(l) < Max) l++;
    while(sumA(r) < Max) r--;
    solve(l, r);
    return Ans;
}

