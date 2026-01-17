#include<bits/stdc++.h>
#include"secret.h"
using namespace std;
using ll=long long;
using pi=pair<int,int>;
 
#define pb push_back
#define fi first
#define se second
 
constexpr int N=1e3+5;
constexpr int lg=11;
int res[lg][N];
int mask[N];
int a[N];
 
void build(int l, int r, int pw){
		if(l==r)return;
		int m=(l+r)>>1;
		res[pw][m]=a[m];
		for(int i=m-1;i>=l;--i)
				res[pw][i]=Secret(a[i],res[pw][i+1]);
		res[pw][m+1]=a[m+1];
		for(int i=m+2;i<=r;++i)
				res[pw][i]=Secret(res[pw][i-1],a[i]);
		for(int i=m+1;i<=r;++i)
				mask[i]^=1<<pw;
		build(l,m,pw+1);
		build(m+1,r,pw+1);
}
 
void Init(int n, int t[]){
		for(int i=0;i<n;++i)
				a[i]=t[i];
		build(0,n-1,0);
}
 
int Query(int l, int r){
		if(l==r)return a[l];
		int x=__builtin_ctz(mask[l]^mask[r]);
		return Secret(res[x][l],res[x][r]);
}
