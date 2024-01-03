// Dijkstra tìm đường đi ngắn nhất từ 1 đỉnh đến các đỉnh còn lại
// Độ phức tạp: (m+n)logn

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
int d[MAX + 1]; // d[i] là độ dài đường đi ngắn nhất từ đỉnh 1 đến đỉnh i
int trace[MAX + 1]; // trace[i] là đỉnh trước đỉnh i trên đường đi ngắn nhất từ đỉnh 1 đến đỉnh i
vector<vector<pair<int,int>>> adj; // danh sách kề của đồ thị

void input()
{
    string fileName = "Dijkstra.inp";
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

void Dijkstra()
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
    pq.push({0, 1}); // {chi phí, đỉnh}

    while (!pq.empty())
    {
        // lấy đỉnh u có d[u] nhỏ nhất ra khỏi hàng đợi
        int u = pq.top().second;
        int du = pq.top().first;
        pq.pop();

        // đã có đỉnh u khác với chi phí nhỏ hơn đưa vào hàng đợi
        if (du > d[u])
            continue;

        // duyệt các đỉnh v kề u
        for (pair<int,int> p: adj[u])
        {
            int v = p.first;
            int w = p.second;

            if (d[v] > w + d[u])
            {
                d[v] = w + d[u];
                pq.push({d[v], v});
                trace[v] = u;
            }
        }
    }

}

void printAns()
{
    string fileName = "Dijkstra.out";
    ofstream out(fileName.c_str());

    for (int i = 1; i <= n; i++) {
        cout << i << " " << trace[i] << " " << d[i] << endl;
    }

    out.close();
}

int main()
{
    input();
    Dijkstra();
    printAns();
    return 0;
}