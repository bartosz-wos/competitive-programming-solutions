#include <iostream>
using namespace std;
using ll=long long;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int t;
	cin>>t;
	while(t--){
	    int x,y;
	    cin>>x>>y;
	    if(x+y>6)cout<<"YES"<<'\n';
	    else cout<<"NO"<<endl;
	}
}
