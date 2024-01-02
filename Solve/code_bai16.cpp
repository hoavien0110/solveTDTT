// Time: O(n^2.logn); Space: O(n^2.logn)
#include <iostream>
#include <vector>
#include <fstream>

#define MAXLOG 20

using namespace std;

void readData(string filename, int &numNodes, vector<vector<int>> &graph) {
    ifstream inp(filename);

    inp >> numNodes;
    graph.resize(numNodes + 1);

    for (int i = 0; i < numNodes - 1; i++) {
        int u, v;
        inp >> u >> v;

        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    inp.close();
}

void dfs(int u, int p, vector<vector<int>> &graph, vector<vector<int>> &parent, vector<int> &depth) {
    parent[u][0] = p;

    for (int i = 1; i < MAXLOG; i++) {
        parent[u][i] = parent[parent[u][i - 1]][i - 1];
    }

    for (int v : graph[u]) {
        if (v != p) {
            depth[v] = depth[u] + 1;
            dfs(v, u, graph, parent, depth);
        }
    }
}

void init(int numNodes, vector<vector<int>> &graph, vector<vector<int>> &parent, vector<int> &depth) {
    parent.resize(numNodes + 1);
    depth.resize(numNodes + 1);

    for (int i = 0; i <= numNodes; i++) {
        parent[i].resize(MAXLOG, 0);
    }

    depth[1] = 1;
    dfs(1, 0, graph, parent, depth);
}

int findLCA(int u, int v, vector<vector<int>> &parent, vector<int> &depth) {
    if (depth[u] < depth[v]) {
        swap(u, v);
    }

    for (int i = MAXLOG - 1; i >= 0; i--) {
        if (depth[u] - (1 << i) >= depth[v]) {
            u = parent[u][i];
        }
    }

    if (u == v) {
        return u;
    }

    for (int i = MAXLOG - 1; i >= 0; i--) {
        if (parent[u][i] != parent[v][i]) {
            u = parent[u][i];
            v = parent[v][i];
        }
    }

    return parent[u][0];
}

int calculateDistance(int u, int v, vector<vector<int>> &parent, vector<int> &depth) {
    int lca = findLCA(u, v, parent, depth);

    return depth[u] + depth[v] - 2 * depth[lca];
}

int findBreadth(int numNodes, vector<vector<int>> &graph, vector<vector<int>> &parent, vector<int> &depth) {
    int ans = 0;

    for (int u = 1; u <= numNodes; u++) {
        for (int v = u + 1; v <= numNodes; v++) {
            ans += calculateDistance(u, v, parent, depth);
        }
    }

    return ans;
}

void printAns(string filename, int ans) {
    ofstream out(filename);

    out << ans;

    out.close();
}

int main() {
    string filein = "bai16.inp";
    string fileout = "bai16.out";

    int numNodes;
    vector<vector<int>> graph;

    vector<vector<int>> parent;
    vector<int> depth;

    readData(filein, numNodes, graph);
    init(numNodes, graph, parent, depth);
    int ans = findBreadth(numNodes, graph, parent, depth);
    printAns(fileout, ans);

    return 0;
}
