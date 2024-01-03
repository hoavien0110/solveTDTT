// tìm cây khung nhỏ nhất bằng thuật toán Kruskal
// ý tưởng: sắp xếp các cạnh theo thứ tự tăng dần của trọng số
// duyệt qua các cạnh, nếu cạnh đó không tạo thành chu trình thì thêm cạnh đó vào cây khung
// đánh dấu các đỉnh đã được thêm vào cây khung bằng cách gán cùng 1 nhóm cho các đỉnh đó
// nếu 2 đỉnh thuộc 2 nhóm khác nhau thì hợp 2 nhóm lại thành 1 nhóm
// nếu 2 đỉnh thuộc cùng 1 nhóm thì bỏ qua cạnh đó
// độ phức tạp thuật toán:
// + thời gian: O(ElogE + ElogV)
// + không gian: O(V + E)


#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// cấu trúc cạnh
struct Edge {
    int u, v, w;
};

// cấu trúc đồ thị
struct Graph {
    int V, E;
    vector<Edge> edge;
};

// cấu trúc tập con
struct Subset {
    int parent; // đỉnh cha
    int rank; // số đỉnh con

    Subset() {
        parent = 0;
        rank = 0;
    }
};

// tìm tập con chứa u
int find(Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);

    return subsets[i].parent;
}

// hợp 2 tập con chứa x và y
void Union(Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    // gán tập con có số đỉnh con ít hơn vào tập con có số đỉnh con nhiều hơn
    if (subsets[xroot].rank < subsets[yroot].rank) {
       subsets[xroot].parent = yroot;
       subsets[yroot].rank += subsets[xroot].rank;
    }
    else {
       subsets[yroot].parent = xroot;
         subsets[xroot].rank += subsets[yroot].rank;
    }
}

// so sánh 2 cạnh
bool cmp(Edge a, Edge b) {
    return a.w < b.w;
}

// thuật toán Kruskal tìm cây khung nhỏ nhất
void Kruskal(Graph graph, vector<Edge> &result) {
    int V = graph.V; // số đỉnh của đồ thị
    int e = 0; // số cạnh đã thêm vào cây khung
    int i = 0; // chỉ số cạnh đang xét

    // sắp xếp các cạnh theo thứ tự tăng dần của trọng số
    sort(graph.edge.begin(), graph.edge.end(), cmp);

    // tạo tập con chứa các đỉnh
    Subset *subsets = new Subset[V];

    // tạo V tập con, mỗi tập con chứa 1 đỉnh
    for (int v = 1; v <= V; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 1;
    }

    // trong khi số cạnh đã thêm vào cây khung chưa đủ V-1 và chưa duyệt hết các cạnh
    while (e < V - 1 && i < graph.E) {
        Edge next_edge = graph.edge[i++];

        int x = find(subsets, next_edge.u);
        int y = find(subsets, next_edge.v);

        if (x != y) {
            result.push_back(next_edge);
            Union(subsets, x, y);
            e++;
        }
    }
}

void readData(Graph &graph) {
    string s = "MST.inp";

    ifstream inp(s.c_str());
    inp >> graph.V >> graph.E;

    for (int i = 0; i < graph.E; i++) {
        Edge e;
        inp >> e.u >> e.v >> e.w;
        graph.edge.push_back(e);
    }

    inp.close();
}

void printAns(vector<Edge> result) {
    string fileName = "Kruskal.out";
    ofstream out(fileName.c_str());

    int sum = 0;
    int sz = result.size();
    for (int i = 0; i < sz; i++) {
        sum += result[i].w;
    }

    out << sum << endl;

    for (int i = 0; i < sz; i++) {
        out << result[i].u << " " << result[i].v << endl;
    }

    out.close();
}

int main() {
    Graph graph;
    vector<Edge> result;

    readData(graph);
    Kruskal(graph, result);
    printAns(result);

    return 0;
}