#include<bits/stdc++.h>
#include "trilib.h"
using namespace std;
using ll=long long;

constexpr int N=2e5+5;

int n;

int c=0;

bool cmp(int x, int y){
    ++c;
    return is_clockwise(1,x,y);
}

vector<int>l,r,res;
int s[N],ss[N],cnt[N];

map<pair<int,pair<int,int>>,int>mp;

void shift(int x){
    for(int i=1;i<=n;++i)
        ss[(i+x)%n+1]=s[i];
    for(int i=1;i<=n;++i)
        s[i]=ss[i];
}

bool check(int x, int y, int z){
    if(mp[{x,{y,z}}]>0)return mp[{x,{y,z}}]-1;
    ++c;
    mp[{x,{y,z}}]=is_clockwise(x,y,z)+1;
    return mp[{x,{y,z}}]-1;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    n=get_n();
    for(int i=2;i<n;++i)
        if(!is_clockwise(1,n,i))
            l.push_back(i);
        else
            r.push_back(i);
    sort(l.begin(),l.end(),cmp);
    sort(r.begin(),r.end(),cmp);
    s[1]=1;
    for(int i=0;i<l.size();++i)
        s[2+i]=l[i];
    s[l.size()+2]=n;
    for(int i=0;i<r.size();++i)
        s[l.size()+3+i]=r[i];
    srand(time(nullptr));
    int tc=20;
    int _tc=20;
    while(_tc--){
        res.clear();
        shift(rand()%n);
        for(int i=1;i<=n;++i){
            while(res.size()>=2 and !check(res[res.size()-2],res.back(),s[i]))
                res.pop_back();
            res.push_back(s[i]);
        }
        for(int i:res)++cnt[i];
    }
    int ret=0;
    for(int i=1;i<=n;++i)
        if(cnt[i]==tc)++ret;
    give_answer(ret);
}
