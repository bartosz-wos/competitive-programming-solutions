#include <iostream>  //cin , cout
#include <fstream>   //fin, fout
#include <stdio.h>   // scanf , pringf
#include <cstdio>
#include <algorithm> // sort , stuff
#include <stack>     // stacks
#include <queue>     // queues
#include <map>
#include <string>
#include <string.h>
#include <set>
 
using namespace std;
 
typedef pair<int, int>          pii;
typedef vector<int>             vi;     /// adjlist without weight
typedef vector<pii>             vii;    /// adjlist with weight
typedef vector<pair<int,pii>>   vpip;   /// edge with weight
typedef long long               ll;
 
#define mp  make_pair
#define ff  first
#define ss  second
#define pb  push_back
#define sz(x)   (int)(x).size()
 
const int MOD = 1e9+7;  // 998244353;
const int MX  = 2e5+5;   //
const ll  INF = 1e18;    //
 
#define MAXV 300007
#define MAXE 100007
 
bool debug;
 
int N;
ll H;
 
/// left and right side queue for the strictly increase/decrease array, with range of H.
priority_queue<ll> lq;
priority_queue<ll, vector<ll>, greater<ll>> rq;
 
int main() {
    debug = false;
    ios_base::sync_with_stdio(false); cin.tie(0);
 
    cin >> N >> H;
 
    ll ans = 0LL;
    for(int i=0;i<N;i++) {
        ll a; cin >> a;
 
        if(i==0) {
            lq.push(a); rq.push(a);
            continue;
        }
 
        ll range = (ll)i * (ll)H;
        if(a + range < lq.top()) {
            lq.push(a + range);             /// max coverage
            ans += lq.top() - (a + range);  /// touch historical set by H
            lq.push(a + range);             /// compensate
            rq.push(lq.top() - range * 2LL);     /// also a possible option for right side
            lq.pop();
        } else if ( a - range > rq.top()) {
            rq.push(a - range);
            ans += (a - range) - rq.top();
            rq.push(a - range);
            lq.push(rq.top() + range *2LL);
            rq.pop();
        } else {
            lq.push(a + range);
            rq.push(a - range);
        }
 
    }
 
    cout << ans << endl;
 
    if(debug) cout << endl << "EOL" << endl;
 
}
