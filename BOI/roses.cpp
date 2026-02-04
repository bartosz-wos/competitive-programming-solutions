#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define fi first
#define se second
#define pb push_back
#define vi vector<int>
#define pi pair<int, int>
#define all(x) (x).begin(),(x).end()

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll n,a,b,c,d;
    cin >> n >> a >> b >> c >> d;
    if (b*c>a*d) {
        swap(a,c);
        swap(b,d);
    }
    ll ans=1e18;
	for(int i=0; i<a; i++) {
		ll lft=n-i*c;
		ll cnt=lft>0?(lft-1)/a+1:0;
		ans= min(ans,cnt*b+i*d);
	}
	cout << ans << '\n';
    return 0;
}
