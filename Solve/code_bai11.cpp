#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

#define INF 1e9

using namespace std;

void readData(string filein, int &num, int &numGroupA, int &numGroupB, vector<pair<int, int>> &cluster) {
    ifstream inp(filein);

    inp >> num >> numGroupA >> numGroupB;

    cluster.resize(num + 1);

    int x, y;
    for (int i = 1; i <= num; i++) {
        inp >> x >> y;
        cluster[i] = make_pair(x, y);
    }

    inp.close();
}

int divideClusters(int num, int numGroupA, int numGroupB, vector<pair<int, int>> cluster) {
    // f[i][j][k]: with i first clusters, j groups A, k groups B
    // 0 <= i <= num
    // 0 <= j <= numGroupA
    // 0 <= k <= numGroupB
    vector<vector<vector<int>>> f(num + 1, vector<vector<int>>(numGroupA + 1, vector<int>(numGroupB + 1, -INF)));

    f[0][0][0] = 0;

    for (int i = 1; i <= num; i++) {
        for (int j = 0; j <= numGroupA; j++) {
            for (int k = 0; k <= numGroupB; k++) {
                f[i][j][k] = f[i - 1][j][k]; // not choose cluster i
                if (j > 0) {
                    // choose cluster i to group A
                    f[i][j][k] = max(f[i][j][k], f[i - 1][j - 1][k] + cluster[i].first); 
                }
                if (k > 0) {
                    // choose cluster i to group B
                    f[i][j][k] = max(f[i][j][k], f[i - 1][j][k - 1] + cluster[i].second);
                }
            }
        }
    }

    return f[num][numGroupA][numGroupB];    
}

void printAns(string fileout, int ans) {
    ofstream out(fileout);

    out << ans;

    out.close();
}

int main() {
    string filein = "bai11.inp";
    string fileout = "bai11.out";

    int numGroupA, numGroupB;
    int num;
    vector<pair<int, int>> cluster;

    readData(filein, num, numGroupA, numGroupB, cluster);
    int ans = divideClusters(num, numGroupA, numGroupB, cluster);
    printAns(fileout, ans);

    return 0;
}