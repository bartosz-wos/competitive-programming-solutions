#include<bits/stdc++.h>
using namespace std;
using ll=long long;
 
struct pt{
	ll x,y;
};
 
ll dist(pt a, pt b){
	a.x=abs(a.x-b.x);
	a.y=abs(a.y-b.y);
	return a.x*a.x+a.y*a.y;
}
 
ll cross(pt a, pt b){
	return a.x*b.y-b.x*a.y;
}
 
int orient(pt a, pt b, pt c){
	ll o=cross(a,b)+cross(b,c)+cross(c,a);
	if(o<0) return -1;
	if(o>0) return 1;
	return 0;
}
 
bool cw(pt a, pt b, pt c, bool f){
	int o=orient(a,b,c);
	return o<0 or (o==0 and f);
}
 
bool colin(pt a, pt b, pt c){
	return orient(a,b,c)==0;
}
 
void convex_hull(vector<pt>&a, bool f){
	pt p0=*min_element(a.begin(),a.end(),[](const pt& a, const pt& b){
		if(a.y==b.y)
			return a.x<b.x;
		return a.y<b.y;
	});
	sort(a.begin(),a.end(),[&p0](const pt& a, const pt& b){
		int o=orient(p0,a,b);
		if(o==0) return dist(p0,a)<dist(p0,b);
		return o<0;
	});
 
	if(f){
		int i=a.size()-1;
		while(i>=0 and colin(p0,a[i],a.back()))
			--i;
		reverse(a.begin()+i+1,a.end());
	}
 
	vector<pt>st;
	for(int i=0;i<a.size();++i){
		while(st.size()>1 and !cw(st.end()[-2],st.back(),a[i],1))
			st.pop_back();
		st.push_back(a[i]);
	}
	a=st;
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int n;
	cin>>n;
	vector<pt>a;
	a.resize(n);
	for(int i=0;i<n;++i)
		cin>>a[i].x>>a[i].y;
	convex_hull(a,1);
	cout<<a.size()<<'\n';
	for(const auto&[f,s]:a)
		cout<<f<<' '<<s<<'\n';
}
