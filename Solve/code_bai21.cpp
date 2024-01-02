// // Tìm tất cả cầu trong đồ thị

// #include <iostream>
// #include <vector>
// #include <algorithm>
// #include <fstream>
// using namespace std;

// struct Node {
//     int u,
//     int v,
//     int w
// };

// const int MAX = 100005;
// int n, m;
// vector<pair<int,int>> adj[MAX];
// int low[MAX], num[MAX], parent[MAX], numchild[MAX];
// int res[MAX];
// vector<Node> bridges;
// int cnt = 0;


// void dfs(int u) {
//     low[u] = num[u] = ++cnt;
//     numchild[u] = 1;

//     for (pair<int,int> p : adj[u]) {
//         int v = p.first;
//         int id = p.second;

//         if (num[v] == 0) {
//             parent[v] = u;
//             dfs(v);
//             low[u] = min(low[u], low[v]);
//             numchild[u] += numchild[v];
//             if (low[v] > num[u]) {
//                 // u - v is a bridge
//                 res[id] = numchild[v] * (n - numchild[v]);
//             }
//         } else if (v != parent[u]) {
//             low[u] = min(low[u], num[v]);
//         }
//     }
// }

// // Xóa cầu ra khỏi adj
// void removeAllBridges() {
//     // Lưu danh sách cầu (1 cầu có u, v, w) vào mảng bridges 
    
    

//     for (int i = 1; i <= n; i++) {
//         for (pair<int,int> p : adj[i]) {
//             int v = p.first;
//             int id = p.second;
            
//             if (res[id] > 0) {
//                 bridges.push_back({adj[i].begin(), ad, res[id]});
//                 adj[i].erase(remove(adj[i].begin(), adj[i].end(), p), adj[i].end());
//                 adj[v].erase(remove(adj[v].begin(), adj[v].end(), make_pair(i, id)), adj[v].end());
//             }
//         }
//     }
// }

// // Tìm tất cả các thành phần liên thông 
// void dfs2(int u, vector<int> &component) {
//     // u là đỉnh đầu tiên của thành phần liên thông
//     // component là tập hợp các đỉnh trong thành phần liên thông

//     component.push_back(u);
//     num[u] = 1;
//     for (pair<int,int> p : adj[u]) {
//         int v = p.first;
//         if (num[v] == 0) {
//             dfs2(v, component);
//         }
//     }
// }

// int main() {
//     // read file
//     ifstream fileInp("bai21.inp", ios::in);
    

//     fileInp >> n >> m;
//     for (int i = 1; i <= m; i++) {
//         int u, v;
//         fileInp >> u >> v;
//         adj[u].push_back(make_pair(v, i));
//         adj[v].push_back(make_pair(u, i));
//     }

//     // Tìm cầu
//     dfs(1);
    
//     // Xóa cầu
//     removeAllBridges();

//     // Tìm tất cả các thành phần liên thông
//     vector<vector<int>> components;
//     for (int i = 1; i <= n; i++) {
//         num[i] = 0;
//     }
//     for (int i = 1; i <= n; i++) {
//         if (num[i] == 0) {
//             vector<int> component;
//             dfs2(i, component);
//             components.push_back(component);
//         }
//     }

//     /
    

//     return 0;
// }



