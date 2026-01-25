#include <bits/stdc++.h>
#define ll long long
#include "shoes.h"
using namespace std;
const int MAXN = 2e5+5;
int N;
int bit[MAXN];
queue<int> lastl[MAXN],lastr[MAXN];
void upd(int pos, int val){
    for(;pos <= N;pos += (pos&(-pos))){
        bit[pos] += val;
    }
}
int query(int pos){
    int ret = 0;
    for(;pos >= 1;pos -= (pos&(-pos))){
        ret += bit[pos];
    }
    return ret;
}
ll count_swaps(vector<int> S){
    N = S.size();
    ll ans = 0;
    for(int i = 0;i<N;++i){
        if(S[i] < 0){
            S[i] *= (-1);
            if(lastr[S[i]].size()){
                int j = lastr[S[i]].front(); lastr[S[i]].pop();
                ans += i-j-query(j)+1;
                upd(j,1); upd(i+2,-1);
            }
            else{
                lastl[S[i]].push(i+1);
            }
        }
        else{
            if(lastl[S[i]].size()){
                int j = lastl[S[i]].front(); lastl[S[i]].pop();
                ans += i-j-query(j);
                upd(j,1); upd(i+2,-1);
            }
            else{
                lastr[S[i]].push(i+1);
            }
        }
    }
    return ans;
}
