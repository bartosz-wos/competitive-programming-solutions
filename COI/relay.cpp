#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using ld=long double;
using pt=complex<ld>;
using seg=pair<pt,pt>;

#define pb push_back
#define X real()
#define Y imag()
#define F first
#define S second
#define sz(x) (int)((x).size())
#define al(x) x.begin(),x.end()


constexpr int MAXN=100000;

bool reaches[MAXN];

seg rev(seg e){return {e.S,e.F};}

ll cross(pt p1, pt p2){return(conj(p1)*p2).Y;}

ll dot(pt p1, pt p2){return(conj(p1)*p2).X;}

bool prawo(pt p, seg e){
    bool ret=cross(e.S-e.F,p-e.S)<=0;
    return ret;
}

pt get(vector<pt>& v, int idx) {return v[(idx%sz(v)+sz(v))%sz(v)];}

bool inside(pt p, vector<pt>& hull) {
    for(int i=0;i<sz(hull);++i){
        seg e={hull[i],get(hull,i+1)};
        if (prawo(p,e))return 0;
    }
    return 1;
}

pt styczna(vector<pt>&hull,pt p,bool f1,bool f2) {
    for(int i=0;i<sz(hull);++i){
        seg o1={get(hull,i-1),hull[i]};
        seg o2={hull[i],get(hull,i+1)};
        if (prawo(p,o1)==f1 and prawo(p,o2)==f2) {
            return hull[i];
        }
    }
    assert(0);
}

ld cosa(pt e1,pt e2) {
    ld res=dot(e1, e2);
    res/=abs(e1);
    res/=abs(e2);
    return res;
}

seg findfarthest(vector<pt>&cand,seg st,int dir,vector<pt>& hull) {
    int idx=0;
    for(int i=0;i<sz(hull);++i)
        if(hull[i] == st.S)idx = i;
    seg res=st;
    ld mincos=1;
    for (const pt p:cand) {
        seg curr={p,hull[idx]};
        while (1) {
            seg e={hull[idx],get(hull,idx+dir)};
            if (dir<0) e=rev(e);
            if (prawo(p,e)) {
                idx=((idx+dir)%sz(hull)+sz(hull))%sz(hull);
                curr={p,get(hull, idx)};
            } else break;
        }
        ld c=cosa(curr.S-curr.F,st.S-st.F);
        if (c<mincos){
            res=curr;
            mincos=c;
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n,m;
    vector<pt>v,hull;
    cin>>n;
    for(int i=0;i<n;++i){
        ll x,y;
        cin>>x>>y;
        v.pb({x,y});
    }
    cin>>m;
    for(int i=0;i<m;++i){
        ll x,y;
        cin>>x>>y;
        hull.pb({x,y});
    }
    
    pt pst=styczna(hull,v[0],1,0);
    pt lst=styczna(hull,v[0],0,1);
    
    vector<pt>triangle;
    triangle.pb(v[0]);
    triangle.pb(pst);
    triangle.pb(lst);
    
    vector<pt>leftpoints,rightpoints;
    for(int i=0;i<sz(v);++i){
        if (inside(v[i],triangle)) {
            reaches[i]=1;
        }
        if (prawo(v[i],{v[0],pst})) {
            reaches[i]=1;
            rightpoints.pb(v[i]);
        }
        if (prawo(v[i],{lst,v[0]})) {
            reaches[i]=1;
            leftpoints.pb(v[i]);
        }
    }
    
    seg farthestleft=findfarthest(leftpoints,{v[0],lst},-1,hull);
    seg farthestright=findfarthest(rightpoints,{v[0],pst},1,hull);
    
    vector<pt>lefttriangle;
    lefttriangle.pb(farthestleft.F);
    lefttriangle.pb(lst);
    lefttriangle.pb(farthestleft.S);
    
    vector<pt>righttriangle;
    righttriangle.pb(farthestright.F);
    righttriangle.pb(farthestright.S);
    righttriangle.pb(pst);
    
    for(int i=0;i<sz(v);++i){
        if (prawo(v[i], rev(farthestleft)))reaches[i]=1;
        if (prawo(v[i],farthestright))reaches[i]=1;
        if (inside(v[i],lefttriangle))reaches[i]=1;
        if(inside(v[i],righttriangle))reaches[i]=1;
    }
    int res=0;
    for(int i=0;i<n;++i)if(reaches[i])++res;
    cout<<--res<<'\n';
}
