// tìm cây khung nhỏ nhất bằng thuật toán Prim
// Ý tưởng: tìm cạnh có trọng số nhỏ nhất nối đỉnh thuộc cây khung với đỉnh ngoài cây khung
// Độ phức tạp:
// - Thời gian: O((E+V)logV)
// - Không gian: O(V + E)

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string.h>

using namespace std;

#define MAX 1000
#define INF 1000000000

int n, m; // n là số đỉnh, m là số cạnh
int d[MAX + 1]; // d[i] là độ dài cạnh nhỏ nhất nối đến đỉnh i
int trace[MAX + 1]; // trace[i] là đỉnh trước đỉnh i
vector<vector<pair<int, int>>> adj; // danh sách kề của đồ thị

void input()
{
    string fileName = "MST.inp";
    ifstream inp(fileName.c_str());

    inp >> n >> m;

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

void Prim()
{
    // đánh dấu các đỉnh chưa thuộc cây khung
    for (int i = 1; i <= n; i++)
    {
        d[i] = INF;
    }

    // tìm đường đi ngắn nhất từ đỉnh 1 đến các đỉnh còn lại
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // đỉnh 1 là đỉnh xuất phát
    d[1] = 0;
    pq.push({0, 1}); // {trọng số, đỉnh}

    while (!pq.empty())
    {
        // lấy đỉnh u có d[u] nhỏ nhất ra khỏi hàng đợi
        // du là khoảng cách ngắn nhất từ 1 đỉnh đến tập đỉnh đã được thêm vào cây khung
        int u = pq.top().second;
        int du = pq.top().first;
        pq.pop();

        // đã có đỉnh u khác với chi phí nhỏ hơn đưa vào hàng đợi
        if (du != d[u])
            continue;

        // duyệt các đỉnh v kề u
        for (pair<int,int> p: adj[u])
        {
            int v = p.first;
            int w = p.second; // trọng số cạnh uv

            // nếu v chưa thuộc cây khung và trọng số mới (đi qua u-v) nhỏ hơn trọng số cũ
            if (v != trace[u] && d[v] > w)
            {
                d[v] = w;
                pq.push({d[v], v});
                trace[v] = u;
            }
        }
       
    }

}

void printAns()
{
    string fileName = "Prim.out";
    ofstream out(fileName.c_str());

    int sum = 0;
    // tổng độ dài cây khung
    for (int u = 2; u <= n; u++)
    {
        sum += d[u];
    }
    out << sum << endl;

    // in các cạnh của cây khung
    for (int i = 2; i <= n; i++)
    {
        out << trace[i] << " " << i << endl;
    }

    out.close();
}

int main()
{
    input();
    Prim();
    printAns();
    return 0;
}