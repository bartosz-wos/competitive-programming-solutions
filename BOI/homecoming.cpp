#include <bits/stdc++.h>
#include "homecoming.h"
 
using namespace std;

long long first_forced(int n, int k, int *a, int *b){
    long long mx, cur, cost, nxtcost;
    
    cost = accumulate(b, b + k, 0ll);
    
    mx = cur = a[0] - cost;
    
    for(int i = 1; i < n; i++){
        cost -= b[i - 1];
        nxtcost = i + k - 1 < n ? b[i + k - 1] : 0;
        
        cur = max(cur + a[i] - nxtcost, mx + a[i] - (cost + nxtcost));
        
        mx = max(mx, cur);
        cost += nxtcost;
    }
    
    return mx;
}

long long first_not_forced(int n, int k, int *a, int *b){
    long long mx, cur, cost, nxtcost;
    
    cost = accumulate(b, b + k, 0ll);
    
    mx = max(0ll, a[0] - cost);
    cur = a[0] - cost;
    
    for(int i = 1; i < n; i++){
        cost -= b[i - 1];
        nxtcost = i + k - 1 < n ? b[i + k - 1] : b[i + k - 1 - n];
        
        cur = max(cur + a[i] - nxtcost, mx + a[i] - (cost + nxtcost));
        
        mx = max(mx, cur);
        cost += nxtcost;
    }
    
    return mx;
}
 
long long solve(int n, int k, int *a, int *b){
	return max(first_forced(n, k, a, b), first_not_forced(n, k, a, b));
}
