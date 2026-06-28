#include<bits/stdc++.h>
using namespace std;
using ll=long long;

struct event{
        int x;
        int type;
        int y1,y2;
        ll w;
        int id;
};

struct BIT{
        int n;
        vector<ll>st;
        BIT(int n) : n(n), st(n+1,0){}
        void add(int i, ll d){
                for(;i<=n;i+=i&-i)st[i]+=d;
        }
        ll query(int i){
                ll s=0;
                for(;i>0;i-=i&-i)s+=st[i];
                return s;
        }
};

int cnt=0;
vector<ll>ans;
BIT* bit_tree;
vector<event>temp;

void cdq(int l, int r, vector<event>& events){
        if(l==r)return;
        int mid=l+(r-l)/2;
        
        cdq(l,mid,events);
        cdq(mid+1,r,events);
        
        int i=l,j=mid+1,k=l;
        
        while(i<=mid&&j<=r){
                bool choose_left;
                if(events[i].x!=events[j].x){
                        choose_left=events[i].x<events[j].x;
                }else if(events[i].type!=events[j].type){
                        choose_left=events[i].type<events[j].type;
                }else{
                        choose_left=true;
                }
                
                if(choose_left){
                        if(events[i].type==1){
                                bit_tree->add(events[i].y1,events[i].w);
                                bit_tree->add(events[i].y2,-events[i].w);
                        }
                        temp[k++]=events[i++];
                }else{
                        if(events[j].type==2){
                                ans[events[j].id]+=bit_tree->query(events[j].y1);
                        }
                        temp[k++]=events[j++];
                }
        }
        
        while(i<=mid){
                if(events[i].type==1){
                        bit_tree->add(events[i].y1,events[i].w);
                        bit_tree->add(events[i].y2,-events[i].w);
                }
                temp[k++]=events[i++];
        }
        
        while(j<=r){
                if(events[j].type==2){
                        ans[events[j].id]+=bit_tree->query(events[j].y1);
                }
                temp[k++]=events[j++];
        }
        
        for(int p=l;p<=mid;++p){
                if(events[p].type==1){
                        bit_tree->add(events[p].y1,-events[p].w);
                        bit_tree->add(events[p].y2,events[p].w);
                }
        }
        
        for(int p=l;p<=r;++p)
                events[p]=temp[p];
}

struct rawRect{int l,d,r,u;ll w;};
struct rawQuery{int type,l,d,r,u,x,y;ll w;};

int main(){
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
        int n,q;
        cin>>n>>q;
        vector<int>ys;
        vector<rawRect>rects(n);
        for(int i=0;i<n;++i){
                cin>>rects[i].l>>rects[i].d>>rects[i].r>>rects[i].u>>rects[i].w;
                ys.push_back(rects[i].d);
                ys.push_back(rects[i].u);
        }

        vector<rawQuery>queries(q);
        for(int i=0;i<q;++i){
                cin>>queries[i].type;
                if(!queries[i].type){
                        cin>>queries[i].l>>queries[i].d>>queries[i].r>>queries[i].u>>queries[i].w;
                        ys.push_back(queries[i].d);
                        ys.push_back(queries[i].u);
                }else{
                        cin>>queries[i].x>>queries[i].y;
                        ys.push_back(queries[i].y);
                }
        }

        sort(ys.begin(),ys.end());
        ys.erase(unique(ys.begin(),ys.end()),ys.end());
        auto get_y=[&](int y){
                return lower_bound(ys.begin(),ys.end(),y)-ys.begin()+1;
        };

        vector<event>events;
        for(const auto&r:rects){
                events.push_back({r.l,1,get_y(r.d),get_y(r.u),r.w,-1});
                events.push_back({r.r,1,get_y(r.d),get_y(r.u),-r.w,-1});
        }

        for(const auto&qq:queries){
                if(!qq.type){
                        events.push_back({qq.l,1,get_y(qq.d),get_y(qq.u),qq.w,-1});
                        events.push_back({qq.r,1,get_y(qq.d),get_y(qq.u),-qq.w,-1});
                }else events.push_back({qq.x,2,get_y(qq.y),0,0,cnt++});
        }

        if(events.empty())return 0;
        ans.assign(cnt,0);
        bit_tree=new BIT(ys.size());
        temp.resize(events.size());

        cdq(0,events.size()-1,events);
	delete bit_tree;
        for(int i=0;i<cnt;++i)
                cout<<ans[i]<<'\n';
}
