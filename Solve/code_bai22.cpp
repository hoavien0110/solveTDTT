// Đếm số cặp đỉnh (u,v) không đến được với nhau khi loại bỏ 1 cạnh

// Tìm cầu trong đồ thị

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAX = 100005;
int n, m;
vector<int> adj[MAX];
int low[MAX], num[MAX], parent[MAX];
int cnt = 0;

void dfs(int u) {
    low[u] = num[u] = ++cnt;
    for (int v : adj[u]) {
        if (num[v] == 0) {
            parent[v] = u;
            dfs(v);
            low[u] = min(low[u], low[v]);
            if (low[v] > num[u]) {
                cout << u << " " << v << endl;
            }
        } else if (v != parent[u]) {
            low[u] = min(low[u], num[v]);
        }
    }
}

int main() {
    string filein = "bai22.inp";
    string fileout = "bai22.out";

    ifstream inp(filein);

    inp >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v; inp >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    inp.close();
    
    dfs(1);
    return 0;
}