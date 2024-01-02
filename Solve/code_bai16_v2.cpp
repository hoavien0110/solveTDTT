// Time: O(n^2); Space: O(n)
// DFS from each node to find the distance to the root
#include <iostream>
#include <vector>
#include <fstream>

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

void dfs(int node, vector<vector<int>> &graph, vector<bool> &visited, vector<int> &distance) {
    visited[node] = true;

    for (int i = 0; i < graph[node].size(); i++) {
        int nextNode = graph[node][i];

        if (!visited[nextNode]) {
            distance[nextNode] = distance[node] + 1;
            dfs(nextNode, graph, visited, distance);
        }
    }
}

long long findBreadth(int numNodes, vector<vector<int>> &graph) {
    long long ans = 0;

    // DFS from each node to find the distance to the root
    for (int i = 1; i <= numNodes; i++) {
        vector<bool> visited(numNodes + 1, false);
        vector<int> distance(numNodes + 1, 0);
        
        dfs(i, graph, visited, distance);

        for (int j = 1; j <= numNodes; j++) {
            // distance[j] is the distance from node j to the root
            ans += distance[j];
        }
    }

    // Divide by 2 because each pair of node is counted twice
    return ans / 2;
}

void printAns(string filename, long long ans) {
    ofstream out(filename);

    out << ans;

    out.close();
}

int main() {
    string filein = "bai16.inp";
    string fileout = "bai16.out";

    int numNodes;
    vector<vector<int>> graph;

    readData(filein, numNodes, graph);
    long long ans = findBreadth(numNodes, graph);
    printAns(fileout, ans);

    return 0;
}
