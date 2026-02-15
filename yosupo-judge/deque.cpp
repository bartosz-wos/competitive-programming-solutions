#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int main(){
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
        int q;
        cin>>q;
        deque<int>dq;
        while(q--){
                int t;
                cin>>t;
                if(t==2){
                        dq.pop_front();
                        continue;
                }
                else if(t==3){
                        dq.pop_back();
                        continue;
                }
                int x;
                cin>>x;
                if(!t)dq.push_front(x);
                else if(t==1)dq.push_back(x);
                else cout<<dq[x]<<'\n';
        }
}
