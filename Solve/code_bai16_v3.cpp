// Time: O(n); Space: O(n)
#include <iostream>
#include <vector>
#include <fstream>
#include <queue>

using namespace std;

struct Node {
    int numNodes;
    long long sumDist;
    long long breadth;

    Node() {
        numNodes = 1;
        sumDist = 0;
        breadth = 0;
    }
};

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

void dfs(int id, vector<vector<int>> &graph, vector<Node> &nodes, vector<bool> &visited) {
    visited[id] = true;

    for (int child : graph[id]) {
        if (!visited[child]) {
            dfs(child, graph, nodes, visited);

            
            nodes[id].breadth += nodes[child].breadth 
                                + nodes[child].numNodes * nodes[id].sumDist
                                + nodes[id].numNodes * (nodes[child].numNodes + nodes[child].sumDist);
            nodes[id].sumDist += nodes[child].sumDist + nodes[child].numNodes;
            nodes[id].numNodes += nodes[child].numNodes;
            // cout << id << ": " << nodes[id].breadth << " " << nodes[id].sumDist << " " << nodes[id].numNodes << endl;
        }
    }
    // cout << id << ": " << nodes[id].breadth << " " << nodes[id].sumDist << " " << nodes[id].numNodes << endl;
}

long long findBreadth(int numNodes, vector<vector<int>> &graph) {
    long long ans = 0;

    vector<Node> nodes(numNodes + 1);
    vector<bool> visited(numNodes + 1, false);

    dfs(1, graph, nodes, visited);

    return nodes[1].breadth;
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

/*
GIẢI THÍCH CODE Ở ĐÂY NÈ

Hướng giải quyết: quy hoạch động trên cây

Tại 1 node id, giả sử ta tính được các thông số sau:
+ numNodes: Số lượng node trong cây con gốc là node id (tính cả nó)
+ sumDist: Tổng khoảng cách từ node id đến các node trong cây con gốc là node id
+ breadth: Độ rộng của cây con gốc là node id (tổng khoảng cách giữa các cặp đỉnh trong cây con)

Ban đầu, 1 cây chỉ có 1 node lá là chính nó:
+ numNodes = 1
+ sumDist = 0
+ breadth = 0

Với 1 cây có sẵn với gốc là node root (numNodes = n, sumDist = s, breadth = b) 
và cây con có gốc là child (numNodes = n', sumDist = s', breadth = b'). 
Gom cây con child vào root:
+ breadth = b + b' + (mỗi node trong child -> mỗi node trong root)
    -> Tính (1 node trong child -> mỗi node trong root):
    ((node trong child) -> root) * n + s
    = (k/c đến root) * n + s
    -> Tính (mỗi node trong child) -> (mỗi node trong root):
    // p là khoảng cách từ node đến root; sum(ki) = n'
    // (s + p_i.n).k_i: tổng chi phí từ các node có độ sâu p_i (so với root) 
    (s + n).k1 + (s + 2n).k2 + ... + (s + pn).kp 
     = n' * s + n * (s' +  n')
     // n * (n' + s'): tổng khoảng cách từ các node trong child đến root
     // n' * s: tổng khoảng cách từ root đến các node trong root
=> breadth = b + b' + n' * s + n * (s' +  n')
+ sumDist = s + s' + n', nghĩa là:
    * s: tổng khoảng cách từ root đến các node ban đầu
    * s' + n': tổng khoảng cách từ các node trong cây child đến root 
        (node -> root = node -> child + child -> root = node -> child + 1; 
        n' node nên tổng khoảng cách cần thêm là n')
+ numNodes = n + n'

Kết quả: breadth của root = 1

Độ phức tạp:
+ Time: O(n)
+ Space: O(n)
*/