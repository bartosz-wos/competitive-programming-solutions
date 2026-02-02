#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> adjList;
vector<bool> visited;
vector<int> sz;
vector<int> ans;
vector<pair<int, int>> values;

int threshold1 = 1e9;
int threshold2 = 1e9;
int node = -1;
int insubtree = -1;

int a, b;

vector<set<int>> tree;

void dfs1(int v) {
    visited[v] = true;
    int n = adjList.size();
    for (int con: adjList[v]) {
        if (!visited[con]) {
            tree[v].insert(con);
            tree[con].insert(v);
            dfs1(con);
            sz[v] += sz[con];
        }
    }
}

vector<int> pre;
vector<int> low;
vector<pair<int, int>> prod;
int timer = 0;

bool dfs2(int v, int p) {
    pre[v] = low[v] = timer++;
    visited[v] = true;
    int n = adjList.size();
    vector<int> merge;
    int maxi = n - sz[v];
    bool stop = false;
    for (int con: adjList[v]) {
        if (stop) return true;
        if (!visited[con]) {
            stop = stop || dfs2(con, v);
            maxi = max(maxi, sz[con]);
            low[v] = min(low[v], low[con]);
            if (low[con] < pre[v]) {
                merge.push_back(con);
                prod[v] = prod[con];
            }
        } else if (con != p && pre[con] < low[v]) {
            low[v] = pre[con];
            prod[v] = {v, con};
        }
    }
    int sum = n - sz[v];
    for (int con: merge) {
        sum += sz[con];
        if (a <= sum) break;
    }
    if (maxi < a && a <= sum) {
        sum = n - sz[v];
        for (int con: merge) {
            sum += sz[con];
            tree[prod[con].first].insert(prod[con].second);
            tree[prod[con].second].insert(prod[con].first);
            tree[v].erase(con);
            tree[con].erase(v);
            if (a <= sum) break;
        }
        node = v;
        return true;
    }
    return false;
}

void dfs3(int v) {
    visited[v] = true;
    for (int con: tree[v]) {
        if (!visited[con]) {
            dfs3(con);
            sz[v] += sz[con];
        }
    }
}
 
void assign(int v, int mode) {
    if (mode) {
        if (threshold1) ans[v] = values[insubtree].second, threshold1--;
        else ans[v] = values[2].second;
    } else {
        if (threshold2) ans[v] = values[1 - insubtree].second, threshold2--;
        else ans[v] = values[2].second;
    }
    visited[v] = true;
    for (int con: tree[v]) {
        if (!visited[con]) {
            assign(con, con == node? 1: mode);
        }
    }
}

vector<int> find_split(int n, int x, int y, int z, vector<int> u, vector<int> v) {
    int m = u.size(); // = v.size()
    adjList.clear();
    adjList.resize(n);
    visited.clear();
    visited.resize(n, false);
    sz.clear();
    sz.resize(n, 1);
    for (int i = 0; i < m; i++) {
        int a = u[i];
        int b = v[i];
        adjList[a].push_back(b);
        adjList[b].push_back(a);
    }

    ans.clear();
    ans.resize(n, 0);

    values.push_back({x, 1});
    values.push_back({y, 2});
    values.push_back({z, 3});
    sort(values.begin(), values.end());
    a = values[0].first;
    b = values[1].first;

    tree.resize(n);

    dfs1(0);

    for (int i = 0; i < n; i++) if (a <= sz[i] && sz[i] <= n - a) node = i;
    if (node == -1) {
        for (int i = 0; i < n; i++) visited[i] = false;
        pre.resize(n);
        low.resize(n);
        prod.resize(n, {-1, -1});
        dfs2(0, -1);
        if (node == -1) return ans;
    }

    for (int i = 0; i < n; i++) visited[i] = false;
    for (int i = 0; i < n; i++) sz[i] = 1;

    dfs3(0);

    int abovea = 1e9;
    int mini1 = -1;
    for (int i = 0; i < n; i++) if (sz[i] >= a && sz[i] < abovea) abovea = sz[i], mini1 = i;
    if (n - abovea >= b) {
        threshold1 = a;
        threshold2 = b;
        node = mini1;
        insubtree = 0;
    } else {
        int aboveb = 1e9;
        int mini2 = -1;
        for (int i = 0; i < n; i++) if (sz[i] >= b && sz[i] < aboveb) aboveb = sz[i], mini2 = i;
        if (n - aboveb >= a) {
            threshold1 = b;
            threshold2 = a;
            node = mini2;
            insubtree = 1;
        }
    }
    if (threshold1 == 1e9) return ans;
    for (int i = 0; i < n; i++) visited[i] = false;
    assign(0, 0);
    return ans;
}
