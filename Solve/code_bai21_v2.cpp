// generate all Spanning Tree of a graph by DFS

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// định nghĩa cạnh của đồ thị
struct Edge {
    int u, v, w;
};

// định nghĩa cây khung của đồ thị
struct SpanningTree {
    int numNodes;
    int numEdges;
    vector<Edge> edges;

    // khởi tạo cây khung cho đồ thị có numNodes đỉnh
    SpanningTree(int numNodes = 0) {
        this->numNodes = numNodes;
        numEdges = 0;
    }

    // thêm cạnh (u, v) có trọng số w vào cây khung
    void addEdge(int u, int v, int w) {
        edges.push_back({u, v, w});
        numEdges++;
    }

    // xóa cạnh cuối cùng của cây khung
    void removeLastEdge() {
        edges.pop_back();
        numEdges--;
    }

    // xóa tất cả các cạnh của cây khung
    void clear() {
        numEdges = 0;
        edges.clear();
    }

    // tính tổng trọng số của cây khung
    int calculateSum() {
        int sum = 0;
        for (int i = 0; i < edges.size(); i++) {
            sum += edges[i].w;
        }
        return sum;
    }

    // kiểm tra cây khung đã đầy đủ các cạnh chưa
    bool isFull() {
        return numEdges == numNodes - 1;
    }
};

void readData(string fileName, int &n, int &m, int &k, vector<vector<pair<int,int>>> &adj)
{
    ifstream inp(fileName.c_str());

    inp >> n >> m >> k;

    adj.resize(n + 1);
    for (int i = 1; i <= m; i++)
    {
        int u, v, w;
        inp >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    inp.close();
}

void generateAllSpanningTrees(int u, SpanningTree &spanningTree, vector<SpanningTree> &spanningTrees, vector<int> &visited, vector<vector<pair<int,int>>> &adj, int &count)
{
    if (spanningTree.isFull())
    {
        count++;
        spanningTrees.push_back(spanningTree);
        return;
    }

    for (int i = 0; i < adj[u].size(); i++)
    {
        int v = adj[u][i].first;
        int w = adj[u][i].second;
        if (!visited[v])
        {
            visited[v] = 1;
            spanningTree.addEdge(u, v, w);
            generateAllSpanningTrees(v, spanningTree, spanningTrees, visited, adj, count);
            spanningTree.removeLastEdge();
            visited[v] = 0;
        }
    }
}

void printAns(string fileout, vector<SpanningTree> spanningTrees, int count)
{
    ofstream out(fileout.c_str());

    // out << count << endl;

    int sz = count < spanningTrees.size() ? count : spanningTrees.size();
    for (int i = 0; i < sz; i++)
    {
        out << "#" << i + 1 << ": " << endl;
        vector<Edge> edges = spanningTrees[i].edges;
        for (int j = 0; j < edges.size(); j++)
        {
            out << edges[j].u << " " << edges[j].v  << " " << edges[j].w << endl;
        }
    }

    out.close();
}

int main()
{
    string fileName = "bai21.inp";
    string fileout = "bai21.out";

    int n, m, k;
    vector<vector<pair<int,int>>> adj;

    readData(fileName, n, m, k, adj);

    vector<int> visited(n + 1);
    SpanningTree spanningTree(n); // cây khung cho đồ thị n đỉnh
    vector<SpanningTree> spanningTrees; // tập hợp các cây khung của đồ thị
    int count = 0;

    // xây dựng tất cả các cây khung của đồ thị
    generateAllSpanningTrees(1, spanningTree, spanningTrees, visited, adj, count);

    // sắp xếp các cây khung theo thứ tự tăng dần của tổng trọng số - số cạnh
    sort(spanningTrees.begin(), spanningTrees.end(), [](SpanningTree a, SpanningTree b) {
        int sumA = a.calculateSum();
        int sumB = b.calculateSum();

        if (sumA != sumB)
            return sumA < sumB;
        else return a.numEdges < b.numEdges;
    });

    // in ra k cây khung đầu tiên
    printAns(fileout, spanningTrees, k);

    return 0;
}