#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int n,m,ret=0;
vector<set<int>>g,g2;
vector<int>ans_set;

void solve(){
        g2=g;
        vector<int>per(n);
        vector<bool>used(n,0);
        vector<int>cur_set;
        int cnt=0;
        iota(per.begin(),per.end(),0);
        for(int i=0;i<5;++i)
                random_shuffle(per.begin(),per.end());
        for(int j=0;j<n;++j){
                int v=per[j];
                if(used[v])continue;
                used[v]=1;
                ++cnt;
                cur_set.push_back(v);
                if(n-1-j+cur_set.size()<=ans_set.size())return;
                if(n-cnt+cur_set.size()<=ans_set.size())return;
                vector<int>to_erase;
                for(const int&i:g2[v])
                        to_erase.push_back(i);
                for(const int&i:to_erase){
                        g2[v].erase(i);
                        g2[i].erase(v);
                        if(!used[i])++cnt;
                        used[i]=1;
                }
        }
        sort(cur_set.begin(),cur_set.end());
        if(cur_set.size()>ans_set.size())
                ans_set.swap(cur_set);
}

int main(){
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
        srand(time(nullptr));
        cin>>n>>m;
        g.resize(n);
        while(m--){
                int a,b;
                cin>>a>>b;
                g[a].insert(b);
                g[b].insert(a);
        }
        int reps=50000;
        while(reps--)
                solve();
        cout<<ans_set.size()<<'\n';
        for(const int&v:ans_set)
                cout<<v<<' ';
}
