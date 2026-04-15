#include<bits/stdc++.h>
using namespace std;
using ll=long long;
constexpr int k=27;
 
string s;
vector<int>t;
vector<int>a[k];
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>s;
	int n=s.size();
	for(int i=0;i<n;++i)a[max(0,s[i]-97+1)].push_back(i);
	for(int i=0;i<k;++i)
		for(int j:a[i])
			t.push_back(j);
	for(int i=t[a[0][0]];i!=a[0][0];i=t[i])cout<<s[i];
}
