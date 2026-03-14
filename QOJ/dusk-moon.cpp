#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned ll
#define pb emplace_back
#define mp make_pair
#define ALL(x) (x).begin(),(x).end()
#define rALL(x) (x).rbegin(),(x).rend()
#define srt(x) sort(ALL(x))
#define rev(x) reverse(ALL(x))
#define rsrt(x) sort(rALL(x))
#define sz(x) (int)(x.size())
#define inf 0x3f3f3f3f
#define pii pair<int,int>
#define lb(v,x) (int)(lower_bound(ALL(v),x)-v.begin())
#define ub(v,x) (int)(upper_bound(ALL(v),x)-v.begin())
#define uni(v) v.resize(unique(ALL(v))-v.begin())
#define longer __int128_t
void die(string S){puts(S.c_str());exit(0);}
const int B=80;
#define ls (x<<1)
#define rs (ls|1)
mt19937_64 rng(0xb6e0);
ll a[100100],b[100100];
class solver
{
	public:
		ll X,Y;
		ll val[100100];
		int segt[100100<<2];
		void build(int x,int l,int r)
		{
			if(l==r)
			{
				segt[x]=l;
				return ;
			}
			int mid=(l+r)/2;
			build(ls,l,mid);
			build(rs,mid+1,r);
			if(val[segt[ls]]>val[segt[rs]])
				segt[x]=segt[ls];
			else
				segt[x]=segt[rs];
		}
		void init(int n)
		{
			X=(ll)rng()%2000000000;
			Y=(ll)rng()%200000000;
			X-=1e9;
			Y-=1e8;
			if(rng()&1)
				Y+=X;
			else
				Y-=X;
			for(int i=1;i<=n;i++)
				val[i]=X*a[i]+Y*b[i];
			build(1,1,n);
		}
		void update(int x,int l,int r,int p)
		{
			if(l==r) return ;
			int mid=(l+r)/2;
			if(p<=mid) update(ls,l,mid,p);
			else update(rs,mid+1,r,p);
			if(val[segt[ls]]>val[segt[rs]])
				segt[x]=segt[ls];
			else
				segt[x]=segt[rs];
		}
		void refresh(int n,int x)
		{
			val[x]=X*a[x]+Y*b[x];
			update(1,1,n,x);
		}
		int query(int x,int l,int r,int ql,int qr)
		{
			if(ql==l&&r==qr) return segt[x];
			int mid=(l+r)/2;
			if(qr<=mid) return query(ls,l,mid,ql,qr);
			if(ql>mid) return query(rs,mid+1,r,ql,qr);
			int A=query(ls,l,mid,ql,mid);
			int B=query(rs,mid+1,r,mid+1,qr);
			return (val[A]>val[B])?A:B;
		}
}sv[B];
namespace Geometry
{
	struct point {
	double x, y;
	} p[100005], o;

	double sqr(double x) { return x * x; }

	double dis(point a, point b) { return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y)); }

	bool cmp(double a, double b) { return fabs(a - b) < 1e-8; }

	point geto(point a, point b, point c) {
	double a1, a2, b1, b2, c1, c2;
	point ans;
	a1 = 2 * (b.x - a.x), b1 = 2 * (b.y - a.y),
	c1 = sqr(b.x) - sqr(a.x) + sqr(b.y) - sqr(a.y);
	a2 = 2 * (c.x - a.x), b2 = 2 * (c.y - a.y),
	c2 = sqr(c.x) - sqr(a.x) + sqr(c.y) - sqr(a.y);
	if (cmp(a1, 0)) {
		ans.y = c1 / b1;
		ans.x = (c2 - ans.y * b2) / a2;
	} else if (cmp(b1, 0)) {
		ans.x = c1 / a1;
		ans.y = (c2 - ans.x * a2) / b2;
	} else {
		ans.x = (c2 * b1 - c1 * b2) / (a2 * b1 - a1 * b2);
		ans.y = (c2 * a1 - c1 * a2) / (b2 * a1 - b1 * a2);
	}
	return ans;
	}
	int r;
	const double eps=1e-8;
	inline int op(double ans){return 1+(int)(ans+eps);}
	int main(int n) {
	r=0;
	for (int i = 1; i <= n; i++) swap(p[rng() % n + 1], p[rng() % n + 1]);
	o = p[1];
	for (int i = 1; i <= n; i++) {
		if (dis(o, p[i]) < r || cmp(dis(o, p[i]), r)) continue;
		o.x = (p[i].x + p[1].x) / 2;
		o.y = (p[i].y + p[1].y) / 2;
		r = op(dis(p[i], p[1]) / 2);
		for (int j = 2; j < i; j++) {
		if (dis(o, p[j]) < r || cmp(dis(o, p[j]), r)) continue;
		o.x = (p[i].x + p[j].x) / 2;
		o.y = (p[i].y + p[j].y) / 2;
		r = op(dis(p[i], p[j]) / 2);
		for (int k = 1; k < j; k++) {
			if (dis(o, p[k]) < r || cmp(dis(o, p[k]), r)) continue;
			o = geto(p[i], p[j], p[k]);
			r = op(dis(o, p[i]));
		}
		}
	}
	return r;
	}
}
int solve(vector<int> vind)
{
	int n=sz(vind);
	for(int i=1;i<=n;i++)
		Geometry::p[i]={(double)a[vind[i-1]],(double)b[vind[i-1]]};
	return Geometry::main(n);
}
const int thres=5e7;
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin>>t;
	while(t--)
	{
		int n,q;
		cin>>n>>q;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i]>>b[i];
			a[i]-=thres;
			b[i]-=thres;
		}
		for(int i=0;i<B;i++)
			sv[i].init(n);
		while(q--)
		{
			int op;
			cin>>op;
			if(op==1)
			{
				int k;
				cin>>k;
				cin>>a[k]>>b[k];
				a[k]-=thres;
				b[k]-=thres;
				for(int i=0;i<B;i++)
					sv[i].refresh(n,k);
			}
			else
			{
				int l,r;
				cin>>l>>r;
				vector<int> vind;
				if(r-l<2000)
				{
					for(int i=l;i<=r;i++)
						vind.pb(i);
				}
				else
				{
					for(int i=0;i<B;i++)
						vind.pb(sv[i].query(1,1,n,l,r));
					srt(vind);
					uni(vind);
				}
				cout<<solve(vind)<<'\n';
			}
		}
	}
}
