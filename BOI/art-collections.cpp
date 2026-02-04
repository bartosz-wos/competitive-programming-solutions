#include "art.h"
#include <bits/stdc++.h>
using namespace std;

void solve(int N) {
    vector<int> num;
    vector<int> proc;
    vector<int> ans;
    vector<int> inv;

    for(int i = 0; i < N; i++){
        proc.push_back(i + 1);
        ans.push_back(4);
    }

    for(int i = 1; i <= N; i++){
        num.push_back(publish(proc));

        for(int i = 0; i < N - 1; i++){
            proc[i] = proc[i + 1];
        }
        proc[N - 1] = i;
    }

    for(int i = 0; i < N; i++){
        int calc = num[(i + 1) % N] - num[i];

        calc -= N - 1;
        calc = (-calc) / 2;

        ans[calc] = i + 1;
    }

    answer(ans);


}

