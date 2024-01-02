// Time: O(n); Space: O(n)
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

long long findBreadth(int numNodes, vector<vector<int>> &graph) {
    long long ans = 0;

    // breadth of a tree is the sum of the distance from each node to the root
    // solve with time complexity O(n)
    
    return ans;
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
