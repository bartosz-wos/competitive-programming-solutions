#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using cd=complex<double>;
constexpr double PI=acos(-1.0);

int n;
vector<int>g[200005];
int sz[200005];
bool del[200005];
ll ans[200005];

void fft(vector<cd>&a, bool f){
	int n=a.size();
	for(int i=1,j=0;i<n;++i){
		int b=n>>1;
		for(;j&b;b>>=1)j^=b;
		j^=b;
		if(i<j)swap(a[i],a[j]);
	}
	for(int len=2;len<=n;len<<=1){
		double ang=2.0*PI/len*(f?-1:1);
		cd wlen(cos(ang),sin(ang));
		for(int i=0;i<n;i+=len){
			cd w(1);
			for(int j=0;j*2<len;++j){
				cd u=a[i+j];
				cd v=a[i+j+len/2]*w;
				a[i+j]=u+v;
				a[i+j+len/2]=u-v;
				w*=wlen;
			}
		}
	}
	if(f)for(cd&x:a)x/=n;
}

vector<ll>mult(const vector<int>&a, const vector<int>&b){
	vector<cd>a2(a.begin(),a.end());
	vector<cd>b2(b.begin(),b.end());
	int n=1;
	while(n<a2.size()+b2.size())
		n<<=1;
	a2.resize(n);
	b2.resize(n);
	fft(a2,0);
	fft(b2,0);
	for(int i=0;i<n;++i)
		a2[i]*=b2[i];
	fft(a2,1);
	vector<ll>res(n);
	for(int i=0;i<n;++i)
		res[i]=llround(a2[i].real());
	return res;
}

void dfs_sz(int v, int e){
	sz[v]=1;
	for(const int&i:g[v]){
		if(i==e or del[i])continue;
		dfs_sz(i,v);
		sz[v]+=sz[i];
	}
}

int cen(int v, int e, int tot){
	for(const int&u:g[v]){
		if(u==e or del[u])continue;
		if((sz[u]<<1)>tot)return cen(u,v,tot);
	}
	return v;
}

void get_dist(int v, int e, int d, vector<int>&vec){
	if(d>=vec.size())vec.resize(d+1,0);
	++vec[d];
	for(const int&u:g[v]){
		if(u==e or del[u])continue;
		get_dist(u,v,d+1,vec);
	}
}

void decomp(int v){
	dfs_sz(v,-1);
	int c=cen(v,-1,sz[v]);
	del[c]=1;
	vector<vector<int>>polys;
	int mxlen=0;
	for(const int&u:g[c]){
		if(del[u])continue;
		vector<int>cnt;
		get_dist(u,c,1,cnt);
		polys.push_back(cnt);
		mxlen=max(mxlen,(int)cnt.size());
	}
	vector<int>tot(mxlen,0);
	if(tot.empty())tot={1};
	tot[0]=1;
	for(auto&poly:polys)
		for(int i=0;i<poly.size();++i)
			tot[i]+=poly[i];
	vector<ll>sq=mult(tot,tot);
	for(int i=0;i<min(n,(int)sq.size());++i)
		ans[i]+=sq[i];
	for(auto&poly:polys){
		vector<ll>p=mult(poly,poly);
		for(int i=0;i<min(n,(int)p.size());++i)
			ans[i]-=p[i];
	}
	for(const int&u:g[c])
		if(!del[u])decomp(u);
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n;
	for(int i=1,a,b;i<n;++i){
		cin>>a>>b;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	decomp(0);
	for(int i=1;i<n;++i)
		cout<<(ans[i]>>1)<<' ';
}
