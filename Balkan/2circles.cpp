#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define ldb double
struct pt{ldb x,y;pt(ldb a=0,ldb b=0):x(a),y(b){}};
pt operator - (pt a,pt b){return pt(a.x-b.x,a.y-b.y);}
pt operator + (pt a,pt b){return pt(a.x+b.x,a.y+b.y);}
pt operator * (pt a,ldb b){return pt(a.x*b,a.y*b);}
pt operator / (pt a,ldb b){return pt(a.x/b,a.y/b);}
ldb cross(pt a,pt b){return a.x*b.y-a.y*b.x;}
ldb dot(pt a,pt b){return a.x*b.x+a.y*b.y;}
ldb abs(pt a){return sqrt(dot(a,a));}
ldb dist(pt a,pt b){return abs(a-b);}
pt rot90(pt a){return pt(-a.y,a.x);}
struct line{pt v;ldb c;line(){}line(pt a,pt b):v(b-a),c(cross(v,b)){}};
ldb side(line a,pt b){return a.c-cross(a.v,b);}


ldb offs(line a,pt b){return dot(a.v,b);}
pt sec(line a,line b){return (b.v*a.c-a.v*b.c)/cross(a.v,b.v);}
bool bad(line a,line b,line c){
	return offs(b,sec(a,b))>=offs(b,sec(b,c));
}
vector<pt> HalfPlaneIntersection(vector<line> lines,vector<line>& out){
	vector<line> ans(lines.size());
	int lo=0,hi=-1;
	for(line now:lines){
		while(hi>=1&&bad(ans[hi-1],ans[hi],now))hi--;
		ans[++hi]=now;
	}
	while(hi-lo+1>=3){
		if(bad(ans[hi-1],ans[hi],ans[lo]))hi--;
		else if(bad(ans[hi],ans[lo],ans[lo+1]))lo++;
		else break;
	}
	if(hi-lo+1<3)return {};
	vector<pt> poly;
	for(int i=lo;i<=hi;i++){
		int j=i==hi?lo:i+1;
		poly.pb(sec(ans[i],ans[j]));
	}
	out=ans;
	return poly;
}


const int N=50050;
pt p[N];
int n;
bool Check(ldb R){
	vector<line> lines;
	for(int i=1;i<=n;i++){
		int j=i==n?1:i+1;
		pt D=rot90(p[j]-p[i]);
		D=D/abs(D)*R;
		line now=line(p[i]+D,p[j]+D);
		lines.pb(now);
	}
	vector<pt> q=HalfPlaneIntersection(lines,lines);
	int m=q.size();
	for(int i=0,j=0;i<m;i++){
		while(dist(q[i],q[j])<dist(q[i],q[(j+1)%m]))j=(j+1)%m;
		if(dist(q[i],q[j])>=2*R)return 1;
	}
	return 0;
}
int main(){
	scanf("%i",&n);
	for(int i=1,x,y;i<=n;i++){
		scanf("%i %i",&x,&y);
		p[i]=pt(x,y);
	}
	ldb top=2e7,bot=0,mid;
	while(top-bot>1e-3){
		mid=(top+bot)/2;
		if(Check(mid))bot=mid;
		else top=mid;
	}
	printf("%.3f\n",(top+bot)/2);
	return 0;
}

