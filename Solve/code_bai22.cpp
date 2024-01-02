// Đếm số cặp đỉnh (u,v) không đến được với nhau khi loại bỏ 1 cạnh

// Tìm cầu trong đồ thị

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAX = 100005;
int n, m;
vector<pair<int,int>> adj[MAX];
int low[MAX], num[MAX], parent[MAX], numchild[MAX];
int res[MAX];
int cnt = 0;

void dfs(int u) {
    low[u] = num[u] = ++cnt;
    numchild[u] = 1;

    for (pair<int,int> p : adj[u]) {
        int v = p.first;
        int id = p.second;

        if (num[v] == 0) {
            parent[v] = u;
            dfs(v);
            low[u] = min(low[u], low[v]);
            numchild[u] += numchild[v];
            if (low[v] > num[u]) {
                // u - v is a bridge
                res[id] = numchild[v] * (n - numchild[v]);
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
        adj[u].push_back(make_pair(v, i));
        adj[v].push_back(make_pair(u, i));
    }

    inp.close();

    dfs(1);

    ofstream out(fileout);

    for (int i = 1; i <= m; i++) {
        out << res[i] << endl;
    }

    out.close();

    return 0;
}

/*
Độ phức tạp:
- Thời gian: O(n + m)
- Bộ nhớ: O(n + m)
*/