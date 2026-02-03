#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
#define fastio ios::sync_with_stdio(false), cin.tie(0)
#define pb push_back
#define eb emplace_back
#define f first
#define s second
#define int long long
int t, pre;

bool qry(int x){
    cout<<"? "<<x<<endl;
    cin>>x;
    return x;
}
signed main(void){
    int n;
    cin>>n;
    vector<int> step;
    int l = 0, r = n;
    while(l + 1 < r){
        int m = (l + r) / 2;
        step.pb(m);
        l = m;
    }
    reverse(step.begin(), step.end());
    int pos = 1;
    for(int i = 0; i < step.size(); i++){
        pos += step[i] * (i % 2 ? -1 : 1);
    }
    qry(pos);
    l = 0, r = n;
    int sign = (step.size() % 2 ? -1 : 1);
    while(l + 1 < r){
        int m = (l + r) / 2;
        if(qry(pos += sign * m)) r = m;
        else l = m;
        sign *= -1;
    }
    cout<<"= "<<r<<endl;
}
