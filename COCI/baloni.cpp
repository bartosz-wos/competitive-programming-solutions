#include <bits/stdc++.h>
#define int long long 
using namespace std;
int h[1000001];
int32_t main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n,ans=0;
	cin >> n;
	for(int i=0;i<n;i++)cin >> h[i];
	map<int,int> mp;
	for(int i=0;i<n;i++){
		if(mp[h[i]]>0){
			mp[h[i]]--;
			mp[h[i]-1]++;
		}
		else{
			ans++;
			mp[h[i]-1]++;
		}
	}
	cout << ans << "\n";
	return 0;
}
