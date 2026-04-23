#include<bits/stdc++.h>
using namespace std;
using ll=long long;
int n,m;
int ind[100001];
vector<int>g[100001];
priority_queue<int>Q;
vector<int>order;
 
int main(){
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
        cin>>n>>m;
        while(m--){
                int a,b;
                cin>>a>>b;
                g[b].push_back(a);
                ++ind[a];
        }
        for(int i=1;i<=n;++i)
                if(!ind[i])
                        Q.push(i);
        while(!Q.empty()){
                int u=Q.top();
                Q.pop();
                order.push_back(u);
                for(const int&i:g[u])
                        if(--ind[i]==0)
                                Q.push(i);
        }
        for(auto it=order.crbegin();it!=order.crend();++it)
                cout<<*it<<' ';
}
