#include<bits/stdc++.h>
using namespace std;
 
int n,d,a,xum;
 
int div(int x){
	int res=0;
	while(x){
		x>>=1;
		res+=x;
	}
	return res;
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n;
	d=div(n-1);
	for(int i=0;i<n;++i){
		cin>>a;
		int d1=div(i);
		int d2=div(n-i-1);
		if(d-d1-d2==0)
			xum^=a;
	}
	cout<<xum;
}
