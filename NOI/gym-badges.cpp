#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int nx=5e5+5;

ll n, x[nx], l[nx], sm;
vector<pair<ll, ll>> v;
priority_queue<ll> pq;

int main()
{
    cin.tie(NULL)->sync_with_stdio(false);
    cin>>n;
    for (int i=1; i<=n; i++) cin>>x[i];
    for (int i=1; i<=n; i++) cin>>l[i], v.push_back({x[i]+l[i], i});
    sort(v.begin(), v.end());
    for (auto [_, i]:v)
    {
        if (sm<=l[i]) sm+=x[i], pq.push(x[i]);
        else if (pq.top()>x[i]) sm+=x[i]-pq.top(), pq.pop(), pq.push(x[i]);
    }
    cout<<pq.size();
}
