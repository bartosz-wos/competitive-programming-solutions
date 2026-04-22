#include<bits/stdc++.h>
using namespace std;
using ll=long long;
#define fi first
#define se second
#define pb push_back
 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n;
	if(!(cin>>n))return 0;
	if(n==1){
		cout<<"! 1"<<endl;
		cout.flush();
		return 0;
	}
	int lim=0;
	while((1<<lim)<n)lim++;
	vector<int> ans(n,0);
	for(int t=0;t<lim;t++){
		string q;
		q.resize(n);
		for(int i=0;i<n;i++){
			q[i]=((i>>t)&1)?'1':'0';
		}
		cout<<"? "<<q<<endl;
		cout.flush();
		string r;
		cin>>r;
		for(int j=0;j<n;j++){
			if(r[j]=='1')ans[j]|=(1<<t);
		}
	}
	cout<<"!";
	for(int j=0;j<n;j++)cout<<' '<<ans[j]+1;
	cout<<endl;
	cout.flush();
	return 0;
}
