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
	vector<char> col(n+1,'?');
	auto ask=[&](int i)->char{
		if(col[i]!='?')return col[i];
		cout<<"? "<<i<<endl;
		cout.flush();
		char c;cin>>c;
		col[i]=c;
		return c;
	};
	char c1=ask(1);
	char cn=ask(n);
	if(c1==cn){
		cout<<"! 1"<<endl;
		cout.flush();
		return 0;
	}
	int l=1,r=n;
	auto seg_has_equal=[&](int L,int R)->bool{
		char a=col[L];
		if(a=='?')a=ask(L);
		char b=col[R];
		if(b=='?')b=ask(R);
		int len=R-L+1;
		if(a==b)return (len%2==0);
		else return (len%2==1);
	};
	while(r-l>1){
		int mid=(l+r)/2;
		ask(mid);
		if(seg_has_equal(l,mid))r=mid;
		else l=mid;
	}
	cout<<"! "<<l<<endl;
	cout.flush();
	return 0;
}
