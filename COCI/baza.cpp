#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for(int i=0;i<n;i++)
#define rng(i,c,n) for(int i=c;i<n;i++)
#define per(i,n) for(int i=n-1;i>=0;i--)
#define fi first
#define se second
#define pb push_back
#define sz(a) (int)a.size()
#define vec(...) vector<__VA_ARGS__>
#define _3PGDklf ios::sync_with_stdio(0),cin.tie(0)
typedef long long ll;
using pii=pair<int,int>;
using vi=vector<int>;
void print(){cout<<'\n';}
template<class h,class...t>
void print(const h&v,const t&...u){cout<<v<<' ',print(u...);}
// e

signed main(){
_3PGDklf;
	int h,w;
	cin>>h>>w;
	vec(vi) a(h,vi(w));
	rep(i,h){
		rep(j,w){
			cin>>a[i][j];
		}
	}
	int q;
	cin>>q;
	rep(i,q){
		vi b(w);
		rep(j,w){
			cin>>b[j];
		}
		int res=0;
		rep(ro,h){
			bool pok=1;
			rep(co,w){
				if(a[ro][co]!=b[co] and b[co]!=-1){
					pok=0;
				}
			}
			res+=pok;
		}
		print(res);
	}
}
