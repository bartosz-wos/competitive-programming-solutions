#include<bits/stdc++.h>
#include "tickets.h"
#define int long long
using namespace std;

int find_maximum(int32_t k, vector<vector<int32_t>> a){
    vector<pair<int, int>> reduce_option;
    int n = a.size(), m = a[0].size(), ans = 0;
    for(int i = 0; i < n; i++){
        for(int j = m-1; j >= m-k; j--) ans += a[i][j];
        for(int j = 0; j < k; j++) reduce_option.push_back(make_pair(a[i][j] + a[i][j+(m-k)], i));
    }
    vector<int> reduce(n), add(n);
    sort(reduce_option.begin(), reduce_option.end());
    for(int i = 0; i < n*k/2; i++){
        ans -= reduce_option[i].first;
        //cout<<"A"<<reduce_option[i].first<<endl;
        reduce[reduce_option[i].second]++;
    }
    for(int i = 0; i < n; i++) add[i] = k-reduce[i];
    vector<vector<int32_t>> s(n);
    for(int i = 0; i < n; i++){
        s[i].resize(m);
        for(int j = 0; j < m; j++) s[i][j] = -1;
    }
    //cout<<"hihi"<<endl;
    for(int it = k-1; it >= 0; it--){
        int reduce_demand = n/2;
        vector<bool> ok(n);
        for(int i = 0; i < n; i++){
            if(add[i] == 0){
                reduce[i]--; reduce_demand--;
                s[i][reduce[i]] = it;
                ok[i] = 1;
            }
            else if(reduce[i] == 0){
                s[i][m-add[i]] = it;
                add[i]--;
                ok[i] = 1;
            }
        }
        for(int i = 0; i < n; i++) if(ok[i] == 0){
            if(reduce_demand > 0 && reduce[i] > 0){
                reduce[i]--; reduce_demand--;
                s[i][reduce[i]] = it;
            }
            else{
                s[i][m-add[i]] = it;
                add[i]--;
            }
        }
    }
    allocate_tickets(s);
    return ans;
}
