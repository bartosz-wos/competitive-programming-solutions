#include<bits/stdc++.h>
#define pb push_back
using namespace std;
int main(){
	int n, ans=0;
	vector <int> v;
	cin>>n;
	for(int i=1; i<=n; i++){
		int a;
		cin>>a;
		ans+=a;
		v.pb(a);
	}
	//cout<<ans<<endl;
	sort(v.begin(), v.end());
	reverse(v.begin(), v.end());
	for(int i=0; i<n; i++){
		if((i+1)%3==0){
			ans-=v[i];
		}
	}
	cout<<ans;
}
