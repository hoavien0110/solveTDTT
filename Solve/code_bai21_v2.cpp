#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v, w;
};

struct Graph {
    int V, E;
    vector<Edge> edges;
};

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

int checkST(Graph g, vector<int> selectedEdges) {
    int sz = g.V - 1;
    int cost = 0;

    for (int i = 0; i < sz; i++) {
        int w = g.edges[selectedEdges[i]].w;
        cost += w;
    }

    return cost;
}

void selectEdge(Graph g, vector<int> selectedEdges, int count, vector<SpanningTree> &spanningTrees) {
    cout << "-----------------\n";
    cout << "count = " << count << endl;
    for (int i = 0; i < count; i++) {
        cout << selectedEdges[i] << " ";
    }
    cout << endl;

    if (count == g.V - 1) {
        // đủ số lượng cạnh
        // for (int i = 0; i < g.V - 1; i++) {
        //     cout << selectedEdges[i] << " ";
        // }
        // cout << endl;

        int cost = checkST(g, selectedEdges);
        if (cost != -1) {
            spanningTrees.push_back(SpanningTree(selectedEdges, count, cost));
        }
        return;
    }

    int start = (count == 0) ? 0 : selectedEdges[count - 1] + 1;
    for (int i = start; i < g.V; i++) {
        cout << i << endl;
        selectedEdges[count] = i;
        selectEdge(g, selectedEdges, count + 1, spanningTrees);
    }
}

void printAns(string filename, vector<SpanningTree> spanningTrees, int k) {
    ofstream out(filename.c_str(), ios::out);

    int sz = k < spanningTrees.size() ? k : spanningTrees.size();
    if (sz == 0) {
        out << -1;
    } else {
        sort(spanningTrees.begin(), spanningTrees.end(), [](SpanningTree a, SpanningTree b) {
            return a.cost < b.cost;
        });

        for (int i = 0; i < sz; i++) {
            if (spanningTrees[i].cost > k) {
                break;
            }

            for (int j = 0; j < spanningTrees[i].edges.size(); j++) {
                out << spanningTrees[i].edges[j] << " ";
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
    vector<int> selectedEdges;
    int count = 0; // số cạnh đã chọn
    selectedEdges.resize(g.V);

    readData(filein, k , g);
    selectEdge(g, selectedEdges, count, spanningTrees);
    printAns(fileout, spanningTrees, k);

    return 0;
}