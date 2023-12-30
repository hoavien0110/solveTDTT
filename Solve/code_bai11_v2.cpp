#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>

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
    // sort cluster decreasingly by first value
    sort(cluster.begin() + 1, cluster.end(), [](pair<int, int> a, pair<int, int> b) {
        return a.first > b.first;
    });

    // f[i][j]: with i first clusters, j groups B
    // 0 <= i <= num
    // 0 <= j <= numGroupB
    vector<vector<int>> f(num + 1, vector<int>(numGroupB + 1, -INF));

    f[0][0] = 0;

    for (int i = 1; i <= num; i++) {
        for (int j = 0; j <= numGroupB; j++) {
            // cluster are sorted decreasingly by first value (A)
            // so if do not choose cluster i for group B
            // it will be choosen for group A if possible (i - j <= numGroupA)
            if (i > j && i - j <= numGroupA) {
                // choose cluster i to group A
                f[i][j] = f[i - 1][j] + cluster[i].first;
            }
            else f[i][j] = f[i - 1][j]; // not choose cluster i

            if (j > 0) {
                // choose cluster i to group B
                f[i][j] = max(f[i][j], f[i - 1][j - 1] + cluster[i].second);
            }
        }
    }

    return f[num][numGroupB];
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