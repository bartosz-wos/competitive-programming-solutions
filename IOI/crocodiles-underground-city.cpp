#include "crocodile.h"
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define vi vector<int>
#define pii pair<int,int>
#define ff first
#define ss second
const int inf = 1e9;
int32_t travel_plan(int32_t N, int32_t M, int32_t R[][2], int32_t L[], int32_t K, int32_t P[])
{
  vector<pii> edges[N];
  for (int i=0;i<M;i++) {
    edges[R[i][0]].push_back({R[i][1],L[i]});
    edges[R[i][1]].push_back({R[i][0],L[i]});
  }
  vector<pii> dist(N,pii{inf,inf});
  priority_queue<pii,vector<pii>,greater<pii>> pq;
  for (int i = 0;i<K;i++) {
    dist[P[i]] = {0,0};
    pq.push({0,P[i]});
  }

  while (!pq.empty()) {
    pii f = pq.top();
    pq.pop();
    if (dist[f.ss].ss < f.ff) continue;
    for (auto it : edges[f.ss]) {
      if (f.ff+it.ss < dist[it.ff].ff) {
        if (dist[it.ff].ff < dist[it.ff].ss) pq.push({dist[it.ff].ff,it.ff});
        dist[it.ff].ss = dist[it.ff].ff;
        dist[it.ff].ff = f.ff+it.ss;
      }
      else if (f.ff+it.ss < dist[it.ff].ss) {
        dist[it.ff].ss = f.ff+it.ss;
        pq.push({dist[it.ff].ss,it.ff});
      }
    }
  }
  return dist[0].ss;
}
