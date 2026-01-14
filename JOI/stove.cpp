#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int main(){
    ll n, k;
    cin >> n >> k;
    k--;
    ll sm=1;
    priority_queue<ll>pq;
    ll y=0;
    for(ll i=0;i<n;++i){
    	ll x;
    	cin>>x;
    	if(i){
	    sm=sm+x-y;
    	    pq.push(x-y-1);
    	}
    	y=x;
    }
    for(ll i=0;i<min(k,n);++i){
        sm=sm-pq.top();
        pq.pop();
    }
    cout << sm;    	
}
