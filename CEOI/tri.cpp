#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pi=pair<int,int>;
using vi=vector<int>;

#define fi first
#define se second

constexpr int N=1e5+5;

struct pt{
    ll x,y;
    bool operator<(const pt&b){
        return x*b.y-b.x*y>0;
    }
};

void print(pt a){
    cout<<a.x<<' '<<a.y<<'\n';
}

pt p[N];

ll area(pt a, pt b, pt c){
    return (b.x-a.x)*(c.y-a.y)-(c.x-a.x)*(b.y-a.y);
}

int cmp(pt a, pt b){
    ll val=a.x*b.y-b.x*a.y;
    if(val==0)return 0;
    if(val<0)return 1;
    return -1;
}

struct segtree{
    int n;
    vector<vi>seg;
    bool ans;
    void convex_hull(vector<int>&hull,int l,int r){
        for(int i=l;i<=r;++i){
            while(hull.size()>=2 and area(p[hull[hull.size()-2]],p[hull.back()],p[i])>0)
                hull.pop_back();
            hull.push_back(i);
        }
    }
    void build(int v,int l, int r){
        convex_hull(seg[v],l,r);
        if(l==r)return;
        int mid=(l+r)>>1;
        build(v<<1,l,mid);
        build(v<<1|1,mid+1,r);
    }
    segtree(int xd):n(xd){
        seg.resize(n<<2);
        build(1,1,n);
    }
    bool solve(vector<int>&hull,pt a,pt b){
        int l=0,r=hull.size()-1;
        while(l<r){
            int mid=(l+r)>>1;
            ll res1=area(a,b,p[hull[mid]]);
            if(res1>0)return 1;
            ll res2=area(a,b,p[hull[mid+1]]);
            if(res1>res2)r=mid-1;
            else l=mid+1;
        }
        return area(a,b,p[hull[l]])>0;
    }
    void query(int v,int l,int r,pt a,pt b){
        if(ans)return;
        if(cmp(b,p[l])<0)return;
        if(cmp(a,p[r])>0)return;
        
        if( cmp(a,p[l])<=0 and cmp(p[r],b)<=0  ){
            ans|=solve(seg[v],a,b);
            return;
        }
        
        if(l==r)return;
        int mid=(l+r)>>1;
        query(v<<1,l,mid,a,b);
        query(v<<1|1,mid+1,r,a,b);
    }
    bool get(pt a,pt b){
        ans=0;
        query(1,1,n,a,b);
        return ans;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cerr<<"sir black monkey on the beat\n";
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;++i)
        cin>>p[i].x>>p[i].y;
    sort(p+1,p+n+1);
    segtree t(n);
    /*
    for(int i=1;i<=n;++i)
        cout<<p[i].x<<' '<<p[i].y<<'\n';
    */
    while(m--){
        pt a,b;
        cin>>a.x>>a.y>>b.x>>b.y;
        if(cmp(a,b)==1)swap(a,b);
        cout<<(t.get(a,b)?'Y':'N')<<'\n';
    }
}
