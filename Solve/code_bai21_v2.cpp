// Sinh tất cả các cây khung của đồ thị
// Sinh các dãy bit từ 0 -> 2^E - 1 --> O(2^m)
// Kiểm tra xem dãy bit đó có tạo thành cây khung không --> O(max(m,n))
// Tổng cộng: O(2^m * max(m,n))

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

// Cấu trúc cạnh
struct Edge {
    int u, v, w;
};

// Cấu trúc đồ thị
struct Graph {
    int V, E;
    vector<Edge> edges;
};

// Cấu trúc cây khung
struct SpanningTree {
    vector<int> edges;
    int cost;

    SpanningTree(vector<int> edges, int count, int cost) {
        this->edges.resize(count);
        for (int i = 0; i < count; i++) {
            this->edges[i] = edges[i];
        }
        this->cost = cost;
    }
};

void readData(string filename, int &k, Graph &g) {
    ifstream inp(filename.c_str(), ios::in);

    inp >> g.V >> g.E >> k;

    for (int i = 0; i < g.E; i++) {
        Edge e;
        inp >> e.u >> e.v >> e.w;
        g.edges.push_back(e);
    }

    inp.close();
}

// Kiểm tra xem cạnh thứ i có được chọn không
bool isSelectEdge(int mask, int i) {
    return mask & (1 << i);
}

bool isST(Graph g, int mask, vector<int> &selectedEdges, int &cost) {
    int count = 0;
    selectedEdges.clear();
    cost = 0;
    // kiểm tra số cạnh được chọn có bằng V - 1 không
    for (int i = 0; i < g.E; i++) {
        if (isSelectEdge(mask, i)) {
            count++;
            cost += g.edges[i].w;
            selectedEdges.push_back(i);
        }
    }

    if (count != g.V - 1) {
        return false;
    }

    // kiểm tra có tạo thành một thành phần liên thông không
    vector<bool> isConnected(g.V + 1, false);

    queue<int> q;

    q.push(g.edges[selectedEdges[0]].u);
    isConnected[g.edges[selectedEdges[0]].u] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int i = 0; i < selectedEdges.size(); i++) {
            int v = g.edges[selectedEdges[i]].v;
            if (g.edges[selectedEdges[i]].u == u && !isConnected[v]) {
                isConnected[v] = true;
                q.push(v);
            }
        }
    }

    for (int i = 1; i <= g.V; i++) {
        if (!isConnected[i]) {
            return false;
        }
    }

    return true;
}

// Chọn các cạnh và kiểm tra có tạo thành cây khung không
void selectEdge(Graph g, vector<SpanningTree> &spanningTrees) {
    for (int mask = 0; mask < (1 << g.E); mask++) {
        int cost = 0;
        vector<int> selectedEdges;
        if (isST(g, mask, selectedEdges, cost) == true) {
            // add spanning tree
            spanningTrees.push_back(SpanningTree(selectedEdges, g.V - 1, cost));
        }
    }
}

// in ra k cây khung nhỏ nhất
void printAns(string filename, vector<SpanningTree> spanningTrees, int k) {
    ofstream out(filename.c_str(), ios::out);

    int sz = k < spanningTrees.size() ? k : spanningTrees.size();
    if (sz <= 0) {
        out << -1;
    } else {
        sort(spanningTrees.begin(), spanningTrees.end(), [](SpanningTree a, SpanningTree b) {
            return a.cost < b.cost;
        });

        for (int i = 0; i < sz; i++) {
            out << "#" << i + 1 << ": " << spanningTrees[i].cost << endl;
            for (int j = 0; j < spanningTrees[i].edges.size(); j++) {
                out << spanningTrees[i].edges[j] + 1 << " ";
            }
            out << endl;
        }
    }

    out.close();
}

int main() {
    string filein = "bai21.inp";
    string fileout = "bai21.out";

    Graph g;
    int k;
    vector<SpanningTree> spanningTrees;

    readData(filein, k , g);
    selectEdge(g, spanningTrees);
    printAns(fileout, spanningTrees, k);

    return 0;
}