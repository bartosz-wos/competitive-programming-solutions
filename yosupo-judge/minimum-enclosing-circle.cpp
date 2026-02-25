#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using ld=long double;
using point=array<ld,2>;
using circle=array<ld,3>;

constexpr long double eps=1e-11;

double dist(const point&a, const point&b){
	return hypot(a[0]-b[0],a[1]-b[1]);
}

bool in(const point&a, const circle& c){
	return dist(a,{c[0],c[1]})<=c[2]+eps;
}

circle two(const point&a, const point&b){
	return {(a[0]+b[0])/2.0,(a[1]+b[1])/2.0,dist(a,b)/2.0};
}

circle three(const point&a, const point&b, const point&c){
	ld bx=b[0]-a[0];
	ld by=b[1]-a[1];
	ld cx=c[0]-a[0];
	ld cy=c[1]-a[1];
	ld bs=bx*bx+by*by;
	ld cs=cx*cx+cy*cy;
	ld cp=bx*cy-by*cx;
	if(abs(cp)<eps)return {0,0,0};
	return {(cy*bs-by*cs)/(2.0*cp)+a[0],(bx*cs-cx*bs)/(2.0*cp)+a[1],
		dist({(cy*bs-by*cs)/(2.0*cp)+a[0],(bx*cs-cx*bs)/(2.0*cp)+a[1]},a)};
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int n;
	cin>>n;
	vector<point>a(n),b;
	for(auto&[x,y]:a)cin>>x>>y;
	b=a;
	mt19937 rng(time(nullptr));
	shuffle(b.begin(),b.end(),rng);
	circle res={b[0][0],b[0][1],0};
	for(int i=1;i<n;++i)
		if(!in(b[i],res)){
			res={b[i][0],b[i][1],0};
			for(int j=0;j<i;++j)
				if(!in(b[j],res)){
					res=two(b[i],b[j]);
					for(int k=0;k<j;++k)
						if(!in(b[k],res))
							res=three(b[i],b[j],b[k]);
				}
		}
	string ret(n,'0');
	for(int i=0;i<n;++i)
		if(abs(dist(a[i],{res[0],res[1]})-res[2])<=eps)
			++ret[i];
	cout<<ret<<'\n';
}
