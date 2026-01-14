#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int MAXN = 1e5 + 7;
constexpr ll oo = 2e18;
ll total;
ll pref[MAXN];
vector<pair<ll, ll>> T;
priority_queue<ll> lefts, rights;
ll sumL, sumR;
int n, k, D;
     
bool cmp(pair<ll, ll> a, pair<ll, ll> b){
	return a.first + a.second < b.first + b.second;
}
     
void medianAdd(ll x){
	ll median = (lefts.size()? lefts.top(): oo);
    if(x <= median){
		lefts.push(x);
    	sumL += x;
    } 
    else{
    	rights.push(-x);
    	sumR += x;
    }
    	
    if(lefts.size() < rights.size()){
    	ll nxt = -(rights.top());
    	rights.pop();
    	sumR -= nxt;
    	lefts.push(nxt);
    	sumL += nxt;
    }
    if(rights.size() + 1 < lefts.size()){
    	ll nxt = lefts.top();
    	lefts.pop();
    	sumL -= nxt;
    	rights.push(-nxt);
    	sumR += nxt;
    }
}
     
void queueclear(){
	while(lefts.size()) lefts.pop();
	while(rights.size()) rights.pop();
}
     
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> k >> n;
	for(int i = 1; i <= n; i++){
		char x, y;
		ll a, b;
		cin >> x >> a >> y >> b;
    	if(b < a) swap(a, b);
    	
    	if(x != y) T.push_back({a, b});
    	else total += (b-a);
    }
    	
    sort(T.begin(), T.end(), cmp);
    D = T.size();
    total += D;
    	
    for(int i = 1; i <= D; i++){
    	medianAdd(T[i-1].first);
    	medianAdd(T[i-1].second);
    	pref[i] = abs(sumL - sumR);
    }
    
    ll best = pref[D];
    
    if(k == 2){
    	sumL = sumR = 0;
    	queueclear();
    	for(int i = D; i > 0; i--){
    		medianAdd(T[i-1].first);
    		medianAdd(T[i-1].second);
    		best = min(best, pref[i-1] + abs(sumL-sumR));
    	}
    }
    
    cout << total + best << "\n";
}
