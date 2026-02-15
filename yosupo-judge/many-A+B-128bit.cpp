#include<bits/stdc++.h>
using namespace std;
using ll=long long;

void f(__int128 x){
	if(!x){
		cout<<0<<'\n';
		return;
	}
	if(x/10)f(x/10);
	cout<<(int)(x%10);
}

int main(){
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
        int t;
        cin>>t;
        while(t--){
                string a,b;
		cin>>a>>b;
		__int128 p=1,c=0;
		__int128 neg_a=1,neg_b=1;
		if(a[0]=='-'){
			neg_a=-1;
			a=a.substr(1);
		}
		if(b[0]=='-'){
			neg_b=-1;
			b=b.substr(1);
		}
		while(!a.empty() or !b.empty()){
			if(!a.empty())c+=(__int128)(a.back()-48)*p*neg_a,a.pop_back();
			if(!b.empty())c+=(__int128)(b.back()-48)*p*neg_b,b.pop_back();
			p*=(__int128)10;
		}
		if(c<0){
			cout<<'-';
			c=-c;
		}
		f(c);
		cout<<'\n';
        }
}
